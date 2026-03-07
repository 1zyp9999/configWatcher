#include "configvalidator.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QXmlStreamReader>
#include <QStandardPaths>
#include <QDebug>

ConfigValidator* ConfigValidator::s_instance = nullptr;

ConfigValidator::ConfigValidator(QObject* parent)
    : QObject(parent)
{
    loadBuiltinRules();
    loadSchema(getSchemaPath());
}

ConfigValidator::~ConfigValidator()
{
}

ConfigValidator* ConfigValidator::instance()
{
    if (!s_instance) {
        s_instance = new ConfigValidator();
    }
    return s_instance;
}

int ConfigValidator::errorCount() const
{
    int count = 0;
    for (const QVariant& item : m_results) {
        if (item.toMap()["severity"].toInt() == Error) count++;
    }
    return count;
}

int ConfigValidator::warningCount() const
{
    int count = 0;
    for (const QVariant& item : m_results) {
        if (item.toMap()["severity"].toInt() == Warning) count++;
    }
    return count;
}

int ConfigValidator::infoCount() const
{
    int count = 0;
    for (const QVariant& item : m_results) {
        if (item.toMap()["severity"].toInt() == Info) count++;
    }
    return count;
}

QVariantList ConfigValidator::validateFile(const QString& filePath)
{
    m_results.clear();
    m_lastValidatedFile = filePath;
    
    if (!QFile::exists(filePath)) {
        addResult("", Error, tr("文件不存在: ") + filePath);
        emit validationResultsChanged();
        return m_results;
    }
    
    QVariantList config = parseConfigFile(filePath);
    
    if (config.isEmpty()) {
        addResult("", Warning, tr("配置文件为空或无法解析"));
        emit validationResultsChanged();
        return m_results;
    }
    
    return validateConfig(config, filePath);
}

QVariantList ConfigValidator::validateConfig(const QVariantList& config, const QString& filePath)
{
    m_results.clear();
    m_lastValidatedFile = filePath;
    
    QSet<QString> foundKeys;
    QHash<QString, QString> keyValues;
    
    for (const QVariant& item : config) {
        QVariantMap entry = item.toMap();
        QString key = entry["key"].toString();
        QString value = entry["value"].toString();
        QString section = entry["section"].toString();
        QString fullKey = section.isEmpty() ? key : section + "/" + key;
        
        foundKeys.insert(fullKey);
        keyValues[fullKey] = value;
        
        QVariantList keyResults = validateKey(key, value, section);
        for (const QVariant& result : keyResults) {
            m_results.append(result);
        }
    }
    
    for (auto it = m_rules.begin(); it != m_rules.end(); ++it) {
        const ValidationRule& rule = it.value();
        
        if (rule.required) {
            bool found = false;
            for (const QString& foundKey : foundKeys) {
                if (rule.keyPattern.isEmpty()) {
                    if (foundKey == rule.key || foundKey.endsWith("/" + rule.key)) {
                        found = true;
                        break;
                    }
                } else {
                    QRegularExpression re(rule.keyPattern);
                    if (re.match(foundKey).hasMatch()) {
                        found = true;
                        break;
                    }
                }
            }
            
            if (!found) {
                addResult(rule.key, Error, tr("缺少必需的配置项: ") + rule.key);
            }
        }
    }
    
    QVariantList conflictResults = checkConflicts(config);
    m_results.append(conflictResults);
    
    QVariantList dependencyResults = checkDependencies(config);
    m_results.append(dependencyResults);
    
    emit validationResultsChanged();
    emit validationCompleted(errorCount(), warningCount(), infoCount());
    
    return m_results;
}

