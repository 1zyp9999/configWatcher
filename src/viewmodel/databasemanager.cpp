#include "databasemanager.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QRegularExpression>
#include <QSqlRecord>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QXmlStreamReader>

DatabaseManager* DatabaseManager::s_instance = nullptr;

DatabaseManager::DatabaseManager(QObject* parent) : QObject(parent)
{
}

DatabaseManager::~DatabaseManager()
{
    closeDatabase();
}

bool DatabaseManager::openDatabase(const QString& path, const QString& connectionName)
{
    // Ensure directory exists (path is file path)
    QFileInfo fi(path);
    QDir dir = fi.absoluteDir();
    if (!dir.exists()) dir.mkpath(".");

    // Use named connection if provided, otherwise default connection
    m_connectionName = connectionName.isEmpty()
        ? QLatin1String(QSqlDatabase::defaultConnection)
        : connectionName;
    m_db = QSqlDatabase::addDatabase("QSQLITE", m_connectionName);
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        qWarning() << "Failed to open database:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery q(m_db);
    q.exec("PRAGMA foreign_keys = ON;");
    q.exec("PRAGMA journal_mode = WAL;");

    // Create schema
    if (!q.exec(
        "CREATE TABLE IF NOT EXISTS files ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "path TEXT NOT NULL UNIQUE,"
        "format TEXT,"
        "last_scanned DATETIME"
        ")")) {
        qWarning() << "Failed to create files table:" << q.lastError().text();
        return false;
    }

    if (!q.exec(
        "CREATE TABLE IF NOT EXISTS sections ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "file_id INTEGER NOT NULL,"
        "name TEXT NOT NULL,"
        "item_index INTEGER DEFAULT -1,"
        "UNIQUE(file_id, name, item_index),"
        "FOREIGN KEY(file_id) REFERENCES files(id) ON DELETE CASCADE"
        ")")) {
        qWarning() << "Failed to create sections table:" << q.lastError().text();
        return false;
    }

    if (!q.exec(
        "CREATE TABLE IF NOT EXISTS parameters ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "file_id INTEGER NOT NULL,"
        "section_id INTEGER NOT NULL,"
        "key TEXT NOT NULL,"
        "raw_value TEXT,"
        "value_type TEXT,"
        "num1 REAL,"
        "num2 REAL,"
        "device TEXT,"
        "chinese_name TEXT,"
        "description TEXT,"
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
        "updated_at DATETIME,"
        "UNIQUE(file_id, section_id, key),"
        "FOREIGN KEY(file_id) REFERENCES files(id) ON DELETE CASCADE,"
        "FOREIGN KEY(section_id) REFERENCES sections(id) ON DELETE CASCADE"
        ")")) {
        qWarning() << "Failed to create parameters table:" << q.lastError().text();
        return false;
    }

    q.exec("CREATE INDEX IF NOT EXISTS idx_parameters_key ON parameters(key);");
    q.exec("CREATE INDEX IF NOT EXISTS idx_parameters_device ON parameters(device);");
    q.exec("CREATE INDEX IF NOT EXISTS idx_sections_file ON sections(file_id);");

    // translations table
    q.exec("CREATE TABLE IF NOT EXISTS translations (key TEXT PRIMARY KEY, chinese TEXT);");

    // FTS5 detection
    bool ftsOk = q.exec(R"(CREATE VIRTUAL TABLE IF NOT EXISTS __fts_test USING fts5(content);)" );
    if (ftsOk) {
        q.exec("DROP TABLE IF EXISTS __fts_test;");
        m_useFts5 = true;
    } else {
        m_useFts5 = false;
    }

    if (m_useFts5) {
        q.exec(R"(CREATE VIRTUAL TABLE IF NOT EXISTS parameters_fts USING fts5(key, raw_value, chinese_name, device, content='parameters', content_rowid='id');)" );
        q.exec(R"(
            CREATE TRIGGER IF NOT EXISTS parameters_ai AFTER INSERT ON parameters BEGIN
              INSERT INTO parameters_fts(rowid, key, raw_value, chinese_name, device) VALUES (new.id, new.key, new.raw_value, new.chinese_name, new.device);
            END;
        )");
        q.exec(R"(
            CREATE TRIGGER IF NOT EXISTS parameters_ad AFTER DELETE ON parameters BEGIN
              INSERT INTO parameters_fts(parameters_fts, rowid, key, raw_value, chinese_name, device) VALUES('delete', old.id, old.key, old.raw_value, old.chinese_name, old.device);
            END;
        )");
        q.exec(R"(
            CREATE TRIGGER IF NOT EXISTS parameters_au AFTER UPDATE ON parameters BEGIN
              INSERT INTO parameters_fts(parameters_fts, rowid, key, raw_value, chinese_name, device) VALUES('delete', old.id, old.key, old.raw_value, old.chinese_name, old.device);
              INSERT INTO parameters_fts(rowid, key, raw_value, chinese_name, device) VALUES (new.id, new.key, new.raw_value, new.chinese_name, new.device);
            END;
        )");

        q.exec(R"(INSERT INTO parameters_fts(rowid, key, raw_value, chinese_name, device) SELECT id, key, raw_value, chinese_name, device FROM parameters WHERE id NOT IN (SELECT rowid FROM parameters_fts);)" );
    }

    // 修改记录表
    q.exec("CREATE TABLE IF NOT EXISTS change_log ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "file_path TEXT NOT NULL,"
           "key TEXT NOT NULL,"
           "old_value TEXT,"
           "new_value TEXT,"
           "changed_at DATETIME DEFAULT CURRENT_TIMESTAMP"
           ")");
    q.exec("CREATE INDEX IF NOT EXISTS idx_changelog_file ON change_log(file_path);");
    q.exec("CREATE INDEX IF NOT EXISTS idx_changelog_time ON change_log(changed_at DESC);");

    s_instance = this;
    return true;
}

