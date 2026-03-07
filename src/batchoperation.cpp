#include "batchoperation.h"
#include "databasemanager.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QDateTime>
#include <QtConcurrent>
#include <QDebug>

BatchOperation::BatchOperation(QObject* parent)
    : QObject(parent)
    , m_totalOperations(0)
    , m_completedOperations(0)
    , m_failedOperations(0)
    , m_isRunning(false)
{
}

BatchOperation::~BatchOperation()
{
}

bool BatchOperation::batchUpdateValues(const QVariantList& entries)
{
    if (entries.isEmpty()) {
        emit operationCompleted("batchUpdate", false, tr("没有要更新的条目"));
        return false;
    }
    
    m_isRunning = true;
    m_totalOperations = entries.size();
    m_completedOperations = 0;
    m_failedOperations = 0;
    emit runningChanged(true);
    
    QHash<QString, QVariantList> fileEntries;
    
    for (const QVariant& item : entries) {
        QVariantMap entry = item.toMap();
        QString filePath = entry["filePath"].toString();
        fileEntries[filePath].append(entry);
    }
    
    int successCount = 0;
    int failCount = 0;
    
    for (auto it = fileEntries.begin(); it != fileEntries.end(); ++it) {
        QString filePath = it.key();
        QVariantList fileData = readConfigFile(filePath);
        QVariantList updatedData;
        QHash<QString, QString> updateMap;
        
        for (const QVariant& e : it.value()) {
            QVariantMap entry = e.toMap();
            QString section = entry["section"].toString();
            QString key = entry["key"].toString();
            QString fullKey = section + "/" + key;
            updateMap[fullKey] = entry["value"].toString();
        }
        
        for (const QVariant& item : fileData) {
            QVariantMap entry = item.toMap();
            QString section = entry["section"].toString();
            QString key = entry["key"].toString();
            QString fullKey = section + "/" + key;
            
            if (updateMap.contains(fullKey)) {
                entry["value"] = updateMap[fullKey];
            }
            updatedData.append(entry);
        }
        
        m_currentOperation = tr("更新文件: ") + filePath;
        emit currentOperationChanged(m_currentOperation);
        
        QString format = detectFormat(filePath);
        bool success = false;
        
        backupFile(filePath);
        
        if (format == "json") {
            success = writeJsonFile(filePath, updatedData);
        } else if (format == "xml") {
            success = writeXmlFile(filePath, updatedData);
        } else {
            success = writeIniFile(filePath, updatedData);
        }
        
        if (success) {
            successCount++;
            m_completedOperations++;
            logOperation("update", filePath, true, "");
        } else {
            failCount++;
            m_failedOperations++;
            logOperation("update", filePath, false, tr("写入失败"));
        }
        
        emit progressChanged(m_completedOperations + m_failedOperations, m_totalOperations);
    }
    
    m_isRunning = false;
    emit runningChanged(false);
    emit batchFinished(successCount, failCount);
    
    return failCount == 0;
}

bool BatchOperation::batchUpdateValue(const QString& key, const QString& newValue, const QStringList& filePaths)
{
    if (filePaths.isEmpty()) {
        return false;
    }
    
    m_isRunning = true;
    m_totalOperations = filePaths.size();
    m_completedOperations = 0;
    m_failedOperations = 0;
    emit runningChanged(true);
    
    int successCount = 0;
    int failCount = 0;
    
    for (const QString& filePath : filePaths) {
        m_currentOperation = tr("更新 %1 在 %2").arg(key, filePath);
        emit currentOperationChanged(m_currentOperation);
        
        backupFile(filePath);
        
        QVariantList entries = readConfigFile(filePath);
        bool found = false;
        
        for (int i = 0; i < entries.size(); ++i) {
            QVariantMap entry = entries[i].toMap();
            if (entry["key"].toString() == key) {
                entry["value"] = newValue;
                entries[i] = entry;
                found = true;
                break;
            }
        }
        
        if (found) {
            QString format = detectFormat(filePath);
            bool success = false;
            
            if (format == "json") {
                success = writeJsonFile(filePath, entries);
            } else if (format == "xml") {
                success = writeXmlFile(filePath, entries);
            } else {
                success = writeIniFile(filePath, entries);
            }
            
            if (success) {
                successCount++;
                m_completedOperations++;
                logOperation("updateValue", filePath, true, key + " = " + newValue);
            } else {
                failCount++;
                m_failedOperations++;
            }
        } else {
            failCount++;
            m_failedOperations++;
            logOperation("updateValue", filePath, false, tr("未找到键: ") + key);
        }
        
        emit progressChanged(m_completedOperations + m_failedOperations, m_totalOperations);
    }
    
    m_isRunning = false;
    emit runningChanged(false);
    emit batchFinished(successCount, failCount);
    
    return failCount == 0;
}

