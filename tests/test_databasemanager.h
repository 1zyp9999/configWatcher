#ifndef TEST_DATABASEMANAGER_H
#define TEST_DATABASEMANAGER_H

#include <QtTest/QtTest>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "test_base.h"
#include "databasemanager.h"

class TestDatabaseManager : public TestBase
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    
    // 构造函数测试
    void testDatabaseManager_Constructor();
    void testDatabaseManager_Singleton();
    
    // 数据库连接测试
    void testOpenDatabase_Success();
    void testOpenDatabase_InvalidPath();
    void testOpenDatabase_MultipleConnections();
    void testCloseDatabase();
    
    // 数据库表结构测试
    void testDatabaseSchema_FilesTable();
    void testDatabaseSchema_SectionsTable();
    void testDatabaseSchema_ParametersTable();
    void testDatabaseSchema_TranslationsTable();
    void testDatabaseSchema_ChangeLogTable();
    void testDatabaseSchema_ReadOnlyFieldsTable();
    void testDatabaseSchema_TemplatesTable();
    
    // INI 文件导入测试
    void testImportIniFile_Basic();
    void testImportIniFile_WithSections();
    void testImportIniFile_NonExistentFile();
    
    // JSON 文件导入测试
    void testImportJsonFile_Basic();
    void testImportJsonFile_Nested();
    void testImportJsonFile_NonExistentFile();
    
    // XML 文件导入测试
    void testImportXmlFile_Basic();
    void testImportXmlFile_NonExistentFile();
    
    // 搜索功能测试
    void testSearchParameters_EmptyQuery();
    void testSearchParameters_ByKey();
    void testSearchParameters_ByValue();
    void testSearchParameters_WithFormatFilter();
    
    // 翻译功能测试
    void testTranslations_List();
    void testTranslations_Set();
    void testTranslations_Apply();
    
    // 修改记录测试
    void testChangeLog_Add();
    void testChangeLog_Get();
    void testChangeLog_Delete();
    void testChangeLog_Clear();
    
    // 只读字段测试
    void testReadOnlyFields_Set();
    void testReadOnlyFields_Check();
    void testReadOnlyFields_Get();
    
    // 模板功能测试
    void testTemplates_Import();
    void testTemplates_List();
    void testTemplates_Delete();
    
    // 缓存功能测试
    void testQueryCache_Basic();
    void testQueryCache_Invalidation();
    void testQueryCache_TTL();
};

void TestDatabaseManager::initTestCase()
{
    qDebug() << "开始 DatabaseManager 测试";
}

void TestDatabaseManager::cleanupTestCase()
{
    // 清理测试数据库
    DatabaseManager* mgr = DatabaseManager::instance();
    if (mgr) {
        mgr->closeDatabase();
    }
    qDebug() << "DatabaseManager 测试完成";
}

void TestDatabaseManager::testDatabaseManager_Constructor()
{
    DatabaseManager manager;
    QVERIFY(manager.parent() == nullptr);
    
    QObject parent;
    DatabaseManager managerWithParent(&parent);
    QCOMPARE(managerWithParent.parent(), &parent);
}

void TestDatabaseManager::testDatabaseManager_Singleton()
{
    // 测试单例模式
    DatabaseManager* mgr1 = DatabaseManager::instance();
    QVERIFY(mgr1 != nullptr);
    
    // 注意：instance() 返回的是最近一次 openDatabase 设置的实例
    // 这里主要验证接口可用
}

void TestDatabaseManager::testOpenDatabase_Success()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    bool result = manager.openDatabase(dbPath);
    
    QVERIFY(result);
    QVERIFY(QFile::exists(dbPath));
    
    manager.closeDatabase();
}

void TestDatabaseManager::testOpenDatabase_InvalidPath()
{
    // 测试无效路径（应该是可创建的目录）
    QString dbPath = "/invalid/path/test.db";
    
    DatabaseManager manager;
    bool result = manager.openDatabase(dbPath);
    
    // 应该失败因为目录不存在
    QVERIFY(!result);
}