void DatabaseManager::closeDatabase()
{
    if (m_db.isOpen()) m_db.close();
    if (s_instance == this) s_instance = nullptr;
    // Remove named connection to avoid Qt warning about dangling connections
    if (!m_connectionName.isEmpty()) {
        QString connName = m_connectionName;
        m_db = QSqlDatabase(); // Release handle before removing
        QSqlDatabase::removeDatabase(connName);
        m_connectionName.clear();
    }
}

int DatabaseManager::ensureFile(const QString& path, const QString& format)
{
    if (!m_db.isOpen()) return -1;
    QSqlQuery q(m_db);
    q.prepare("SELECT id FROM files WHERE path = :path");
    q.bindValue(":path", path);
    if (!q.exec()) return -1;
    if (q.next()) return q.value(0).toInt();

    q.prepare("INSERT INTO files (path, format, last_scanned) VALUES (:path, :format, CURRENT_TIMESTAMP)");
    q.bindValue(":path", path);
    q.bindValue(":format", format);
    if (!q.exec()) return -1;
    return q.lastInsertId().toInt();
}

int DatabaseManager::ensureSection(int fileId, const QString& name, int itemIndex)
{
    if (!m_db.isOpen()) return -1;
    QSqlQuery q(m_db);
    q.prepare("SELECT id FROM sections WHERE file_id = :fid AND name = :name AND item_index = :idx");
    q.bindValue(":fid", fileId);
    q.bindValue(":name", name);
    q.bindValue(":idx", itemIndex);
    if (!q.exec()) return -1;
    if (q.next()) return q.value(0).toInt();

    q.prepare("INSERT INTO sections (file_id, name, item_index) VALUES (:fid, :name, :idx)");
    q.bindValue(":fid", fileId);
    q.bindValue(":name", name);
    q.bindValue(":idx", itemIndex);
    if (!q.exec()) return -1;
    return q.lastInsertId().toInt();
}

