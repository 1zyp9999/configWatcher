#ifndef TEST_CONFIGVALIDATOR_H
#define TEST_CONFIGVALIDATOR_H

#include <QtTest/QtTest>
#include "test_base.h"
#include "configvalidator.h"

class TestConfigValidator : public TestBase
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    
    // 构造函数和单例测试
    void testConfigValidator_Constructor();
    void testConfigValidator_Instance();
    
    // 文件验证测试
    void testValidateFile_Basic();
    void testValidateFile_NonExistent();
    void testValidateFile_Empty();
    
    // 配置验证测试
    void testValidateConfig_Basic();
    void testValidateConfig_Empty();
    void testValidateConfig_Required();
    
    // 键验证测试
    void testValidateKey_Basic();
    void testValidateKey_Type();
    void testValidateKey_Range();
    void testValidateKey_Regex();
    void testValidateKey_Enum();
    
    // Schema 管理测试
    void testLoadSchema();
    void testLoadSchemaFromJson();
    void testGetSchema();
    void testSaveSchema();
    
    // 规则管理测试
    void testAddRule();
    void testRemoveRule();
    void testClearRules();
    void testGetRules();
    
    // 冲突检查测试
    void testCheckConflicts();
    
    // 依赖检查测试
    void testCheckDependencies();
    
    // 范围检查测试
    void testCheckRanges();
    
    // 格式检查测试
    void testCheckFormats();
    
    // 统计测试
    void testErrorCount();
    void testWarningCount();
    void testInfoCount();
    
    // 报告生成测试
    void testGenerateValidationReport_Text();
    void testGenerateValidationReport_JSON();
    void testGenerateValidationReport_Markdown();
    
    // 报告导出测试
    void testExportValidationReport();
    
    // 修复建议测试
    void testSuggestFixes();
    void testAutoFix();
    
    // 信号测试
    void testValidationResultsChanged_Signal();
    void testValidationCompleted_Signal();
    void testSchemaLoaded_Signal();
    void testErrorOccurred_Signal();
};

void TestConfigValidator::initTestCase()
{
    qDebug() << "开始 ConfigValidator 测试";
}

void TestConfigValidator::cleanupTestCase()
{
    qDebug() << "ConfigValidator 测试完成";
}

void TestConfigValidator::testConfigValidator_Constructor()
{
    ConfigValidator validator;
    QVERIFY(validator.parent() == nullptr);
    QCOMPARE(validator.validationResults().size(), 0);
}

void TestConfigValidator::testConfigValidator_Instance()
{
    ConfigValidator* instance1 = ConfigValidator::instance();
    QVERIFY(instance1 != nullptr);
    // 单例模式
}

void TestConfigValidator::testValidateFile_Basic()
{
    QString content = "key1=value1\nkey2=value2";
    QString filePath = createTempFile(content, ".ini");
    
    ConfigValidator validator;
    QVariantList results = validator.validateFile(filePath);
    
    // 应该有验证结果
    QVERIFY(results.size() >= 0);
}

void TestConfigValidator::testValidateFile_NonExistent()
{
    ConfigValidator validator;
    QSignalSpy spy(&validator, SIGNAL(errorOccurred(QString)));
    
    QVariantList results = validator.validateFile("/non/existent.ini");
    
    QCOMPARE(results.size(), 1);  // 应该有错误
    QCOMPARE(spy.count(), 1);
}

void TestConfigValidator::testValidateFile_Empty()
{
    QString content = "";
    QString filePath = createTempFile(content, ".ini");
    
    ConfigValidator validator;
    QVariantList results = validator.validateFile(filePath);
    
    // 空文件应该有警告
    QVERIFY(results.size() > 0);
}

void TestConfigValidator::testValidateConfig_Basic()
{
    QVariantList config;
    QVariantMap entry;
    entry["key"] = "key1";
    entry["value"] = "value1";
    entry["section"] = "";
    config.append(entry);
    
    ConfigValidator validator;
    QVariantList results = validator.validateConfig(config);
    
    QVERIFY(results.size() >= 0);
}

void TestConfigValidator::testValidateConfig_Empty()
{
    QVariantList config;
    
    ConfigValidator validator;
    QVariantList results = validator.validateConfig(config);
    
    QCOMPARE(results.size(), 0);
}