bool BatchOperation::batchDelete(const QStringList& keys, const QString& filePath)
{
    if (keys.isEmpty() || filePath.isEmpty()) {
        return false;
    }
    
    backupFile(filePath);
    
    QVariantList entries = readConfigFile(filePath);
    QVariantList newEntries;
    QSet<QString> keysToDelete(keys.begin(), keys.end());
    
    for (const QVariant& item : entries) {
        QVariantMap entry = item.toMap();
        if (!keysToDelete.contains(entry["key"].toString())) {
            newEntries.append(entry);
        }
    }
    
    QString format = detectFormat(filePath);
    bool success = false;
    
    if (format == "json") {
        success = writeJsonFile(filePath, newEntries);
    } else if (format == "xml") {
        success = writeXmlFile(filePath, newEntries);
    } else {
        success = writeIniFile(filePath, newEntries);
    }
    
    logOperation("delete", filePath, success, keys.join(", "));
    return success;
}

bool BatchOperation::batchAddSection(const QString& sectionName, const QVariantList& entries, const QString& filePath)
{
    if (sectionName.isEmpty() || filePath.isEmpty()) {
        return false;
    }
    
    backupFile(filePath);
    
    QVariantList existingEntries = readConfigFile(filePath);
    
    for (const QVariant& item : entries) {
        QVariantMap entry = item.toMap();
        entry["section"] = sectionName;
        existingEntries.append(entry);
    }
    
    QString format = detectFormat(filePath);
    bool success = false;
    
    if (format == "json") {
        success = writeJsonFile(filePath, existingEntries);
    } else if (format == "xml") {
        success = writeXmlFile(filePath, existingEntries);
    } else {
        success = writeIniFile(filePath, existingEntries);
    }
    
    logOperation("addSection", filePath, success, sectionName);
    return success;
}

bool BatchOperation::batchImport(const QString& sourceDir, const QString& targetDir, const QStringList& filters)
{
    QDir source(sourceDir);
    if (!source.exists()) {
        emit operationCompleted("import", false, tr("源目录不存在"));
        return false;
    }
    
    QDir target(targetDir);
    if (!target.exists()) {
        target.mkpath(".");
    }
    
    QStringList useFilters = filters.isEmpty() ? QStringList{"*.ini", "*.json", "*.xml"} : filters;
    QStringList files;
    
    for (const QString& filter : useFilters) {
        files += source.entryList(QStringList() << filter, QDir::Files);
    }
    
    if (files.isEmpty()) {
        emit operationCompleted("import", false, tr("没有找到匹配的文件"));
        return false;
    }
    
    m_isRunning = true;
    m_totalOperations = files.size();
    m_completedOperations = 0;
    m_failedOperations = 0;
    emit runningChanged(true);
    
    int successCount = 0;
    int failCount = 0;
    
    for (const QString& fileName : files) {
        QString srcPath = source.absoluteFilePath(fileName);
        QString dstPath = target.absoluteFilePath(fileName);
        
        m_currentOperation = tr("导入: ") + fileName;
        emit currentOperationChanged(m_currentOperation);
        
        if (QFile::copy(srcPath, dstPath)) {
            successCount++;
            m_completedOperations++;
            logOperation("import", dstPath, true, srcPath);
        } else {
            failCount++;
            m_failedOperations++;
            logOperation("import", dstPath, false, srcPath);
        }
        
        emit progressChanged(m_completedOperations + m_failedOperations, m_totalOperations);
    }
    
    m_isRunning = false;
    emit runningChanged(false);
    emit batchFinished(successCount, failCount);
    
    return failCount == 0;
}

