#include "configdiff.h"
#include "databasemanager.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QXmlStreamReader>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QDateTime>
#include <QDebug>

ConfigDiff::ConfigDiff(QObject* parent)
    : QObject(parent)
{
}

ConfigDiff::~ConfigDiff()
{
}

QVariantList ConfigDiff::compareFiles(const QString& file1Path, const QString& file2Path)
{
    QVariantList config1 = parseConfigFile(file1Path);
    QVariantList config2 = parseConfigFile(file2Path);
    
    if (config1.isEmpty() && config2.isEmpty()) {
        emit errorOccurred(tr("无法解析配置文件"));
        return QVariantList();
    }
    
    m_lastFile1 = file1Path;
    m_lastFile2 = file2Path;
    m_diffResults = compareConfigs(config1, config2);
    emit diffResultsChanged();
    
    return m_diffResults;
}

QVariantList ConfigDiff::compareWithDatabase(const QString& filePath)
{
    QVariantList fileConfig = parseConfigFile(filePath);
    
    DatabaseManager* db = DatabaseManager::instance();
    if (!db) {
        emit errorOccurred(tr("数据库未初始化"));
        return QVariantList();
    }
    
    QVariantList dbConfig;
    QString format = detectFormat(filePath);
    QFileInfo fi(filePath);
    QString fileName = fi.fileName();
    
    QVariantList allParams = db->searchParameters("", 1, format);
    for (const QVariant& param : allParams) {
        QVariantMap p = param.toMap();
        if (p["filePath"].toString().contains(fileName)) {
            QVariantMap entry;
            entry["key"] = p["key"];
            entry["value"] = p["value"];
            entry["section"] = p["section"];
            dbConfig.append(entry);
        }
    }
    
    m_lastFile1 = filePath;
    m_lastFile2 = "database:" + fileName;
    m_diffResults = compareConfigs(fileConfig, dbConfig);
    emit diffResultsChanged();
    
    return m_diffResults;
}

QVariantList ConfigDiff::compareConfigs(const QVariantList& config1, const QVariantList& config2)
{
    QVariantList results;
    QHash<QString, QVariantMap> map1;
    QHash<QString, QVariantMap> map2;
    
    for (const QVariant& item : config1) {
        QVariantMap entry = item.toMap();
        QString key = entry["section"].toString() + "/" + entry["key"].toString();
        map1[key] = entry;
    }
    
    for (const QVariant& item : config2) {
        QVariantMap entry = item.toMap();
        QString key = entry["section"].toString() + "/" + entry["key"].toString();
        map2[key] = entry;
    }
    
    QSet<QString> allKeys;
    for (const QString& key : map1.keys()) allKeys.insert(key);
    for (const QString& key : map2.keys()) allKeys.insert(key);
    
    for (const QString& key : allKeys) {
        QVariantMap result;
        QStringList parts = key.split("/");
        QString section = parts.size() > 1 ? parts[0] : "";
        QString configKey = parts.size() > 1 ? parts.mid(1).join("/") : key;
        
        result["key"] = configKey;
        result["section"] = section;
        result["fullKey"] = key;
        
        bool inMap1 = map1.contains(key);
        bool inMap2 = map2.contains(key);
        
        if (inMap1 && !inMap2) {
            result["changeType"] = "removed";
            result["oldValue"] = map1[key]["value"].toString();
            result["newValue"] = "";
        } else if (!inMap1 && inMap2) {
            result["changeType"] = "added";
            result["oldValue"] = "";
            result["newValue"] = map2[key]["value"].toString();
        } else {
            QString val1 = map1[key]["value"].toString();
            QString val2 = map2[key]["value"].toString();
            
            if (val1 != val2) {
                result["changeType"] = "modified";
                result["oldValue"] = val1;
                result["newValue"] = val2;
            } else {
                result["changeType"] = "unchanged";
                result["oldValue"] = val1;
                result["newValue"] = val2;
            }
        }
        
        results.append(result);
    }
    
    return results;
}