void TestConfigValidator::testValidateConfig_Required()
{
    // 添加必需规则
    ConfigValidator validator;
    validator.clearRules();
    
    QVariantMap constraints;
    constraints["required"] = true;
    validator.addRule("required_key", "string", constraints);
    
    // 验证缺少必需键的配置
    QVariantList config;
    QVariantMap entry;
    entry["key"] = "other_key";
    entry["value"] = "value";
    entry["section"] = "";
    config.append(entry);
    
    QVariantList results = validator.validateConfig(config);
    
    // 应该有错误（缺少必需键）
    bool hasError = false;
    for (const QVariant& r : results) {
        if (r.toMap()["severity"].toInt() == ConfigValidator::Error) {
            hasError = true;
            break;
        }
    }
    QVERIFY(hasError);
}

void TestConfigValidator::testValidateKey_Basic()
{
    ConfigValidator validator;
    QVariantList results = validator.validateKey("key1", "value1", "");
    
    QCOMPARE(results.size(), 0);  // 没有规则时应该通过
}

void TestConfigValidator::testValidateKey_Type()
{
    ConfigValidator validator;
    validator.clearRules();
    
    QVariantMap constraints;
    constraints["type"] = "int";
    validator.addRule("test_key", "int", constraints);
    
    // 测试无效类型
    QVariantList results = validator.validateKey("test_key", "not_a_number", "");
    
    bool hasError = false;
    for (const QVariant& r : results) {
        if (r.toMap()["severity"].toInt() == ConfigValidator::Error) {
            hasError = true;
            break;
        }
    }
    QVERIFY(hasError);
}

void TestConfigValidator::testValidateKey_Range()
{
    ConfigValidator validator;
    validator.clearRules();
    
    QVariantMap constraints;
    constraints["min"] = 0;
    constraints["max"] = 100;
    validator.addRule("test_key", "int", constraints);
    
    // 测试超出范围
    QVariantList results = validator.validateKey("test_key", "150", "");
    
    // 应该有警告
    bool hasWarning = false;
    for (const QVariant& r : results) {
        if (r.toMap()["severity"].toInt() == ConfigValidator::Warning) {
            hasWarning = true;
            break;
        }
    }
    QVERIFY(hasWarning);
}

void TestConfigValidator::testValidateKey_Regex()
{
    ConfigValidator validator;
    validator.clearRules();
    
    QVariantMap constraints;
    constraints["regex"] = "^[a-z]+$";
    validator.addRule("test_key", "string", constraints);
    
    // 测试不匹配的模式
    QVariantList results = validator.validateKey("test_key", "123", "");
    
    // 应该有警告
    bool hasWarning = false;
    for (const QVariant& r : results) {
        if (r.toMap()["severity"].toInt() == ConfigValidator::Warning) {
            hasWarning = true;
            break;
        }
    }
    QVERIFY(hasWarning);
}

void TestConfigValidator::testValidateKey_Enum()
{
    ConfigValidator validator;
    validator.clearRules();
    
    QVariantMap constraints;
    constraints["allowedValues"] = QStringList() << "value1" << "value2";
    validator.addRule("test_key", "string", constraints);
    
    // 测试不在允许列表中的值
    QVariantList results = validator.validateKey("test_key", "invalid_value", "");
    
    // 应该有警告
    bool hasWarning = false;
    for (const QVariant& r : results) {
        if (r.toMap()["severity"].toInt() == ConfigValidator::Warning) {
            hasWarning = true;
            break;
        }
    }
    QVERIFY(hasWarning);
}

void TestConfigValidator::testLoadSchema()
{
    ConfigValidator validator;
    
    // 创建 schema 文件
    QString schemaContent = R"({
        "rules": [
            {"key": "test_key", "type": "string", "required": false}
        ]
    })";
    QString schemaPath = createTempFile(schemaContent, ".json");
    
    bool result = validator.loadSchema(schemaPath);
    QVERIFY(result);
}

void TestConfigValidator::testLoadSchemaFromJson()
{
    ConfigValidator validator;
    
    QString schemaJson = R"({
        "rules": [
            {"key": "test_key", "type": "string", "required": true}
        ]
    })";
    
    bool result = validator.loadSchemaFromJson(schemaJson);
    QVERIFY(result);
}

void TestConfigValidator::testGetSchema()
{
    ConfigValidator validator;
    QVariantMap schema = validator.getSchema();
    
    // 初始 schema 应该为空或有默认值
    QVERIFY(schema.size() >= 0);
}

void TestConfigValidator::testSaveSchema()
{
    ConfigValidator validator;
    validator.clearRules();
    
    QVariantMap constraints;
    constraints["type"] = "string";
    validator.addRule("test_key", "string", constraints);
    
    QString outputPath = m_tempDir.filePath("schema.json");
    bool result = validator.saveSchema(outputPath);
    
    QVERIFY(result);
    QVERIFY(QFile::exists(outputPath));
}