QVariantList ConfigValidator::validateKey(const QString& key, const QString& value, const QString& section)
{
    QVariantList results;
    QString fullKey = section.isEmpty() ? key : section + "/" + key;
    
    for (auto it = m_rules.begin(); it != m_rules.end(); ++it) {
        const ValidationRule& rule = it.value();
        
        bool matches = false;
        if (rule.keyPattern.isEmpty()) {
            matches = (key == rule.key || fullKey == rule.key || fullKey.endsWith("/" + rule.key));
        } else {
            QRegularExpression re(rule.keyPattern);
            matches = re.match(key).hasMatch() || re.match(fullKey).hasMatch();
        }
        
        if (!matches) continue;
        
        if (value.isEmpty() && rule.required) {
            QVariantMap result;
            result["key"] = key;
            result["section"] = section;
            result["severity"] = Error;
            result["message"] = tr("必需的配置项值为空");
            result["suggestion"] = tr("请设置有效的值");
            results.append(result);
            continue;
        }
        
        if (!rule.type.isEmpty() && !value.isEmpty()) {
            if (!validateType(rule.type, value)) {
                QVariantMap result;
                result["key"] = key;
                result["section"] = section;
                result["severity"] = Error;
                result["message"] = tr("类型错误: 期望 %1, 实际值 '%2'").arg(rule.type, value);
                result["suggestion"] = tr("请输入有效的 %1 值").arg(rule.type);
                results.append(result);
            }
        }
        
        if (rule.minValue.isValid() || rule.maxValue.isValid()) {
            if (!validateRange(value, rule.minValue, rule.maxValue)) {
                QVariantMap result;
                result["key"] = key;
                result["section"] = section;
                result["severity"] = Warning;
                
                QString rangeMsg;
                if (rule.minValue.isValid() && rule.maxValue.isValid()) {
                    rangeMsg = tr("值超出范围 [%1, %2]").arg(rule.minValue.toString(), rule.maxValue.toString());
                } else if (rule.minValue.isValid()) {
                    rangeMsg = tr("值小于最小值 %1").arg(rule.minValue.toString());
                } else {
                    rangeMsg = tr("值大于最大值 %1").arg(rule.maxValue.toString());
                }
                
                result["message"] = rangeMsg;
                result["suggestion"] = tr("建议值范围: %1 - %2").arg(
                    rule.minValue.isValid() ? rule.minValue.toString() : "-inf",
                    rule.maxValue.isValid() ? rule.maxValue.toString() : "inf");
                results.append(result);
            }
        }
        
        if (!rule.regex.isEmpty() && !value.isEmpty()) {
            if (!validateRegex(value, rule.regex)) {
                QVariantMap result;
                result["key"] = key;
                result["section"] = section;
                result["severity"] = Warning;
                result["message"] = tr("值格式不正确: %1").arg(value);
                result["suggestion"] = tr("期望格式: %1").arg(rule.regex);
                results.append(result);
            }
        }
        
        if (!rule.allowedValues.isEmpty() && !value.isEmpty()) {
            if (!validateEnum(value, rule.allowedValues)) {
                QVariantMap result;
                result["key"] = key;
                result["section"] = section;
                result["severity"] = Warning;
                result["message"] = tr("值不在允许列表中: %1").arg(value);
                result["suggestion"] = tr("允许的值: %1").arg(rule.allowedValues.join(", "));
                results.append(result);
            }
        }
    }
    
    return results;
}

bool ConfigValidator::loadSchema(const QString& schemaPath)
{
    QFile file(schemaPath);
    if (!file.exists()) {
        return false;
    }
    
    if (!file.open(QIODevice::ReadOnly)) {
        emit errorOccurred(tr("无法打开 schema 文件"));
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    return loadSchemaFromJson(QString::fromUtf8(data));
}

bool ConfigValidator::loadSchemaFromJson(const QString& jsonContent)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonContent.toUtf8(), &error);
    
    if (error.error != QJsonParseError::NoError) {
        emit errorOccurred(tr("Schema JSON 解析错误: ") + error.errorString());
        return false;
    }
    
    m_schema = doc.toVariant().toMap();
    m_rules.clear();
    
    loadBuiltinRules();
    
    QVariantList rules = m_schema["rules"].toList();
    for (const QVariant& ruleVar : rules) {
        QVariantMap ruleMap = ruleVar.toMap();
        
        ValidationRule rule;
        rule.key = ruleMap["key"].toString();
        rule.keyPattern = ruleMap["keyPattern"].toString();
        rule.type = ruleMap["type"].toString();
        rule.required = ruleMap["required"].toBool();
        rule.description = ruleMap["description"].toString();
        rule.regex = ruleMap["regex"].toString();
        
        if (ruleMap.contains("min")) {
            rule.minValue = ruleMap["min"];
        }
        if (ruleMap.contains("max")) {
            rule.maxValue = ruleMap["max"];
        }
        if (ruleMap.contains("allowedValues")) {
            rule.allowedValues = ruleMap["allowedValues"].toStringList();
        }
        
        if (!rule.key.isEmpty()) {
            m_rules[rule.key] = rule;
        }
    }
    
    emit schemaLoaded("json");
    return true;
}