QVariantList ConfigDiff::compareSnapshots(const QString& filePath, const QString& snapshot1, const QString& snapshot2)
{
    QString snap1Path = getSnapshotPath(filePath, snapshot1);
    QString snap2Path = getSnapshotPath(filePath, snapshot2);
    
    if (!QFile::exists(snap1Path) || !QFile::exists(snap2Path)) {
        emit errorOccurred(tr("快照不存在"));
        return QVariantList();
    }
    
    return compareFiles(snap1Path, snap2Path);
}

bool ConfigDiff::createSnapshot(const QString& filePath)
{
    QFileInfo fi(filePath);
    if (!fi.exists()) {
        emit errorOccurred(tr("文件不存在"));
        return false;
    }
    
    QString snapshotsDir = getSnapshotsDir();
    QDir().mkpath(snapshotsDir);
    
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString snapshotPath = getSnapshotPath(filePath, timestamp);
    
    if (QFile::copy(filePath, snapshotPath)) {
        emit snapshotCreated(filePath);
        qDebug() << "[ConfigDiff] Created snapshot:" << snapshotPath;
        return true;
    }
    
    emit errorOccurred(tr("创建快照失败"));
    return false;
}

QVariantList ConfigDiff::listSnapshots(const QString& filePath)
{
    QVariantList snapshots;
    QString snapshotsDir = getSnapshotsDir();
    QFileInfo fi(filePath);
    QString baseName = fi.completeBaseName();
    QString suffix = fi.suffix();
    
    QDir dir(snapshotsDir);
    QStringList filters;
    filters << baseName + "_*." + suffix;
    QStringList files = dir.entryList(filters, QDir::Files, QDir::Time | QDir::Reversed);
    
    for (const QString& file : files) {
        QRegularExpression re(R"((\d{8}_\d{6}))");
        QRegularExpressionMatch match = re.match(file);
        if (match.hasMatch()) {
            QString timestamp = match.captured(1);
            QDateTime dt = QDateTime::fromString(timestamp, "yyyyMMdd_HHmmss");
            
            QVariantMap snapshot;
            snapshot["fileName"] = file;
            snapshot["timestamp"] = timestamp;
            snapshot["displayTime"] = dt.toString("yyyy-MM-dd HH:mm:ss");
            snapshot["path"] = snapshotsDir + "/" + file;
            snapshots.append(snapshot);
        }
    }
    
    return snapshots;
}

bool ConfigDiff::deleteSnapshot(const QString& filePath, const QString& snapshotTime)
{
    QString snapshotPath = getSnapshotPath(filePath, snapshotTime);
    
    if (QFile::remove(snapshotPath)) {
        qDebug() << "[ConfigDiff] Deleted snapshot:" << snapshotPath;
        return true;
    }
    
    emit errorOccurred(tr("删除快照失败"));
    return false;
}

bool ConfigDiff::restoreSnapshot(const QString& filePath, const QString& snapshotTime)
{
    QString snapshotPath = getSnapshotPath(filePath, snapshotTime);
    
    if (!QFile::exists(snapshotPath)) {
        emit errorOccurred(tr("快照不存在"));
        return false;
    }
    
    QFile::remove(filePath);
    
    if (QFile::copy(snapshotPath, filePath)) {
        emit snapshotRestored(filePath);
        qDebug() << "[ConfigDiff] Restored snapshot:" << snapshotPath << "to" << filePath;
        return true;
    }
    
    emit errorOccurred(tr("恢复快照失败"));
    return false;
}