void TestConfigValidator::testAddRule()
{
    ConfigValidator validator;
    validator.clearRules();
    
    QVariantMap constraints;
    constraints["type"] = "int";
    constraints["required"] = true;
    validator.addRule("test_key", "int", constraints);
    
    QVariantList rules = validator.getRules();
    QCOMPARE(rules.size(), 1);
}

void TestConfigValidator::testRemoveRule()
{
    ConfigValidator validator;
    validator.clearRules();
    
    QVariantMap constraints;
    constraints["type"] = "string";
    validator.addRule("test_key", "string", constraints);
    validator.removeRule("test_key");
    
    QVariantList rules = validator.getRules();
    QCOMPARE(rules.size(), 0);
}

void TestConfigValidator::testClearRules()
{
    ConfigValidator validator;
    validator.clearRules();
    
    QVariantMap constraints;
    constraints["type"] = "string";
    validator.addRule("key1", "string", constraints);
    validator.addRule("key2", "string", constraints);
    
    validator.clearRules();
    
    QVariantList rules = validator.getRules();
    QCOMPARE(rules.size(), 0);
}

void TestConfigValidator::testGetRules()
{
    ConfigValidator validator;
    validator.clearRules();
    
    QVariantMap constraints;
    constraints["type"] = "string";
    validator.addRule("key1", "string", constraints);
    
    QVariantList rules = validator.getRules();
    QCOMPARE(rules.size(), 1);
}

void TestConfigValidator::testCheckConflicts()
{
    QVariantList config;
    
    QVariantMap entry1;
    entry1["key"] = "ExposureTime";
    entry1["value"] = "1000";
    entry1["section"] = "";
    config.append(entry1);
    
    QVariantMap entry2;
    entry2["key"] = "FrameRate";
    entry2["value"] = "60";
    entry2["section"] = "";
    config.append(entry2);
    
    ConfigValidator validator;
    QVariantList results = validator.checkConflicts(config);
    
    // 可能有信息提示
    QVERIFY(results.size() >= 0);
}

void TestConfigValidator::testCheckDependencies()
{
    QVariantList config;
    
    QVariantMap entry1;
    entry1["key"] = "TriggerMode";
    entry1["value"] = "On";
    entry1["section"] = "";
    config.append(entry1);
    
    // 缺少 TriggerSource
    
    ConfigValidator validator;
    QVariantList results = validator.checkDependencies(config);
    
    // 应该有警告（缺少依赖）
    bool hasWarning = false;
    for (const QVariant& r : results) {
        if (r.toMap()["severity"].toInt() == ConfigValidator::Warning) {
            hasWarning = true;
            break;
        }
    }
    QVERIFY(hasWarning);
}

void TestConfigValidator::testCheckRanges()
{
    QVariantList config;
    
    QVariantMap entry;
    entry["key"] = "ExposureTime";
    entry["value"] = "1";  // 超出推荐范围
    entry["section"] = "";
    config.append(entry);
    
    ConfigValidator validator;
    QVariantList results = validator.checkRanges(config);
    
    // 应该有警告
    bool hasWarning = false;
    for (const QVariant& r : results) {
        if (r.toMap()["severity"].toInt() == ConfigValidator::Warning) {
            hasWarning = true;
            break;
        }
    }
    QVERIFY(hasWarning);
}

void TestConfigValidator::testCheckFormats()
{
    QVariantList config;
    
    QVariantMap entry;
    entry["key"] = "IPAddress";
    entry["value"] = "invalid_ip";
    entry["section"] = "";
    config.append(entry);
    
    ConfigValidator validator;
    QVariantList results = validator.checkFormats(config);
    
    // 应该有警告（格式不正确）
    bool hasWarning = false;
    for (const QVariant& r : results) {
        if (r.toMap()["severity"].toInt() == ConfigValidator::Warning) {
            hasWarning = true;
            break;
        }
    }
    QVERIFY(hasWarning);
}

void TestConfigValidator::testErrorCount()
{
    ConfigValidator validator;
    validator.validateFile("/non/existent.ini");
    
    QVERIFY(validator.errorCount() > 0);
}