bool BatchOperation::batchExport(const QStringList& filePaths, const QString& targetDir, const QString& format)
{
    if (filePaths.isEmpty()) {
        return false;
    }
    
    QDir target(targetDir);
    if (!target.exists()) {
        target.mkpath(".");
    }
    
    m_isRunning = true;
    m_totalOperations = filePaths.size();
    m_completedOperations = 0;
    m_failedOperations = 0;
    emit runningChanged(true);
    
    int successCount = 0;
    int failCount = 0;
    
    for (const QString& filePath : filePaths) {
        QFileInfo fi(filePath);
        QString baseName = fi.completeBaseName();
        QString outputPath;
        
        if (format == "csv") {
            outputPath = target.absoluteFilePath(baseName + ".csv");
            m_currentOperation = tr("导出 CSV: ") + baseName;
        } else if (format == "json") {
            outputPath = target.absoluteFilePath(baseName + ".json");
            m_currentOperation = tr("导出 JSON: ") + baseName;
        } else {
            outputPath = target.absoluteFilePath(fi.fileName());
            m_currentOperation = tr("导出: ") + fi.fileName();
        }
        
        emit currentOperationChanged(m_currentOperation);
        
        bool success = false;
        
        if (format == "csv") {
            success = exportToCsv(filePath, outputPath);
        } else if (format == "json") {
            success = exportToJson(filePath, outputPath);
        } else {
            success = QFile::copy(filePath, outputPath);
        }
        
        if (success) {
            successCount++;
            m_completedOperations++;
            logOperation("export", outputPath, true, filePath);
        } else {
            failCount++;
            m_failedOperations++;
            logOperation("export", outputPath, false, filePath);
        }
        
        emit progressChanged(m_completedOperations + m_failedOperations, m_totalOperations);
    }
    
    m_isRunning = false;
    emit runningChanged(false);
    emit batchFinished(successCount, failCount);
    
    return failCount == 0;
}