bool DatabaseManager::upsertParameter(int fileId,
                                      int sectionId,
                                      const QString& key,
                                      const QString& rawValue,
                                      const QString& valueType,
                                      double num1,
                                      double num2,
                                      const QString& device,
                                      const QString& chineseName,
                                      const QString& description)
{
    if (!m_db.isOpen()) return false;
    QSqlQuery q(m_db);
    q.prepare(R"(
        INSERT INTO parameters (file_id, section_id, key, raw_value, value_type, num1, num2, device, chinese_name, description, updated_at)
        VALUES (:fid, :sid, :key, :raw, :vtype, :n1, :n2, :device, :cname, :desc, CURRENT_TIMESTAMP)
        ON CONFLICT(file_id, section_id, key) DO UPDATE SET
          raw_value = excluded.raw_value,
          value_type = excluded.value_type,
          num1 = excluded.num1,
          num2 = excluded.num2,
          device = excluded.device,
          chinese_name = excluded.chinese_name,
          description = excluded.description,
          updated_at = CURRENT_TIMESTAMP
    )");
    q.bindValue(":fid", fileId);
    q.bindValue(":sid", sectionId);
    q.bindValue(":key", key);
    q.bindValue(":raw", rawValue);
    q.bindValue(":vtype", valueType);
    q.bindValue(":n1", num1);
    q.bindValue(":n2", num2);
    q.bindValue(":device", device);
    q.bindValue(":cname", chineseName);
    q.bindValue(":desc", description);
    if (!q.exec()) {
        qWarning() << "upsert failed:" << q.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::importIniFile(const QString& filePath, const QString& device)
{
    if (!m_db.isOpen()) return false;
    QFile f(filePath);
    if (!f.exists()) { qWarning() << "ini not found:" << filePath; return false; }
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) { qWarning() << "open failed:" << filePath; return false; }

    QTextStream in(&f);
    QString section;
    QRegularExpression listRe(R"((.+)\.(.+)\.(\d+)$)");

    QSqlQuery tx(m_db);
    if (!tx.exec("BEGIN")) { qWarning() << "Failed to begin transaction:" << tx.lastError().text(); }

    int fileId = ensureFile(filePath, QStringLiteral("ini"));
    if (fileId < 0) { tx.exec("ROLLBACK"); f.close(); return false; }

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith(';') || line.startsWith('#')) continue;
        if (line.startsWith('[') && line.endsWith(']')) {
            section = line.mid(1, line.size() - 2).trimmed();
            continue;
        }
        int eqPos = line.indexOf('=');
        if (eqPos > 0) {
            QString key = line.left(eqPos).trimmed();
            QString value = line.mid(eqPos + 1).trimmed();

            QString sectionName = section;
            int itemIndex = -1;
            QRegularExpressionMatch m = listRe.match(section);
            if (m.hasMatch()) {
                sectionName = m.captured(1) + "." + m.captured(2);
                itemIndex = m.captured(3).toInt();
            }

            int sectionId = ensureSection(fileId, sectionName, itemIndex);
            if (sectionId < 0) continue;

            double n1 = 0, n2 = 0;
            QString vtype = "string";
            QString raw = value;
            QStringList parts = value.split(',', QString::SkipEmptyParts);
            if (parts.size() == 2) {
                bool ok1=false, ok2=false;
                double a = parts[0].toDouble(&ok1);
                double b = parts[1].toDouble(&ok2);
                if (ok1 && ok2) { n1 = a; n2 = b; vtype = "pair"; }
            } else {
                bool okInt=false; int iv = value.toInt(&okInt);
                if (okInt) { vtype = "int"; n1 = iv; }
                else {
                    bool okDouble=false; double dv = value.toDouble(&okDouble);
                    if (okDouble) { vtype = "float"; n1 = dv; }
                }
            }

            QString chineseName = key;
            QString description;
            QString dev = device;
            if (key.toLower().contains("cameratype") || key.toLower().contains("stagetype")) {
                dev = value;
            }

            upsertParameter(fileId, sectionId, key, raw, vtype, n1, n2, dev, chineseName, description);
        }
    }

    QSqlQuery commit(m_db);
    if (!commit.exec("COMMIT")) { qWarning() << "Commit failed:" << commit.lastError().text(); }

    f.close();
    return true;
}

