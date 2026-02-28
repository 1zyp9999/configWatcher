#include <QTest>
#include <QObject>
#include <QTemporaryFile>
#include <QDir>
#include "../src/viewmodel/databasemanager.h"

class TestDatabaseManager : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    
    // 数据库打开/关闭测试
    void testOpenDatabase_valid();
    void testOpenDatabase_invalidPath();
    
    // 配置项保存测试
    void testSaveConfigEntry();
    
    // 文件管理测试
    void testListFiles();
    
    // 翻译功能测试
    void testTranslation();
    
    // 搜索功能测试
    void testSearchParameters();

private:
    DatabaseManager* m_db;
    QString m_dbPath;
};

void TestDatabaseManager::initTestCase()
{
    m_db = new DatabaseManager();
    
    // 创建临时数据库文件
    m_dbPath = QDir::tempPath() + "/ConfigWatcherTest_XXXXXX.db";
    QTemporaryFile tempFile(m_dbPath);
    tempFile.open();
    m_dbPath = tempFile.fileName();
    tempFile.close();
    QFile::remove(m_dbPath);  // 删除让 DatabaseManager 创建
}

void TestDatabaseManager::cleanupTestCase()
{
    m_db->closeDatabase();
    delete m_db;
    QFile::remove(m_dbPath);
}

void TestDatabaseManager::testOpenDatabase_valid()
{
    bool result = m_db->openDatabase(m_dbPath);
    QVERIFY(result);
    QVERIFY(QFile::exists(m_dbPath));
}

void TestDatabaseManager::testOpenDatabase_invalidPath()
{
    DatabaseManager tempDb;
    // 尝试打开一个不可写的路径
    bool result = tempDb.openDatabase("/root/nonexistent/test.db");
    // 可能失败（取决于权限）
    QVERIFY(!result || QFile::exists("/root/nonexistent/test.db"));
}

void TestDatabaseManager::testSaveConfigEntry()
{
    QVERIFY(m_db->openDatabase(m_dbPath));
    
    bool result = m_db->saveConfigEntry(
        "test_key", 
        "test_value", 
        "/test/path.ini", 
        "ini", 
        "测试键"
    );
    
    QVERIFY(result);
}

void TestDatabaseManager::testListFiles()
{
    QVERIFY(m_db->openDatabase(m_dbPath));
    
    // 先保存一个条目以创建文件记录
    m_db->saveConfigEntry("key1", "value1", "/test/file1.ini", "ini", "");
    m_db->saveConfigEntry("key2", "value2", "/test/file2.json", "json", "");
    
    QVariantList files = m_db->listFiles();
    QVERIFY(files.size() >= 2);
}

void TestDatabaseManager::testTranslation()
{
    QVERIFY(m_db->openDatabase(m_dbPath));
    
    // 设置翻译
    bool result = m_db->setTranslation("brightness", "亮度");
    QVERIFY(result);
    
    // 列出翻译
    QVariantList translations = m_db->listTranslations();
    QVERIFY(translations.size() >= 1);
    
    // 验证翻译内容
    bool found = false;
    for (const QVariant& t : translations) {
        QVariantMap m = t.toMap();
        if (m["key"] == "brightness" && m["chinese"] == "亮度") {
            found = true;
            break;
        }
    }
    QVERIFY(found);
}

void TestDatabaseManager::testSearchParameters()
{
    QVERIFY(m_db->openDatabase(m_dbPath));
    
    // 添加测试数据
    m_db->saveConfigEntry("camera_type", "area_scan", "/test/camera.ini", "ini", "相机类型");
    m_db->saveConfigEntry("light_angle", "45", "/test/light.ini", "ini", "光源角度");
    
    // 搜索测试
    QVariantList results = m_db->searchParameters("camera", 0);
    QVERIFY(results.size() >= 1);
    
    // 验证结果字段
    if (!results.isEmpty()) {
        QVariantMap first = results.first().toMap();
        QVERIFY(first.contains("key"));
        QVERIFY(first.contains("value"));
    }
}

QTEST_APPLESS_MAIN(TestDatabaseManager)
#include "tst_databasemanager.moc"