QString ConfigDiff::generateDiffReport(const QString& format)
{
    QString report;
    
    if (format == "json") {
        QJsonArray arr;
        for (const QVariant& item : m_diffResults) {
            arr.append(QJsonObject::fromVariantMap(item.toMap()));
        }
        report = QJsonDocument(arr).toJson(QJsonDocument::Indented);
    } else if (format == "markdown") {
        report = "# 配置对比报告\n\n";
        report += QString("**文件 1**: %1\n\n").arg(m_lastFile1);
        report += QString("**文件 2**: %1\n\n").arg(m_lastFile2);
        report += QString("**统计**: 新增 %1, 删除 %2, 修改 %3, 未变 %4\n\n")
            .arg(addedCount()).arg(removedCount()).arg(modifiedCount()).arg(unchangedCount());
        
        report += "## 修改项\n\n";
        for (const QVariant& item : m_diffResults) {
            QVariantMap entry = item.toMap();
            if (entry["changeType"] == "modified") {
                report += QString("- `%1`: `%2` → `%3`\n")
                    .arg(entry["fullKey"].toString())
                    .arg(entry["oldValue"].toString())
                    .arg(entry["newValue"].toString());
            }
        }
        
        report += "\n## 新增项\n\n";
        for (const QVariant& item : m_diffResults) {
            QVariantMap entry = item.toMap();
            if (entry["changeType"] == "added") {
                report += QString("- `%1` = `%2`\n")
                    .arg(entry["fullKey"].toString())
                    .arg(entry["newValue"].toString());
            }
        }
        
        report += "\n## 删除项\n\n";
        for (const QVariant& item : m_diffResults) {
            QVariantMap entry = item.toMap();
            if (entry["changeType"] == "removed") {
                report += QString("- `%1` (原值: `%2`)\n")
                    .arg(entry["fullKey"].toString())
                    .arg(entry["oldValue"].toString());
            }
        }
    } else {
        report = QString("=== 配置对比报告 ===\n");
        report += QString("文件 1: %1\n").arg(m_lastFile1);
        report += QString("文件 2: %1\n").arg(m_lastFile2);
        report += QString("统计: 新增 %1, 删除 %2, 修改 %3, 未变 %4\n\n")
            .arg(addedCount()).arg(removedCount()).arg(modifiedCount()).arg(unchangedCount());
        
        for (const QVariant& item : m_diffResults) {
            QVariantMap entry = item.toMap();
            QString type = entry["changeType"].toString();
            
            if (type != "unchanged") {
                report += QString("[%1] %2\n").arg(type.toUpper(), entry["fullKey"].toString());
                if (type == "modified") {
                    report += QString("  - %1 -> %2\n").arg(entry["oldValue"].toString(), entry["newValue"].toString());
                } else if (type == "added") {
                    report += QString("  + %1\n").arg(entry["newValue"].toString());
                } else if (type == "removed") {
                    report += QString("  - %1\n").arg(entry["oldValue"].toString());
                }
            }
        }
    }
    
    return report;
}

bool ConfigDiff::exportDiffReport(const QString& outputPath, const QString& format)
{
    QString report = generateDiffReport(format);
    
    QFile file(outputPath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << report;
        file.close();
        return true;
    }
    
    emit errorOccurred(tr("导出报告失败"));
    return false;
}

QVariantList ConfigDiff::getFilteredResults(const QString& changeType)
{
    QVariantList filtered;
    for (const QVariant& item : m_diffResults) {
        QVariantMap entry = item.toMap();
        if (entry["changeType"] == changeType) {
            filtered.append(entry);
        }
    }
    return filtered;
}

QVariantMap ConfigDiff::getDiffStatistics()
{
    QVariantMap stats;
    stats["total"] = m_diffResults.size();
    stats["added"] = addedCount();
    stats["removed"] = removedCount();
    stats["modified"] = modifiedCount();
    stats["unchanged"] = unchangedCount();
    stats["file1"] = m_lastFile1;
    stats["file2"] = m_lastFile2;
    return stats;
}

int ConfigDiff::addedCount() const
{
    int count = 0;
    for (const QVariant& item : m_diffResults) {
        if (item.toMap()["changeType"] == "added") count++;
    }
    return count;
}

int ConfigDiff::removedCount() const
{
    int count = 0;
    for (const QVariant& item : m_diffResults) {
        if (item.toMap()["changeType"] == "removed") count++;
    }
    return count;
}

int ConfigDiff::modifiedCount() const
{
    int count = 0;
    for (const QVariant& item : m_diffResults) {
        if (item.toMap()["changeType"] == "modified") count++;
    }
    return count;
}