// ---- JSON 文件导入 ----
bool DatabaseManager::importJsonFile(const QString& filePath, const QString& device)
{
    if (!m_db.isOpen()) return false;
    QFile f(filePath);
    if (!f.exists()) { qWarning() << "json not found:" << filePath; return false; }
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) { qWarning() << "open failed:" << filePath; return false; }

    QByteArray data = f.readAll();
    f.close();

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << err.errorString() << filePath;
        return false;
    }

    QSqlQuery tx(m_db);
    tx.exec("BEGIN");

    int fileId = ensureFile(filePath, QStringLiteral("json"));
    if (fileId < 0) { tx.exec("ROLLBACK"); return false; }

    // 递归辅助 lambda：将 JSON 对象展平写入 DB
    std::function<void(const QJsonObject&, const QString&, const QString&)> importObj;
    importObj = [&](const QJsonObject& obj, const QString& sectionName, const QString& dev) {
        int sectionId = ensureSection(fileId, sectionName, -1);
        if (sectionId < 0) return;
        for (auto it = obj.constBegin(); it != obj.constEnd(); ++it) {
            QString key = it.key();
            QJsonValue val = it.value();
            if (val.isObject()) {
                // 嵌套对象作为子 section
                QString childSection = sectionName.isEmpty() ? key : (sectionName + "." + key);
                importObj(val.toObject(), childSection, dev);
            } else if (val.isArray()) {
                QJsonArray arr = val.toArray();
                for (int i = 0; i < arr.size(); ++i) {
                    if (arr[i].isObject()) {
                        QString childSection = sectionName.isEmpty() ? key : (sectionName + "." + key);
                        int childSectionId = ensureSection(fileId, childSection, i);
                        if (childSectionId < 0) continue;
                        QJsonObject itemObj = arr[i].toObject();
                        for (auto jt = itemObj.constBegin(); jt != itemObj.constEnd(); ++jt) {
                            QString rawVal = jt.value().isString() ? jt.value().toString() : QString::number(jt.value().toDouble());
                            upsertParameter(fileId, childSectionId, jt.key(), rawVal, "string", 0, 0, dev, jt.key(), QString());
                        }
                    } else {
                        QString rawVal = arr[i].isString() ? arr[i].toString() : QString::number(arr[i].toDouble());
                        upsertParameter(fileId, sectionId, key + "[" + QString::number(i) + "]", rawVal, "string", 0, 0, dev, key, QString());
                    }
                }
            } else {
                QString rawVal = val.isString() ? val.toString() : (val.isBool() ? (val.toBool() ? "true" : "false") : QString::number(val.toDouble()));
                QString vtype = val.isDouble() ? "float" : (val.isBool() ? "bool" : "string");
                double n1 = val.isDouble() ? val.toDouble() : 0;
                upsertParameter(fileId, sectionId, key, rawVal, vtype, n1, 0, dev, key, QString());
            }
        }
    };

    if (doc.isObject()) {
        importObj(doc.object(), QStringLiteral("__root__"), device);
    } else if (doc.isArray()) {
        QJsonArray arr = doc.array();
        for (int i = 0; i < arr.size(); ++i) {
            if (arr[i].isObject()) {
                importObj(arr[i].toObject(), QStringLiteral("__root__"), device);
            }
        }
    }

    QSqlQuery commit(m_db);
    commit.exec("COMMIT");
    return true;
}