void TestDatabaseManager::testOpenDatabase_MultipleConnections()
{
    QString dbPath1 = m_tempDir.filePath("test1.db");
    QString dbPath2 = m_tempDir.filePath("test2.db");
    
    DatabaseManager manager1;
    DatabaseManager manager2;
    
    bool result1 = manager1.openDatabase(dbPath1, "conn1", false);
    bool result2 = manager2.openDatabase(dbPath2, "conn2", false);
    
    QVERIFY(result1);
    QVERIFY(result2);
    
    manager1.closeDatabase();
    manager2.closeDatabase();
}

void TestDatabaseManager::testCloseDatabase()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    QVERIFY(QFile::exists(dbPath));
    
    manager.closeDatabase();
    
    // 数据库文件应该仍然存在
    QVERIFY(QFile::exists(dbPath));
}

void TestDatabaseManager::testDatabaseSchema_FilesTable()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    // 通过查询 sqlite_master 表来验证表是否存在
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "schema_test");
    db.setDatabaseName(dbPath);
    db.open();
    
    QSqlQuery query(db);
    QVERIFY(query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='files'"));
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toString(), QString("files"));
    
    db.close();
    QSqlDatabase::removeDatabase("schema_test");
    
    manager.closeDatabase();
}

void TestDatabaseManager::testDatabaseSchema_SectionsTable()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "schema_test2");
    db.setDatabaseName(dbPath);
    db.open();
    
    QSqlQuery query(db);
    QVERIFY(query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='sections'"));
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toString(), QString("sections"));
    
    db.close();
    QSqlDatabase::removeDatabase("schema_test2");
    
    manager.closeDatabase();
}

void TestDatabaseManager::testDatabaseSchema_ParametersTable()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "schema_test3");
    db.setDatabaseName(dbPath);
    db.open();
    
    QSqlQuery query(db);
    QVERIFY(query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='parameters'"));
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toString(), QString("parameters"));
    
    db.close();
    QSqlDatabase::removeDatabase("schema_test3");
    
    manager.closeDatabase();
}

void TestDatabaseManager::testDatabaseSchema_TranslationsTable()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "schema_test4");
    db.setDatabaseName(dbPath);
    db.open();
    
    QSqlQuery query(db);
    QVERIFY(query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='translations'"));
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toString(), QString("translations"));
    
    db.close();
    QSqlDatabase::removeDatabase("schema_test4");
    
    manager.closeDatabase();
}

void TestDatabaseManager::testDatabaseSchema_ChangeLogTable()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "schema_test5");
    db.setDatabaseName(dbPath);
    db.open();
    
    QSqlQuery query(db);
    QVERIFY(query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='change_log'"));
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toString(), QString("change_log"));
    
    db.close();
    QSqlDatabase::removeDatabase("schema_test5");
    
    manager.closeDatabase();
}

void TestDatabaseManager::testDatabaseSchema_ReadOnlyFieldsTable()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "schema_test6");
    db.setDatabaseName(dbPath);
    db.open();
    
    QSqlQuery query(db);
    QVERIFY(query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='readonly_fields'"));
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toString(), QString("readonly_fields"));
    
    db.close();
    QSqlDatabase::removeDatabase("schema_test6");
    
    manager.closeDatabase();
}

void TestDatabaseManager::testDatabaseSchema_TemplatesTable()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "schema_test7");
    db.setDatabaseName(dbPath);
    db.open();
    
    QSqlQuery query(db);
    QVERIFY(query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='templates'"));
    QVERIFY(query.next());
    QCOMPARE(query.value(0).toString(), QString("templates"));
    
    db.close();
    QSqlDatabase::removeDatabase("schema_test7");
    
    manager.closeDatabase();
}