int ConfigDiff::unchangedCount() const
{
    int count = 0;
    for (const QVariant& item : m_diffResults) {
        if (item.toMap()["changeType"] == "unchanged") count++;
    }
    return count;
}

QVariantList ConfigDiff::parseConfigFile(const QString& filePath)
{
    QString format = detectFormat(filePath);
    
    if (format == "json") {
        return parseJsonFile(filePath);
    } else if (format == "xml") {
        return parseXmlFile(filePath);
    } else {
        return parseIniFile(filePath);
    }
}

QString ConfigDiff::detectFormat(const QString& filePath)
{
    if (filePath.endsWith(".json", Qt::CaseInsensitive)) return "json";
    if (filePath.endsWith(".xml", Qt::CaseInsensitive)) return "xml";
    return "ini";
}

QVariantList ConfigDiff::parseIniFile(const QString& filePath)
{
    QVariantList entries;
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return entries;
    }
    
    QTextStream in(&file);
    QString currentSection;
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        
        if (line.isEmpty() || line.startsWith(';') || line.startsWith('#')) {
            continue;
        }
        
        if (line.startsWith('[') && line.endsWith(']')) {
            currentSection = line.mid(1, line.size() - 2).trimmed();
            continue;
        }
        
        int eqPos = line.indexOf('=');
        if (eqPos > 0) {
            QString key = line.left(eqPos).trimmed();
            QString value = line.mid(eqPos + 1).trimmed();
            
            QVariantMap entry;
            entry["key"] = key;
            entry["value"] = value;
            entry["section"] = currentSection;
            entries.append(entry);
        }
    }
    
    file.close();
    return entries;
}

QVariantList ConfigDiff::parseJsonFile(const QString& filePath)
{
    QVariantList entries;
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly)) {
        return entries;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    
    if (error.error != QJsonParseError::NoError) {
        return entries;
    }
    
    std::function<void(const QJsonObject&, const QString&)> parseObject;
    parseObject = [&](const QJsonObject& obj, const QString& prefix) {
        for (auto it = obj.begin(); it != obj.end(); ++it) {
            QString key = prefix.isEmpty() ? it.key() : prefix + "/" + it.key();
            
            if (it.value().isObject()) {
                parseObject(it.value().toObject(), key);
            } else {
                QVariantMap entry;
                entry["key"] = it.key();
                entry["value"] = it.value().toVariant().toString();
                entry["section"] = prefix;
                entries.append(entry);
            }
        }
    };
    
    if (doc.isObject()) {
        parseObject(doc.object(), "");
    } else if (doc.isArray()) {
        int idx = 0;
        for (const QJsonValue& val : doc.array()) {
            if (val.isObject()) {
                parseObject(val.toObject(), QString("[%1]").arg(idx));
            }
            idx++;
        }
    }
    
    return entries;
}

QVariantList ConfigDiff::parseXmlFile(const QString& filePath)
{
    QVariantList entries;
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly)) {
        return entries;
    }
    
    QXmlStreamReader xml(&file);
    QString currentSection;
    
    while (!xml.atEnd()) {
        xml.readNext();
        
        if (xml.isStartElement()) {
            QString name = xml.name().toString();
            
            if (xml.attributes().hasAttribute("key")) {
                QString key = xml.attributes().value("key").toString();
                QString value = xml.readElementText();
                
                QVariantMap entry;
                entry["key"] = key;
                entry["value"] = value;
                entry["section"] = currentSection;
                entries.append(entry);
            } else {
                currentSection = name;
            }
        }
    }
    
    file.close();
    return entries;
}

QString ConfigDiff::getSnapshotPath(const QString& filePath, const QString& snapshotTime)
{
    QFileInfo fi(filePath);
    QString baseName = fi.completeBaseName();
    QString suffix = fi.suffix();
    return getSnapshotsDir() + "/" + baseName + "_" + snapshotTime + "." + suffix;
}

QString ConfigDiff::getSnapshotsDir()
{
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    return dataDir + "/snapshots";
}