// ---- XML 文件导入 ----
bool DatabaseManager::importXmlFile(const QString& filePath, const QString& device)
{
    if (!m_db.isOpen()) return false;
    QFile f(filePath);
    if (!f.exists()) { qWarning() << "xml not found:" << filePath; return false; }
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) { qWarning() << "open failed:" << filePath; return false; }

    QSqlQuery tx(m_db);
    tx.exec("BEGIN");

    int fileId = ensureFile(filePath, QStringLiteral("xml"));
    if (fileId < 0) { tx.exec("ROLLBACK"); f.close(); return false; }

    QXmlStreamReader xml(&f);
    QStringList sectionStack;
    QString currentText;
    int defaultSectionId = ensureSection(fileId, QStringLiteral("__root__"), -1);

    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartElement) {
            QString elemName = xml.name().toString();
            sectionStack.append(elemName);
            currentText.clear();

            // 将元素的属性作为参数导入
            QXmlStreamAttributes attrs = xml.attributes();
            if (!attrs.isEmpty()) {
                QString sectionName = sectionStack.join(".");
                int sectionId = ensureSection(fileId, sectionName, -1);
                if (sectionId < 0) sectionId = defaultSectionId;
                for (const QXmlStreamAttribute& attr : attrs) {
                    QString key = attr.name().toString();
                    QString val = attr.value().toString();
                    upsertParameter(fileId, sectionId, key, val, "string", 0, 0, device, key, QString());
                }
            }
        } else if (token == QXmlStreamReader::Characters) {
            currentText += xml.text().toString();
        } else if (token == QXmlStreamReader::EndElement) {
            QString text = currentText.trimmed();
            if (!text.isEmpty() && !sectionStack.isEmpty()) {
                QString elemName = sectionStack.last();
                QString sectionName;
                // 用父元素路径作为 section
                if (sectionStack.size() > 1) {
                    QStringList parentPath = sectionStack.mid(0, sectionStack.size() - 1);
                    sectionName = parentPath.join(".");
                } else {
                    sectionName = "__root__";
                }
                int sectionId = ensureSection(fileId, sectionName, -1);
                if (sectionId < 0) sectionId = defaultSectionId;

                double n1 = 0;
                QString vtype = "string";
                bool okInt = false;
                int iv = text.toInt(&okInt);
                if (okInt) { vtype = "int"; n1 = iv; }
                else {
                    bool okDouble = false;
                    double dv = text.toDouble(&okDouble);
                    if (okDouble) { vtype = "float"; n1 = dv; }
                }
                upsertParameter(fileId, sectionId, elemName, text, vtype, n1, 0, device, elemName, QString());
            }
            currentText.clear();
            if (!sectionStack.isEmpty()) sectionStack.removeLast();
        }
    }

    if (xml.hasError()) {
        qWarning() << "XML parse error:" << xml.errorString() << filePath;
    }

    f.close();
    QSqlQuery commit(m_db);
    commit.exec("COMMIT");
    return true;
}

bool DatabaseManager::saveConfigEntry(const QString& key, const QString& value, const QString& filePath, const QString& format, const QString& chineseKey)
{
    if (!m_db.isOpen()) return false;

    int fileId = ensureFile(filePath, format.isEmpty() ? QStringLiteral("ini") : format);
    if (fileId < 0) return false;

    int sectionId = ensureSection(fileId, QStringLiteral("__default__"), -1);
    if (sectionId < 0) return false;

    return upsertParameter(fileId, sectionId, key, value, QStringLiteral("string"), 0.0, 0.0, QString(), chineseKey, QString());
}

QVariantList DatabaseManager::listTranslations()
{
    QVariantList list;
    if (!m_db.isOpen()) return list;
    QSqlQuery q(m_db);
    if (!q.exec("SELECT key, chinese FROM translations ORDER BY key")) return list;
    while (q.next()) {
        QVariantMap m;
        m["key"] = q.value(0).toString();
        m["chinese"] = q.value(1).toString();
        list.append(m);
    }
    return list;
}