QVariantMap ConfigValidator::getSchema()
{
    return m_schema;
}

bool ConfigValidator::saveSchema(const QString& outputPath)
{
    QVariantMap schema;
    QVariantList rulesList;
    
    for (auto it = m_rules.begin(); it != m_rules.end(); ++it) {
        const ValidationRule& rule = it.value();
        QVariantMap ruleMap;
        ruleMap["key"] = rule.key;
        if (!rule.keyPattern.isEmpty()) ruleMap["keyPattern"] = rule.keyPattern;
        if (!rule.type.isEmpty()) ruleMap["type"] = rule.type;
        if (rule.required) ruleMap["required"] = true;
        if (!rule.description.isEmpty()) ruleMap["description"] = rule.description;
        if (!rule.regex.isEmpty()) ruleMap["regex"] = rule.regex;
        if (rule.minValue.isValid()) ruleMap["min"] = rule.minValue;
        if (rule.maxValue.isValid()) ruleMap["max"] = rule.maxValue;
        if (!rule.allowedValues.isEmpty()) ruleMap["allowedValues"] = rule.allowedValues;
        rulesList.append(ruleMap);
    }
    
    schema["rules"] = rulesList;
    schema["version"] = "1.0";
    
    QFile file(outputPath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    
    file.write(QJsonDocument::fromVariant(schema).toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

void ConfigValidator::addRule(const QString& key, const QString& type, const QVariantMap& constraints)
{
    ValidationRule rule;
    rule.key = key;
    rule.type = type;
    rule.required = constraints.value("required", false).toBool();
    rule.description = constraints.value("description").toString();
    rule.regex = constraints.value("regex").toString();
    rule.keyPattern = constraints.value("keyPattern").toString();
    
    if (constraints.contains("min")) {
        rule.minValue = constraints["min"];
    }
    if (constraints.contains("max")) {
        rule.maxValue = constraints["max"];
    }
    if (constraints.contains("allowedValues")) {
        rule.allowedValues = constraints["allowedValues"].toStringList();
    }
    
    m_rules[key] = rule;
}

void ConfigValidator::removeRule(const QString& key)
{
    m_rules.remove(key);
}

void ConfigValidator::clearRules()
{
    m_rules.clear();
}

QVariantList ConfigValidator::getRules()
{
    QVariantList result;
    for (auto it = m_rules.begin(); it != m_rules.end(); ++it) {
        QVariantMap ruleMap;
        ruleMap["key"] = it.value().key;
        ruleMap["type"] = it.value().type;
        ruleMap["required"] = it.value().required;
        ruleMap["description"] = it.value().description;
        result.append(ruleMap);
    }
    return result;
}

QVariantList ConfigValidator::checkConflicts(const QVariantList& config)
{
    QVariantList results;
    
    QHash<QString, QString> keyValues;
    for (const QVariant& item : config) {
        QVariantMap entry = item.toMap();
        QString key = entry["key"].toString();
        QString value = entry["value"].toString();
        keyValues[key] = value;
    }
    
    static QVector<QPair<QStringList, QString>> conflicts = {
        {{"ExposureTime", "FrameRate"}, tr("曝光时间和帧率可能冲突，高曝光时间会限制最大帧率")},
        {{"Gain", "ExposureTime"}, tr("增益和曝光时间需要平衡，过高增益会增加噪声")},
        {{"LightIntensity", "ExposureTime"}, tr("光源强度和曝光时间需要配合调整")},
        {{"TriggerMode", "TriggerSource"}, tr("触发模式和触发源需要匹配设置")},
    };
    
    for (const auto& conflict : conflicts) {
        const QStringList& keys = conflict.first;
        bool allFound = true;
        
        for (const QString& key : keys) {
            if (!keyValues.contains(key)) {
                allFound = false;
                break;
            }
        }
        
        if (allFound) {
            QVariantMap result;
            result["severity"] = Info;
            result["keys"] = keys;
            result["message"] = conflict.second;
            results.append(result);
        }
    }
    
    return results;
}

QVariantList ConfigValidator::checkDependencies(const QVariantList& config)
{
    QVariantList results;
    
    QHash<QString, QString> keyValues;
    for (const QVariant& item : config) {
        QVariantMap entry = item.toMap();
        QString key = entry["key"].toString();
        QString value = entry["value"].toString();
        keyValues[key] = value;
    }
    
    static QVector<QPair<QString, QString>> dependencies = {
        {"TriggerMode", "TriggerSource"},
        {"Binning", "Resolution"},
        {"PixelFormat", "Binning"},
    };
    
    for (const auto& dep : dependencies) {
        QString key = dep.first;
        QString requiredKey = dep.second;
        
        if (keyValues.contains(key) && !keyValues.contains(requiredKey)) {
            QVariantMap result;
            result["severity"] = Warning;
            result["key"] = key;
            result["message"] = tr("配置项 %1 依赖于 %2，但 %2 未设置").arg(key, requiredKey);
            result["suggestion"] = tr("请设置 %1").arg(requiredKey);
            results.append(result);
        }
    }
    
    return results;
}

QVariantList ConfigValidator::checkRanges(const QVariantList& config)
{
    QVariantList results;
    
    static QHash<QString, QPair<double, double>> knownRanges = {
        {"ExposureTime", {100, 10000000}},
        {"Gain", {0, 48}},
        {"FrameRate", {1, 200}},
        {"LightIntensity", {0, 100}},
        {"Brightness", {0, 255}},
        {"Contrast", {0, 100}},
        {"Saturation", {0, 100}},
        {"Gamma", {0.1, 4.0}},
    };
    
    for (const QVariant& item : config) {
        QVariantMap entry = item.toMap();
        QString key = entry["key"].toString();
        QString valueStr = entry["value"].toString();
        
        if (knownRanges.contains(key)) {
            bool ok;
            double value = valueStr.toDouble(&ok);
            
            if (ok) {
                auto range = knownRanges[key];
                if (value < range.first || value > range.second) {
                    QVariantMap result;
                    result["severity"] = Warning;
                    result["key"] = key;
                    result["message"] = tr("值 %1 超出推荐范围 [%2, %3]")
                        .arg(value).arg(range.first).arg(range.second);
                    result["suggestion"] = tr("建议范围: %1 - %2").arg(range.first).arg(range.second);
                    results.append(result);
                }
            }
        }
    }
    
    return results;
}

QVariantList ConfigValidator::checkFormats(const QVariantList& config)
{
    QVariantList results;
    
    static QHash<QString, QRegularExpression> formatPatterns = {
        {"IPAddress", QRegularExpression(R"((\d{1,3}\.){3}\d{1,3})")},
        {"MACAddress", QRegularExpression(R"(([0-9A-Fa-f]{2}:){5}[0-9A-Fa-f]{2})")},
        {"Port", QRegularExpression(R"(\d{1,5})")},
        {"FilePath", QRegularExpression(R"([a-zA-Z]:\\[\\\S|*?\S]*|/[^\0]*)")},
        {"Email", QRegularExpression(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})")},
    };
    
    for (const QVariant& item : config) {
        QVariantMap entry = item.toMap();
        QString key = entry["key"].toString();
        QString value = entry["value"].toString();
        
        for (auto it = formatPatterns.begin(); it != formatPatterns.end(); ++it) {
            if (key.contains(it.key(), Qt::CaseInsensitive)) {
                if (!it.value().match(value).hasMatch() && !value.isEmpty()) {
                    QVariantMap result;
                    result["severity"] = Warning;
                    result["key"] = key;
                    result["message"] = tr("值 '%1' 格式不符合 %2 格式").arg(value, it.key());
                    results.append(result);
                }
            }
        }
    }
    
    return results;
}

QString ConfigValidator::generateValidationReport(const QString& format)
{
    QString report;
    
    if (format == "json") {
        QJsonArray arr;
        for (const QVariant& item : m_results) {
            arr.append(QJsonObject::fromVariantMap(item.toMap()));
        }
        report = QJsonDocument(arr).toJson(QJsonDocument::Indented);
    } else if (format == "markdown") {
        report = "# 配置验证报告\n\n";
        report += QString("**文件**: %1\n\n").arg(m_lastValidatedFile);
        report += QString("**统计**: 错误 %1, 警告 %2, 信息 %3\n\n")
            .arg(errorCount()).arg(warningCount()).arg(infoCount());
        
        report += "## 错误\n\n";
        for (const QVariant& item : m_results) {
            QVariantMap r = item.toMap();
            if (r["severity"].toInt() == Error) {
                report += QString("- **%1**: %2\n").arg(r["key"].toString(), r["message"].toString());
            }
        }
        
        report += "\n## 警告\n\n";
        for (const QVariant& item : m_results) {
            QVariantMap r = item.toMap();
            if (r["severity"].toInt() == Warning) {
                report += QString("- **%1**: %2\n").arg(r["key"].toString(), r["message"].toString());
            }
        }
    } else {
        report = QString("=== 配置验证报告 ===\n");
        report += QString("文件: %1\n").arg(m_lastValidatedFile);
        report += QString("统计: 错误 %1, 警告 %2, 信息 %3\n\n")
            .arg(errorCount()).arg(warningCount()).arg(infoCount());
        
        for (const QVariant& item : m_results) {
            QVariantMap r = item.toMap();
            QString severityStr;
            switch (r["severity"].toInt()) {
                case Error: severityStr = "ERROR"; break;
                case Warning: severityStr = "WARN"; break;
                default: severityStr = "INFO"; break;
            }
            
            report += QString("[%1] %2: %3\n")
                .arg(severityStr, r["key"].toString(), r["message"].toString());
            
            if (r.contains("suggestion")) {
                report += QString("  建议: %1\n").arg(r["suggestion"].toString());
            }
        }
    }
    
    return report;
}

bool ConfigValidator::exportValidationReport(const QString& outputPath, const QString& format)
{
    QString report = generateValidationReport(format);
    
    QFile file(outputPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream out(&file);
    out << report;
    file.close();
    return true;
}

QVariantList ConfigValidator::suggestFixes(const QVariantList& issues)
{
    QVariantList suggestions;
    
    for (const QVariant& issue : issues) {
        QVariantMap issueMap = issue.toMap();
        QString key = issueMap["key"].toString();
        QString message = issueMap["message"].toString();
        
        QVariantMap suggestion;
        suggestion["key"] = key;
        suggestion["issue"] = message;
        
        if (message.contains("类型错误")) {
            suggestion["fix"] = "转换为正确的类型";
            suggestion["autoFixable"] = true;
        } else if (message.contains("超出范围")) {
            suggestion["fix"] = "调整到有效范围内";
            suggestion["autoFixable"] = true;
        } else if (message.contains("格式不正确")) {
            suggestion["fix"] = "修正格式";
            suggestion["autoFixable"] = false;
        } else {
            suggestion["fix"] = "手动检查和修正";
            suggestion["autoFixable"] = false;
        }
        
        suggestions.append(suggestion);
    }
    
    return suggestions;
}

bool ConfigValidator::autoFix(QVariantList& config, const QVariantList& issues)
{
    bool anyFixed = false;
    
    for (const QVariant& issue : issues) {
        QVariantMap issueMap = issue.toMap();
        
        if (!issueMap["autoFixable"].toBool()) continue;
        
        QString key = issueMap["key"].toString();
        
        for (int i = 0; i < config.size(); ++i) {
            QVariantMap entry = config[i].toMap();
            if (entry["key"].toString() == key) {
                QString message = issueMap["message"].toString();
                
                if (message.contains("超出范围")) {
                    if (m_rules.contains(key)) {
                        const ValidationRule& rule = m_rules[key];
                        double value = entry["value"].toString().toDouble();
                        
                        if (rule.minValue.isValid() && value < rule.minValue.toDouble()) {
                            entry["value"] = rule.minValue;
                            config[i] = entry;
                            anyFixed = true;
                        } else if (rule.maxValue.isValid() && value > rule.maxValue.toDouble()) {
                            entry["value"] = rule.maxValue;
                            config[i] = entry;
                            anyFixed = true;
                        }
                    }
                }
                break;
            }
        }
    }
    
    return anyFixed;
}

bool ConfigValidator::validateType(const QString& type, const QString& value)
{
    if (value.isEmpty()) return true;
    
    if (type == "int") {
        bool ok;
        value.toInt(&ok);
        return ok;
    } else if (type == "float" || type == "double") {
        bool ok;
        value.toDouble(&ok);
        return ok;
    } else if (type == "bool") {
        QString lower = value.toLower();
        return lower == "true" || lower == "false" || 
               lower == "1" || lower == "0" ||
               lower == "yes" || lower == "no";
    } else if (type == "string") {
        return true;
    }
    
    return true;
}

bool ConfigValidator::validateRange(const QString& value, const QVariant& min, const QVariant& max)
{
    bool ok;
    double numValue = value.toDouble(&ok);
    if (!ok) return true;
    
    if (min.isValid() && numValue < min.toDouble()) return false;
    if (max.isValid() && numValue > max.toDouble()) return false;
    
    return true;
}

bool ConfigValidator::validateRegex(const QString& value, const QString& pattern)
{
    if (value.isEmpty()) return true;
    
    QRegularExpression re(pattern);
    return re.match(value).hasMatch();
}

bool ConfigValidator::validateEnum(const QString& value, const QStringList& allowed)
{
    return allowed.contains(value, Qt::CaseInsensitive);
}

void ConfigValidator::addResult(const QString& key, Severity severity, const QString& message, const QString& suggestion)
{
    QVariantMap result;
    result["key"] = key;
    result["severity"] = static_cast<int>(severity);
    result["message"] = message;
    if (!suggestion.isEmpty()) {
        result["suggestion"] = suggestion;
    }
    m_results.append(result);
}

QVariantList ConfigValidator::parseConfigFile(const QString& filePath)
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
    } else {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString currentSection;
            
            while (!in.atEnd()) {
                QString line = in.readLine().trimmed();
                
                if (line.isEmpty() || line.startsWith(';') || line.startsWith('#')) continue;
                
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

QString ConfigValidator::detectFormat(const QString& filePath)
{
    if (filePath.endsWith(".json", Qt::CaseInsensitive)) return "json";
    if (filePath.endsWith(".xml", Qt::CaseInsensitive)) return "xml";
    return "ini";
}

QString ConfigValidator::getSchemaPath()
{
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataDir);
    return dataDir + "/validation_schema.json";
}

void ConfigValidator::loadDefaultSchema()
{
}

void ConfigValidator::loadBuiltinRules()
{
    ValidationRule rule;
    
    rule.key = "ExposureTime";
    rule.type = "int";
    rule.minValue = 100;
    rule.maxValue = 10000000;
    rule.description = tr("曝光时间 (微秒)");
    m_rules[rule.key] = rule;
    
    rule.key = "Gain";
    rule.type = "float";
    rule.minValue = 0;
    rule.maxValue = 48;
    rule.description = tr("增益值");
    m_rules[rule.key] = rule;
    
    rule.key = "FrameRate";
    rule.type = "float";
    rule.minValue = 1;
    rule.maxValue = 200;
    rule.description = tr("帧率");
    m_rules[rule.key] = rule;
    
    rule.key = "Brightness";
    rule.type = "int";
    rule.minValue = 0;
    rule.maxValue = 255;
    rule.description = tr("亮度值");
    m_rules[rule.key] = rule;
    
    rule.key = "Contrast";
    rule.type = "int";
    rule.minValue = 0;
    rule.maxValue = 100;
    rule.description = tr("对比度");
    m_rules[rule.key] = rule;
    
    rule.key = "Gamma";
    rule.type = "float";
    rule.minValue = 0.1;
    rule.maxValue = 4.0;
    rule.description = tr("伽马值");
    m_rules[rule.key] = rule;
    
    rule.key = "LightIntensity";
    rule.type = "int";
    rule.minValue = 0;
    rule.maxValue = 100;
    rule.description = tr("光源强度 (%)");
    m_rules[rule.key] = rule;
    
    rule.key = "TriggerMode";
    rule.type = "string";
    rule.allowedValues = QStringList() << "Continuous" << "Software" << "Hardware" << "External";
    rule.description = tr("触发模式");
    m_rules[rule.key] = rule;
    
    rule.key = "PixelFormat";
    rule.type = "string";
    rule.allowedValues = QStringList() << "Mono8" << "Mono10" << "Mono12" << "RGB8" << "RGB10" << "BGR8" << "BayerRG8" << "BayerGB8";
    rule.description = tr("像素格式");
    m_rules[rule.key] = rule;
    
    rule.key = "Binning";
    rule.type = "string";
    rule.allowedValues = QStringList() << "1x1" << "2x2" << "4x4";
    rule.description = tr("像素合并");
    m_rules[rule.key] = rule;
    
    rule.key = "Port";
    rule.type = "int";
    rule.minValue = 1;
    rule.maxValue = 65535;
    rule.description = tr("网络端口");
    m_rules[rule.key] = rule;
    
    rule.key = "IPAddress";
    rule.type = "string";
    rule.regex = R"((\d{1,3}\.){3}\d{1,3})";
    rule.description = tr("IP 地址");
    m_rules[rule.key] = rule;
}
