#include "configparser.h"

ConfigParser::ConfigParser(QObject *parent) : QObject(parent)
{
}

void ConfigParser::loadConfigFiles(const QStringList& filePaths)
{
    // 清空原有数据
    qDeleteAll(m_allEntries);
    m_allEntries.clear();

    // 异步加载文件（Qt 5.15 原生 QtConcurrent）
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
            if (info.suffix().toLower() == "ini") {
                parseIniFile(filePath);
            } else if (info.suffix().toLower() == "json") {
                parseJsonFile(filePath);
            }

            current++;
            emit loadProgress((current * 100) / total);
        }

        emit loadFinished();
    });
}

QList<ConfigEntry*> ConfigParser::search(const QString& keyword)
{
    QList<ConfigEntry*> results;
    if (keyword.isEmpty()) {
        return m_allEntries;
    }

    for (ConfigEntry* entry : m_allEntries) {
        if (entry->key().contains(keyword, Qt::CaseInsensitive) ||
            entry->chineseKey().contains(keyword, Qt::CaseInsensitive) ||
            entry->value().contains(keyword, Qt::CaseInsensitive)) {
            results << entry;
        }
    }

    return results;
}

void ConfigParser::parseIniFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    QString section;
        
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
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

            ConfigEntry* entry = new ConfigEntry();
                entry->setKey(section.isEmpty() ? key : section + "." + key);
                entry->setChineseKey(key);
                entry->setValue(value);
                entry->setFilePath(filePath);

                m_allEntries << entry;
            }
        }

    file.close();
}

void ConfigParser::parseJsonFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        // 简单解析一级JSON节点
        for (auto it = obj.begin(); it != obj.end(); ++it) {
            ConfigEntry* entry = new ConfigEntry();
            entry->setKey(it.key());
            entry->setChineseKey(it.key());
            entry->setValue(it.value().toString());
            entry->setFilePath(filePath);

            m_allEntries << entry;
        }
    }

    file.close();
}

// 实现递归遍历目录方法
QStringList ConfigParser::getConfigFiles(const QString& dirPath)
{
    QStringList files;
    QDir dir(dirPath);
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