bool DatabaseManager::setTranslation(const QString& key, const QString& chinese)
{
    if (!m_db.isOpen()) return false;
    QSqlQuery q(m_db);
    q.prepare(R"(INSERT INTO translations(key, chinese) VALUES(:k, :c) ON CONFLICT(key) DO UPDATE SET chinese=excluded.chinese)" );
    q.bindValue(":k", key);
    q.bindValue(":c", chinese);
    if (!q.exec()) {
        qWarning() << "Failed to set translation:" << q.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::applyTranslationsToParameters()
{
    if (!m_db.isOpen()) return false;
    QSqlQuery q(m_db);
    bool ok = q.exec(R"(
        UPDATE parameters SET chinese_name = (
            SELECT chinese FROM translations WHERE translations.key = parameters.key
        ) WHERE EXISTS (
            SELECT 1 FROM translations WHERE translations.key = parameters.key
        );
    )");
    if (!ok) {
        qWarning() << "apply translations failed:" << q.lastError().text();
    }
    return ok;
}

QVariantList DatabaseManager::searchParameters(const QString& query, int mode, const QString& formatFilter)
{
    Q_UNUSED(mode);
    QVariantList out;
    if (!m_db.isOpen()) return out;
    QSqlQuery q(m_db);

    // 构建格式过滤条件
    bool hasFormatFilter = !formatFilter.isEmpty() && formatFilter.toLower() != "all";
    QString formatCondition;
    if (hasFormatFilter) {
        formatCondition = " AND f.format = :fmt";
    }

    if (m_useFts5) {
        QString qstr = query.trimmed();
        if (qstr.isEmpty()) return out;

        // 对输入进行分词，并对每个 token 使用前缀匹配（token*），以便前缀搜索生效。
        QStringList tokens = qstr.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        bool useLikeFallback = false;
        for (const QString &t : tokens) {
            if (t.length() < 3) { useLikeFallback = true; break; }
        }

        if (!useLikeFallback) {
            for (int i = 0; i < tokens.size(); ++i) tokens[i] = tokens[i] + "*";
            QString match = tokens.join(' ');

            QString sql = "SELECT p.key, p.raw_value, p.chinese_name, p.device, f.path, f.format FROM parameters p JOIN files f ON p.file_id=f.id WHERE p.id IN (SELECT rowid FROM parameters_fts WHERE parameters_fts MATCH :m)" + formatCondition + " LIMIT 500";
            q.prepare(sql);
            q.bindValue(":m", match);
            if (hasFormatFilter) q.bindValue(":fmt", formatFilter.toLower());
            if (!q.exec()) {
                useLikeFallback = true;
            } else {
                bool found = false;
                while (q.next()) {
                    found = true;
                    QVariantMap m;
                    m["key"] = q.value(0).toString();
                    m["value"] = q.value(1).toString();
                    m["chinese"] = q.value(2).toString();
                    m["device"] = q.value(3).toString();
                    m["filePath"] = q.value(4).toString();
                    m["format"] = q.value(5).toString();
                    out.append(m);
                }
                if (found) return out;
                useLikeFallback = true;
            }
        }
    }

    // LIKE 模糊匹配回退逻辑
    // Escape LIKE wildcards in user input
    QString escaped = query;
    escaped.replace(QLatin1String("\\"), QLatin1String("\\\\"));
    escaped.replace(QLatin1String("%"), QLatin1String("\\%"));
    escaped.replace(QLatin1String("_"), QLatin1String("\\_"));
    QString like = QString("%") + escaped + "%";
    QString sql = "SELECT p.key, p.raw_value, p.chinese_name, p.device, f.path, f.format FROM parameters p JOIN files f ON p.file_id=f.id WHERE (p.key LIKE :l ESCAPE '\\' OR p.raw_value LIKE :l ESCAPE '\\' OR p.chinese_name LIKE :l ESCAPE '\\' OR p.device LIKE :l ESCAPE '\\')" + formatCondition + " LIMIT 500";
    q.prepare(sql);
    q.bindValue(":l", like);
    if (hasFormatFilter) q.bindValue(":fmt", formatFilter.toLower());
    if (!q.exec()) return out;
    while (q.next()) {
        QVariantMap m;
        m["key"] = q.value(0).toString();
        m["value"] = q.value(1).toString();
        m["chinese"] = q.value(2).toString();
        m["device"] = q.value(3).toString();
        m["filePath"] = q.value(4).toString();
        m["format"] = q.value(5).toString();
        out.append(m);
    }
    return out;
}

QStringList DatabaseManager::listAllKeys()
{
    QStringList out;
    if (!m_db.isOpen()) return out;
    QSqlQuery q(m_db);
    if (!q.exec("SELECT DISTINCT key FROM parameters ORDER BY key")) return out;
    while (q.next()) {
        out.append(q.value(0).toString());
    }
    return out;
}

QVariantList DatabaseManager::listFiles()
{
    QVariantList results;
    if (!m_db.isOpen()) {
        qWarning() << "Database not open in listFiles";
        return results;
    }

    QSqlQuery query(m_db);
    QString sql = "SELECT path, format FROM files ORDER BY path ASC";
    if (!query.exec(sql)) {
        qWarning() << "listFiles query failed:" << query.lastError().text();
        return results;
    }

    while (query.next()) {
        QVariantMap m;
        m["path"] = query.value(0).toString();
        m["format"] = query.value(1).toString();
        results.append(m);
    }

    return results;
}

DatabaseManager* DatabaseManager::instance()
{
    return s_instance;
}

// ---- 修改记录 ----
bool DatabaseManager::addChangeLog(const QString& filePath, const QString& key, const QString& oldValue, const QString& newValue)
{
    if (!m_db.isOpen()) return false;
    if (oldValue == newValue) return true; // 没有实际变化
    QSqlQuery q(m_db);
    q.prepare("INSERT INTO change_log (file_path, key, old_value, new_value) VALUES (?, ?, ?, ?)");
    q.addBindValue(filePath);
    q.addBindValue(key);
    q.addBindValue(oldValue);
    q.addBindValue(newValue);
    if (!q.exec()) {
        qWarning() << "addChangeLog failed:" << q.lastError().text();
        return false;
    }
    return true;
}

QVariantList DatabaseManager::getChangeLogs(int limit)
{
    QVariantList results;
    if (!m_db.isOpen()) return results;
    QSqlQuery q(m_db);
    q.prepare("SELECT file_path, key, old_value, new_value, changed_at FROM change_log ORDER BY changed_at DESC LIMIT ?");
    q.addBindValue(limit);
    if (!q.exec()) {
        qWarning() << "getChangeLogs failed:" << q.lastError().text();
        return results;
    }
    while (q.next()) {
        QVariantMap m;
        m["filePath"] = q.value(0).toString();
        m["key"] = q.value(1).toString();
        m["oldValue"] = q.value(2).toString();
        m["newValue"] = q.value(3).toString();
        m["changedAt"] = q.value(4).toString();
        results.append(m);
    }
    return results;
}

QVariantList DatabaseManager::getChangeLogsForFile(const QString& filePath, int limit)
{
    QVariantList results;
    if (!m_db.isOpen()) return results;
    QSqlQuery q(m_db);
    q.prepare("SELECT file_path, key, old_value, new_value, changed_at FROM change_log WHERE file_path = ? ORDER BY changed_at DESC LIMIT ?");
    q.addBindValue(filePath);
    q.addBindValue(limit);
    if (!q.exec()) {
        qWarning() << "getChangeLogsForFile failed:" << q.lastError().text();
        return results;
    }
    while (q.next()) {
        QVariantMap m;
        m["filePath"] = q.value(0).toString();
        m["key"] = q.value(1).toString();
        m["oldValue"] = q.value(2).toString();
        m["newValue"] = q.value(3).toString();
        m["changedAt"] = q.value(4).toString();
        results.append(m);
    }
    return results;
}