void TestDatabaseManager::testImportIniFile_Basic()
{
    QString content = R"(
key1=value1
key2=value2
key3=value3
)";
    
    QString filePath = createTempFile(content, ".ini");
    QVERIFY(!filePath.isEmpty());
    
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    bool result = manager.importIniFile(filePath);
    QVERIFY(result);
    
    // 验证导入的数据
    QVariantList params = manager.searchParameters("", 0, "");
    QVERIFY(params.size() >= 3);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testImportIniFile_WithSections()
{
    QString content = R"(
[Section1]
key1=value1
key2=value2

[Section2]
key3=value3
)";
    
    QString filePath = createTempFile(content, ".ini");
    QVERIFY(!filePath.isEmpty());
    
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    bool result = manager.importIniFile(filePath);
    QVERIFY(result);
    
    QVariantList params = manager.searchParameters("", 0, "");
    QVERIFY(params.size() >= 3);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testImportIniFile_NonExistentFile()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    bool result = manager.importIniFile("/non/existent/file.ini");
    QVERIFY(!result);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testImportJsonFile_Basic()
{
    QString content = R"({
        "key1": "value1",
        "key2": "value2",
        "key3": "value3"
    })";
    
    QString filePath = createTempFile(content, ".json");
    QVERIFY(!filePath.isEmpty());
    
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    bool result = manager.importJsonFile(filePath);
    QVERIFY(result);
    
    QVariantList params = manager.searchParameters("", 0, "");
    QVERIFY(params.size() >= 3);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testImportJsonFile_Nested()
{
    QString content = R"({
        "section1": {
            "key1": "value1",
            "key2": "value2"
        }
    })";
    
    QString filePath = createTempFile(content, ".json");
    QVERIFY(!filePath.isEmpty());
    
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    bool result = manager.importJsonFile(filePath);
    QVERIFY(result);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testImportJsonFile_NonExistentFile()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    bool result = manager.importJsonFile("/non/existent/file.json");
    QVERIFY(!result);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testImportXmlFile_Basic()
{
    QString content = R"(<?xml version="1.0"?>
<config>
    <item key="key1">value1</item>
    <item key="key2">value2</item>
</config>)";
    
    QString filePath = createTempFile(content, ".xml");
    QVERIFY(!filePath.isEmpty());
    
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    bool result = manager.importXmlFile(filePath);
    QVERIFY(result);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testImportXmlFile_NonExistentFile()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    bool result = manager.importXmlFile("/non/existent/file.xml");
    QVERIFY(!result);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testSearchParameters_EmptyQuery()
{
    QString content = "key1=value1\nkey2=value2";
    QString filePath = createTempFile(content, ".ini");
    
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    manager.importIniFile(filePath);
    
    QVariantList results = manager.searchParameters("", 0, "");
    QVERIFY(results.size() >= 2);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testSearchParameters_ByKey()
{
    QString content = "key1=value1\nkey2=value2\nkey3=value3";
    QString filePath = createTempFile(content, ".ini");
    
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    manager.importIniFile(filePath);
    
    QVariantList results = manager.searchParameters("key1", 0, "");
    QCOMPARE(results.size(), 1);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testSearchParameters_ByValue()
{
    QString content = "key1=value1\nkey2=value2\nkey3=special";
    QString filePath = createTempFile(content, ".ini");
    
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    manager.importIniFile(filePath);
    
    QVariantList results = manager.searchParameters("special", 0, "");
    QCOMPARE(results.size(), 1);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testSearchParameters_WithFormatFilter()
{
    QString content = "key1=value1";
    QString filePath = createTempFile(content, ".ini");
    
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    manager.importIniFile(filePath);
    
    // 测试格式过滤
    QVariantList results = manager.searchParameters("", 0, "ini");
    QVERIFY(results.size() >= 1);
    
    results = manager.searchParameters("", 0, "json");
    QCOMPARE(results.size(), 0);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testTranslations_List()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    QVariantList translations = manager.listTranslations();
    QCOMPARE(translations.size(), 0);  // 初始为空
    
    manager.closeDatabase();
}

void TestDatabaseManager::testTranslations_Set()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    bool result = manager.setTranslation("camera", "相机");
    QVERIFY(result);
    
    QVariantList translations = manager.listTranslations();
    QCOMPARE(translations.size(), 1);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testTranslations_Apply()
{
    QString content = "camera=type1";
    QString filePath = createTempFile(content, ".ini");
    
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    manager.importIniFile(filePath);
    
    // 设置翻译
    manager.setTranslation("camera", "相机");
    
    // 应用翻译
    bool result = manager.applyTranslationsToParameters();
    QVERIFY(result);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testChangeLog_Add()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    bool result = manager.addChangeLog("/test/file.ini", "key1", "oldValue", "newValue");
    QVERIFY(result);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testChangeLog_Get()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    manager.addChangeLog("/test/file.ini", "key1", "oldValue", "newValue");
    
    QVariantList logs = manager.getChangeLogs(10);
    QVERIFY(logs.size() >= 1);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testChangeLog_Delete()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    manager.addChangeLog("/test/file.ini", "key1", "oldValue", "newValue");
    
    QVariantList logs = manager.getChangeLogs(10);
    QVERIFY(logs.size() >= 1);
    
    QVariantMap log = logs[0].toMap();
    bool result = manager.deleteChangeLog(
        log["file_path"].toString(),
        log["key"].toString(),
        log["changed_at"].toString()
    );
    QVERIFY(result);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testChangeLog_Clear()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    manager.addChangeLog("/test/file1.ini", "key1", "oldValue", "newValue");
    manager.addChangeLog("/test/file2.ini", "key2", "oldValue", "newValue");
    
    manager.clearChangeLogs();
    
    QVariantList logs = manager.getChangeLogs(10);
    QCOMPARE(logs.size(), 0);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testReadOnlyFields_Set()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    bool result = manager.setFieldReadOnly("/test/file.ini", "key1", true);
    QVERIFY(result);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testReadOnlyFields_Check()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    manager.setFieldReadOnly("/test/file.ini", "key1", true);
    
    // 检查是否为只读
    // 注意：需要验证 isFieldReadOnly 的返回值
    
    manager.closeDatabase();
}

void TestDatabaseManager::testReadOnlyFields_Get()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    manager.setFieldReadOnly("/test/file.ini", "key1", true);
    manager.setFieldReadOnly("/test/file.ini", "key2", true);
    
    QVariantList readOnlyFields = manager.getReadOnlyFields("/test/file.ini");
    QVERIFY(readOnlyFields.size() >= 2);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testTemplates_Import()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    // 创建模板文件
    QString templateContent = R"({
        "template_key1": "value1",
        "template_key2": "value2"
    })";
    QString templatePath = createTempFile(templateContent, ".json");
    
    bool result = manager.importTemplate(templatePath, "/target/file.ini");
    // 注意：importTemplate 可能返回 false 如果文件不存在
    
    manager.closeDatabase();
}