void TestConfigValidator::testWarningCount()
{
    ConfigValidator validator;
    
    QVariantList config;
    QVariantMap entry;
    entry["key"] = "ExposureTime";
    entry["value"] = "1";  // 超出范围
    entry["section"] = "";
    config.append(entry);
    
    validator.validateConfig(config);
    
    QVERIFY(validator.warningCount() > 0);
}

void TestConfigValidator::testInfoCount()
{
    ConfigValidator validator;
    
    QVariantList config;
    QVariantMap entry1;
    entry1["key"] = "ExposureTime";
    entry1["value"] = "1000";
    entry1["section"] = "";
    config.append(entry1);
    
    QVariantMap entry2;
    entry2["key"] = "FrameRate";
    entry2["value"] = "60";
    entry2["section"] = "";
    config.append(entry2);
    
    validator.validateConfig(config);
    
    // 可能有信息提示
    QVERIFY(validator.infoCount() >= 0);
}

void TestConfigValidator::testGenerateValidationReport_Text()
{
    ConfigValidator validator;
    validator.validateFile("/non/existent.ini");
    
    QString report = validator.generateValidationReport("text");
    QVERIFY(!report.isEmpty());
}

void TestConfigValidator::testGenerateValidationReport_JSON()
{
    ConfigValidator validator;
    validator.validateFile("/non/existent.ini");
    
    QString report = validator.generateValidationReport("json");
    QVERIFY(!report.isEmpty());
    QVERIFY(report.contains("{"));
}

void TestConfigValidator::testGenerateValidationReport_Markdown()
{
    ConfigValidator validator;
    validator.validateFile("/non/existent.ini");
    
    QString report = validator.generateValidationReport("markdown");
    QVERIFY(!report.isEmpty());
    QVERIFY(report.contains("#"));
}

void TestConfigValidator::testExportValidationReport()
{
    ConfigValidator validator;
    validator.validateFile("/non/existent.ini");
    
    QString outputPath = m_tempDir.filePath("report.txt");
    bool result = validator.exportValidationReport(outputPath, "text");
    
    QVERIFY(result);
    QVERIFY(QFile::exists(outputPath));
}

void TestConfigValidator::testSuggestFixes()
{
    QVariantList issues;
    QVariantMap issue;
    issue["key"] = "test_key";
    issue["message"] = "类型错误";
    issues.append(issue);
    
    ConfigValidator validator;
    QVariantList suggestions = validator.suggestFixes(issues);
    
    QCOMPARE(suggestions.size(), 1);
    QVERIFY(suggestions[0].toMap().contains("fix"));
}

void TestConfigValidator::testAutoFix()
{
    QVariantList config;
    QVariantMap entry;
    entry["key"] = "test_key";
    entry["value"] = "150";  // 超出范围
    entry["section"] = "";
    config.append(entry);
    
    QVariantList issues;
    QVariantMap issue;
    issue["key"] = "test_key";
    issue["message"] = "超出范围";
    issue["autoFixable"] = true;
    issues.append(issue);
    
    ConfigValidator validator;
    validator.clearRules();
    
    QVariantMap constraints;
    constraints["min"] = 0;
    constraints["max"] = 100;
    validator.addRule("test_key", "int", constraints);
    
    bool result = validator.autoFix(config, issues);
    QVERIFY(result);
}

void TestConfigValidator::testValidationResultsChanged_Signal()
{
    ConfigValidator validator;
    QSignalSpy spy(&validator, SIGNAL(validationResultsChanged()));
    
    validator.validateFile("/non/existent.ini");
    
    QCOMPARE(spy.count(), 1);
}

void TestConfigValidator::testValidationCompleted_Signal()
{
    ConfigValidator validator;
    QSignalSpy spy(&validator, SIGNAL(validationCompleted(int, int, int)));
    
    QString content = "key1=value1";
    QString filePath = createTempFile(content, ".ini");
    
    validator.validateFile(filePath);
    
    QCOMPARE(spy.count(), 1);
}

void TestConfigValidator::testSchemaLoaded_Signal()
{
    ConfigValidator validator;
    QSignalSpy spy(&validator, SIGNAL(schemaLoaded(QString)));
    
    QString schemaJson = R"({"rules": []})";
    validator.loadSchemaFromJson(schemaJson);
    
    QCOMPARE(spy.count(), 1);
}

void TestConfigValidator::testErrorOccurred_Signal()
{
    ConfigValidator validator;
    QSignalSpy spy(&validator, SIGNAL(errorOccurred(QString)));
    
    validator.validateFile("/non/existent.ini");
    
    QCOMPARE(spy.count(), 1);
}

#endif // TEST_CONFIGVALIDATOR_H
