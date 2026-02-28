#include "configparser.h"
#include <QMutexLocker>
#include <QCryptographicHash>

ConfigParser::ConfigParser(QObject *parent) : QObject(parent)
{
}

ConfigParser::~ConfigParser()
{
    QMutexLocker locker(&m_entriesMutex);
    m_allEntries.clear();  // QSharedPointer 会自动释放内存
}

void ConfigParser::loadConfigFiles(const QStringList& filePaths)
{
    QMutexLocker locker(&m_entriesMutex);
    m_allEntries.clear();

    QtConcurrent::run([=]() {
        QStringList allFiles;
        for (const QString& path : filePaths) {
            QFileInfo info(path);
            if (info.isDir()) {
                allFiles += getConfigFiles(path);
            } else if (info.isFile()) {
                allFiles << path;
            }
        }

        int total = allFiles.size();
        int current = 0;

        for (const QString& filePath : allFiles) {
            QFileInfo info(filePath);
            bool success = false;
            if (info.suffix().toLower() == "ini") {
                success = parseIniFile(filePath);
            } else if (info.suffix().toLower() == "json") {
                success = parseJsonFile(filePath);
            }

            if (!success) {
                emit errorOccurred(QString("Failed to parse: %1").arg(filePath));
            }

            current++;
            emit loadProgress((current * 100) / total);
        }

        emit loadFinished();
    });
}

QList<QSharedPointer<ConfigEntry>> ConfigParser::search(const QString& keyword)
{
    QMutexLocker locker(&m_entriesMutex);
    QList<QSharedPointer<ConfigEntry>> results;
    
    if (keyword.isEmpty()) {
        return m_allEntries;
    }

    for (const auto& entry : m_allEntries) {
        if (entry->key().contains(keyword, Qt::CaseInsensitive) ||
            entry->chineseKey().contains(keyword, Qt::CaseInsensitive) ||
            entry->value().contains(keyword, Qt::CaseInsensitive)) {
            results << entry;
        }
    }

    return results;
}

bool ConfigParser::parseIniFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.exists()) {
        emit errorOccurred(QString("File not found: %1").arg(filePath));
        return false;
    }
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit errorOccurred(QString("Cannot open file: %1 - %2").arg(filePath, file.errorString()));
        return false;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");  // 支持中文
    QString section;
    int lineNum = 0;

    {
        QMutexLocker locker(&m_entriesMutex);
        
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            lineNum++;
            
            if (line.isEmpty() || line.startsWith(';') || line.startsWith('#')) {
                continue;
            }

            if (line.startsWith('[') && line.endsWith(']')) {
                section = line.mid(1, line.size() - 2).trimmed();
                continue;
            }

            int eqPos = line.indexOf('=');
            if (eqPos > 0) {
                QString key = line.left(eqPos).trimmed();
                QString value = line.mid(eqPos + 1).trimmed();

                auto entry = QSharedPointer<ConfigEntry>::create();
                entry->setKey(section.isEmpty() ? key : section + "." + key);
                entry->setChineseKey(key);
                entry->setValue(value);
                entry->setFilePath(filePath);

                m_allEntries << entry;
            }
        }
    }

    file.close();
    return true;
}

bool ConfigParser::parseJsonFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.exists()) {
        emit errorOccurred(QString("File not found: %1").arg(filePath));
        return false;
    }
    
    if (!file.open(QIODevice::ReadOnly)) {
        emit errorOccurred(QString("Cannot open file: %1 - %2").arg(filePath, file.errorString()));
        return false;
    }

    QByteArray data = file.readAll();
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        emit errorOccurred(QString("JSON parse error in %1: %2").arg(filePath, parseError.errorString()));
        return false;
    }

    QMutexLocker locker(&m_entriesMutex);
    
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        for (auto it = obj.begin(); it != obj.end(); ++it) {
            auto entry = QSharedPointer<ConfigEntry>::create();
            entry->setKey(it.key());
            entry->setChineseKey(it.key());
            entry->setValue(it.value().toVariant().toString());
            entry->setFilePath(filePath);

            m_allEntries << entry;
        }
    } else if (doc.isArray()) {
        QJsonArray arr = doc.array();
        for (int i = 0; i < arr.size(); ++i) {
            auto entry = QSharedPointer<ConfigEntry>::create();
            entry->setKey(QString("item_%1").arg(i));
            entry->setChineseKey(QString("项目_%1").arg(i));
            entry->setValue(arr[i].toVariant().toString());
            entry->setFilePath(filePath);

            m_allEntries << entry;
        }
    }

    file.close();
    return true;
}

QStringList ConfigParser::getConfigFiles(const QString& dirPath)
{
    QStringList files;
    QDir dir(dirPath);
    
    if (!dir.exists()) {
        return files;
    }
    
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setNameFilters(QStringList() << "*.ini" << "*.json");

    QFileInfoList list = dir.entryInfoList();
    for (const QFileInfo& info : list) {
        files << info.absoluteFilePath();
    }

    // 递归子目录
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList dirList = dir.entryInfoList();
    for (const QFileInfo& info : dirList) {
        files += getConfigFiles(info.absoluteFilePath());
    }

    return files;
}