bool BatchOperation::exportToCsv(const QString& filePath, const QString& outputPath)
{
    QVariantList entries = readConfigFile(filePath);
    if (entries.isEmpty()) {
        return false;
    }
    
    QFile file(outputPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << "Section,Key,Value\n";
    
    for (const QVariant& item : entries) {
        QVariantMap entry = item.toMap();
        QString section = entry["section"].toString();
        QString key = entry["key"].toString();
        QString value = entry["value"].toString();
        
        value.replace("\"", "\"\"");
        
        out << QString("\"%1\",\"%2\",\"%3\"\n")
            .arg(section, key, value);
    }
    
    file.close();
    return true;
}

bool BatchOperation::exportToJson(const QString& filePath, const QString& outputPath)
{
    QVariantList entries = readConfigFile(filePath);
    if (entries.isEmpty()) {
        return false;
    }
    
    QJsonObject root;
    QJsonObject currentSection;
    QString lastSection;
    
    for (const QVariant& item : entries) {
        QVariantMap entry = item.toMap();
        QString section = entry["section"].toString();
        QString key = entry["key"].toString();
        QString value = entry["value"].toString();
        
        if (section != lastSection) {
            if (!lastSection.isEmpty()) {
                root[lastSection] = currentSection;
            }
            currentSection = QJsonObject();
            lastSection = section;
        }
        
        currentSection[key] = value;
    }
    
    if (!lastSection.isEmpty()) {
        root[lastSection] = currentSection;
    }
    
    QFile file(outputPath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    
    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

bool BatchOperation::importFromCsv(const QString& csvPath, const QString& targetFilePath)
{
    QFile file(csvPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    
    QVariantList entries;
    QTextStream in(&file);
    in.setCodec("UTF-8");
    
    bool firstLine = true;
    while (!in.atEnd()) {
        QString line = in.readLine();
        
        if (firstLine) {
            firstLine = false;
            continue;
        }
        
        QStringList parts;
        QString current;
        bool inQuotes = false;
        
        for (int i = 0; i < line.size(); ++i) {
            QChar c = line[i];
            
            if (c == '"') {
                if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                    current += '"';
                    ++i;
                } else {
                    inQuotes = !inQuotes;
                }
            } else if (c == ',' && !inQuotes) {
                parts.append(current);
                current.clear();
            } else {
                current += c;
            }
        }
        parts.append(current);
        
        if (parts.size() >= 3) {
            QVariantMap entry;
            entry["section"] = parts[0];
            entry["key"] = parts[1];
            entry["value"] = parts[2];
            entries.append(entry);
        }
    }
    
    file.close();
    
    if (entries.isEmpty()) {
        return false;
    }
    
    backupFile(targetFilePath);
    
    QString format = detectFormat(targetFilePath);
    if (format == "json") {
        return writeJsonFile(targetFilePath, entries);
    } else if (format == "xml") {
        return writeXmlFile(targetFilePath, entries);
    }
    return writeIniFile(targetFilePath, entries);
}

bool BatchOperation::importFromJson(const QString& jsonPath, const QString& targetFilePath)
{
    QFile file(jsonPath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        return false;
    }
    
    QVariantList entries;
    QJsonObject root = doc.object();
    
    for (auto sectionIt = root.begin(); sectionIt != root.end(); ++sectionIt) {
        QString section = sectionIt.key();
        QJsonObject sectionObj = sectionIt.value().toObject();
        
        for (auto keyIt = sectionObj.begin(); keyIt != sectionObj.end(); ++keyIt) {
            QVariantMap entry;
            entry["section"] = section;
            entry["key"] = keyIt.key();
            entry["value"] = keyIt.value().toVariant().toString();
            entries.append(entry);
        }
    }
    
    backupFile(targetFilePath);
    
    QString format = detectFormat(targetFilePath);
    if (format == "json") {
        return writeJsonFile(targetFilePath, entries);
    } else if (format == "xml") {
        return writeXmlFile(targetFilePath, entries);
    }
    return writeIniFile(targetFilePath, entries);
}

bool BatchOperation::batchReplace(const QString& searchText, const QString& replaceText, const QStringList& keys, const QString& filePath)
{
    if (searchText.isEmpty() || filePath.isEmpty()) {
        return false;
    }
    
    backupFile(filePath);
    
    QVariantList entries = readConfigFile(filePath);
    QSet<QString> keySet(keys.begin(), keys.end());
    bool modified = false;
    
    for (int i = 0; i < entries.size(); ++i) {
        QVariantMap entry = entries[i].toMap();
        
        if (keySet.isEmpty() || keySet.contains(entry["key"].toString())) {
            QString value = entry["value"].toString();
            if (value.contains(searchText)) {
                value.replace(searchText, replaceText);
                entry["value"] = value;
                entries[i] = entry;
                modified = true;
            }
        }
    }
    
    if (!modified) {
        return true;
    }
    
    QString format = detectFormat(filePath);
    if (format == "json") {
        return writeJsonFile(filePath, entries);
    } else if (format == "xml") {
        return writeXmlFile(filePath, entries);
    }
    return writeIniFile(filePath, entries);
}

bool BatchOperation::batchApplyTemplate(const QString& templateFilePath, const QStringList& targetFilePaths)
{
    if (templateFilePath.isEmpty() || targetFilePaths.isEmpty()) {
        return false;
    }
    
    DatabaseManager* db = DatabaseManager::instance();
    if (!db) {
        return false;
    }
    
    m_isRunning = true;
    m_totalOperations = targetFilePaths.size();
    m_completedOperations = 0;
    m_failedOperations = 0;
    emit runningChanged(true);
    
    int successCount = 0;
    int failCount = 0;
    
    for (const QString& targetPath : targetFilePaths) {
        m_currentOperation = tr("应用模板到: ") + targetPath;
        emit currentOperationChanged(m_currentOperation);
        
        backupFile(targetPath);
        
        if (db->importTemplate(templateFilePath, targetPath)) {
            successCount++;
            m_completedOperations++;
            logOperation("applyTemplate", targetPath, true, templateFilePath);
        } else {
            failCount++;
            m_failedOperations++;
            logOperation("applyTemplate", targetPath, false, templateFilePath);
        }
        
        emit progressChanged(m_completedOperations + m_failedOperations, m_totalOperations);
    }
    
    m_isRunning = false;
    emit runningChanged(false);
    emit batchFinished(successCount, failCount);
    
    return failCount == 0;
}

bool BatchOperation::batchSetReadOnly(const QStringList& keys, const QString& filePath, bool readOnly)
{
    DatabaseManager* db = DatabaseManager::instance();
    if (!db) {
        return false;
    }
    
    for (const QString& key : keys) {
        db->setFieldReadOnly(filePath, key, readOnly);
    }
    
    logOperation("setReadOnly", filePath, true, QString::number(keys.size()) + " keys");
    return true;
}

QVariantList BatchOperation::getOperationLog()
{
    return m_operationLog;
}

void BatchOperation::clearOperationLog()
{
    m_operationLog.clear();
}

bool BatchOperation::undoLastOperation()
{
    if (!canUndo()) {
        return false;
    }
    
    QString originalPath = m_lastBackup.keys().first();
    QString backupPath = m_lastBackup[originalPath].toString();
    
    if (QFile::exists(backupPath)) {
        QFile::remove(originalPath);
        if (QFile::copy(backupPath, originalPath)) {
            QFile::remove(backupPath);
            m_lastBackup.clear();
            logOperation("undo", originalPath, true, "");
            return true;
        }
    }
    
    return false;
}

bool BatchOperation::canUndo() const
{
    return !m_lastBackup.isEmpty();
}

bool BatchOperation::writeIniFile(const QString& filePath, const QVariantList& entries)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    out.setCodec("UTF-8");
    
    QHash<QString, QVariantList> sectionMap;
    for (const QVariant& item : entries) {
        QVariantMap entry = item.toMap();
        QString section = entry["section"].toString();
        sectionMap[section].append(entry);
    }
    
    for (auto it = sectionMap.begin(); it != sectionMap.end(); ++it) {
        out << "[" << it.key() << "]\n";
        
        for (const QVariant& item : it.value()) {
            QVariantMap entry = item.toMap();
            out << entry["key"].toString() << "=" << entry["value"].toString() << "\n";
        }
        out << "\n";
    }
    
    file.close();
    return true;
}

bool BatchOperation::writeJsonFile(const QString& filePath, const QVariantList& entries)
{
    QJsonObject root;
    QJsonObject currentSection;
    QString lastSection;
    
    for (const QVariant& item : entries) {
        QVariantMap entry = item.toMap();
        QString section = entry["section"].toString();
        QString key = entry["key"].toString();
        QString value = entry["value"].toString();
        
        if (section != lastSection) {
            if (!lastSection.isEmpty()) {
                root[lastSection] = currentSection;
            }
            currentSection = QJsonObject();
            lastSection = section;
        }
        
        currentSection[key] = value;
    }
    
    if (!lastSection.isEmpty()) {
        root[lastSection] = currentSection;
    }
    
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    
    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

bool BatchOperation::writeXmlFile(const QString& filePath, const QVariantList& entries)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    
    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("config");
    
    QHash<QString, QVariantList> sectionMap;
    for (const QVariant& item : entries) {
        QVariantMap entry = item.toMap();
        QString section = entry["section"].toString();
        sectionMap[section].append(entry);
    }
    
    for (auto it = sectionMap.begin(); it != sectionMap.end(); ++it) {
        xml.writeStartElement(it.key().isEmpty() ? "section" : it.key());
        
        for (const QVariant& item : it.value()) {
            QVariantMap entry = item.toMap();
            xml.writeTextElement(entry["key"].toString(), entry["value"].toString());
        }
        
        xml.writeEndElement();
    }
    
    xml.writeEndElement();
    xml.writeEndDocument();
    file.close();
    return true;
}

QVariantList BatchOperation::readConfigFile(const QString& filePath)
{
    QVariantList entries;
    QString format = detectFormat(filePath);
    
    if (format == "json") {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly)) {
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            file.close();
            
            if (doc.isObject()) {
                QJsonObject root = doc.object();
                for (auto sectionIt = root.begin(); sectionIt != root.end(); ++sectionIt) {
                    QString section = sectionIt.key();
                    QJsonObject sectionObj = sectionIt.value().toObject();
                    
                    for (auto keyIt = sectionObj.begin(); keyIt != sectionObj.end(); ++keyIt) {
                        QVariantMap entry;
                        entry["section"] = section;
                        entry["key"] = keyIt.key();
                        entry["value"] = keyIt.value().toVariant().toString();
                        entries.append(entry);
                    }
                }
            }
        }
    } else if (format == "xml") {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly)) {
            QXmlStreamReader xml(&file);
            QString currentSection;
            
            while (!xml.atEnd()) {
                xml.readNext();
                
                if (xml.isStartElement() && xml.name() != "config") {
                    currentSection = xml.name().toString();
                } else if (xml.isCharacters() && !xml.isWhitespace()) {
                    QString key = "value";
                    QVariantMap entry;
                    entry["section"] = currentSection;
                    entry["key"] = key;
                    entry["value"] = xml.text().toString();
                    entries.append(entry);
                }
            }
            file.close();
        }
    } else {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
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
                    QVariantMap entry;
                    entry["key"] = line.left(eqPos).trimmed();
                    entry["value"] = line.mid(eqPos + 1).trimmed();
                    entry["section"] = currentSection;
                    entries.append(entry);
                }
            }
            file.close();
        }
    }
    
    return entries;
}

QString BatchOperation::detectFormat(const QString& filePath)
{
    if (filePath.endsWith(".json", Qt::CaseInsensitive)) return "json";
    if (filePath.endsWith(".xml", Qt::CaseInsensitive)) return "xml";
    return "ini";
}

void BatchOperation::logOperation(const QString& type, const QString& target, bool success, const QString& message)
{
    QVariantMap log;
    log["type"] = type;
    log["target"] = target;
    log["success"] = success;
    log["message"] = message;
    log["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    
    m_operationLog.prepend(log);
    
    while (m_operationLog.size() > 100) {
        m_operationLog.removeLast();
    }
}

void BatchOperation::backupFile(const QString& filePath)
{
    if (!QFile::exists(filePath)) {
        return;
    }
    
    QString backupDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    QString backupPath = backupDir + "/" + QFileInfo(filePath).fileName() + ".bak";
    
    QFile::remove(backupPath);
    if (QFile::copy(filePath, backupPath)) {
        m_lastBackup.clear();
        m_lastBackup[filePath] = backupPath;
    }
}