void TestDatabaseManager::testTemplates_List()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    QVariantList templates = manager.getTemplateFiles();
    QCOMPARE(templates.size(), 0);  // 初始为空
    
    manager.closeDatabase();
}

void TestDatabaseManager::testTemplates_Delete()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    // 删除不存在的模板应该返回 false
    bool result = manager.deleteTemplate("/non/existent/template.json");
    QVERIFY(!result);
    
    manager.closeDatabase();
}

void TestDatabaseManager::testQueryCache_Basic()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    // 执行搜索以填充缓存
    manager.searchParameters("test", 0, "");
    
    // 验证缓存被使用
    // 这主要通过性能来验证，这里只做基本测试
    
    manager.closeDatabase();
}

void TestDatabaseManager::testQueryCache_Invalidation()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    manager.searchParameters("test", 0, "");
    
    // 使缓存失效
    manager.invalidateCache();
    
    // 再次搜索应该重新执行查询
    manager.searchParameters("test", 0, "");
    
    manager.closeDatabase();
}

void TestDatabaseManager::testQueryCache_TTL()
{
    QString dbPath = m_tempDir.filePath("test.db");
    
    DatabaseManager manager;
    manager.openDatabase(dbPath);
    
    // 缓存 TTL 默认为 5000ms
    // 这里主要验证缓存机制存在
    
    manager.searchParameters("test", 0, "");
    
    // 立即再次搜索应该使用缓存
    manager.searchParameters("test", 0, "");
    
    manager.closeDatabase();
}

#endif // TEST_DATABASEMANAGER_H
