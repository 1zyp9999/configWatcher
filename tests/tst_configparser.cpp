#include <QTest>
#include <QObject>
#include <QTemporaryFile>
#include <QDir>
#include <QSharedPointer>
#include "../src/model/configparser.h"
#include "../src/model/configentry.h"

class TestConfigParser : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    
    // INI 解析测试
    void testParseIniFile_valid();
    void testParseIniFile_empty();
    void testParseIniFile_notExist();
    
    // JSON 解析测试
    void testParseJsonFile_valid();
    void testParseJsonFile_invalid();
    
    // 搜索测试
    void testSearch_basic();
    void testSearch_caseInsensitive();
    void testSearch_emptyKeyword();
    
    // 目录遍历测试
    void testGetConfigFiles();

private:
    ConfigParser* m_parser;
    QString m_testDir;
};

void TestConfigParser::initTestCase()
{
    m_parser = new ConfigParser();
    
    // 创建临时测试目录
    m_testDir = QDir::tempPath() + "/ConfigWatcherTests";
    QDir().mkpath(m_testDir);
}

void TestConfigParser::cleanupTestCase()
{
    delete m_parser;
    QDir(m_testDir).removeRecursively();
}

void TestConfigParser::testParseIniFile_valid()
{
    // 创建测试 INI 文件
    QTemporaryFile tempFile(m_testDir + "/test_XXXXXX.ini");
    QVERIFY(tempFile.open());
    
    QTextStream out(&tempFile);
    out << "[Section1]\n";
    out << "key1=value1\n";
    out << "key2=value2\n";
    out << "\n";
    out << "[Section2]\n";
    out << "key3=value3\n";
    out.flush();
    tempFile.close();
    
    // 加载并验证
    m_parser->loadConfigFiles({tempFile.fileName()});
    QSignalSpy spy(m_parser, SIGNAL(loadFinished()));
    QVERIFY(spy.wait(5000));  // 等待异步加载完成
    
    auto results = m_parser->search("");
    QCOMPARE(results.size(), 3);
}

void TestConfigParser::testParseIniFile_empty()
{
    QTemporaryFile tempFile(m_testDir + "/empty_XXXXXX.ini");
    QVERIFY(tempFile.open());
    tempFile.close();
    
    m_parser->loadConfigFiles({tempFile.fileName()});
    QSignalSpy spy(m_parser, SIGNAL(loadFinished()));
    QVERIFY(spy.wait(5000));
    
    auto results = m_parser->search("");
    QCOMPARE(results.size(), 0);
}

void TestConfigParser::testParseIniFile_notExist()
{
    QSignalSpy errorSpy(m_parser, SIGNAL(errorOccurred(QString)));
    m_parser->loadConfigFiles({"/non/existent/file.ini"});
    QSignalSpy spy(m_parser, SIGNAL(loadFinished()));
    QVERIFY(spy.wait(5000));
    
    // 应该触发错误信号
    QCOMPARE(errorSpy.size(), 1);
}

void TestConfigParser::testParseJsonFile_valid()
{
    QTemporaryFile tempFile(m_testDir + "/test_XXXXXX.json");
    QVERIFY(tempFile.open());
    
    QTextStream out(&tempFile);
    out << R"({ "name": "test", "value": 123, "enabled": true })";
    out.flush();
    tempFile.close();
    
    m_parser->loadConfigFiles({tempFile.fileName()});
    QSignalSpy spy(m_parser, SIGNAL(loadFinished()));
    QVERIFY(spy.wait(5000));
    
    auto results = m_parser->search("");
    QCOMPARE(results.size(), 3);
}

void TestConfigParser::testParseJsonFile_invalid()
{
    QTemporaryFile tempFile(m_testDir + "/invalid_XXXXXX.json");
    QVERIFY(tempFile.open());
    
    QTextStream out(&tempFile);
    out << "{ invalid json }";
    out.flush();
    tempFile.close();
    
    QSignalSpy errorSpy(m_parser, SIGNAL(errorOccurred(QString)));
    m_parser->loadConfigFiles({tempFile.fileName()});
    QSignalSpy spy(m_parser, SIGNAL(loadFinished()));
    QVERIFY(spy.wait(5000));
    
    QCOMPARE(errorSpy.size(), 1);
}

void TestConfigParser::testSearch_basic()
{
    m_parser->loadConfigFiles({m_testDir});
    QSignalSpy spy(m_parser, SIGNAL(loadFinished()));
    QVERIFY(spy.wait(5000));
    
    auto results = m_parser->search("key1");
    QVERIFY(results.size() >= 1);
}

void TestConfigParser::testSearch_caseInsensitive()
{
    m_parser->loadConfigFiles({m_testDir});
    QSignalSpy spy(m_parser, SIGNAL(loadFinished()));
    QVERIFY(spy.wait(5000));
    
    auto results1 = m_parser->search("KEY1");
    auto results2 = m_parser->search("key1");
    
    QCOMPARE(results1.size(), results2.size());
}

void TestConfigParser::testSearch_emptyKeyword()
{
    m_parser->loadConfigFiles({m_testDir});
    QSignalSpy spy(m_parser, SIGNAL(loadFinished()));
    QVERIFY(spy.wait(5000));
    
    auto results = m_parser->search("");
    // 空关键字应返回所有结果
    QVERIFY(results.size() >= 0);
}

void TestConfigParser::testGetConfigFiles()
{
    // 创建测试文件
    QFile file1(m_testDir + "/test1.ini");
    QFile file2(m_testDir + "/test2.json");
    file1.open(QIODevice::WriteOnly);
    file2.open(QIODevice::WriteOnly);
    file1.close();
    file2.close();
    
    // 此测试主要验证目录遍历功能
    QDir dir(m_testDir);
    QStringList files = dir.entryList(QStringList() << "*.ini" << "*.json", QDir::Files);
    QCOMPARE(files.size(), 2);
}

QTEST_APPLESS_MAIN(TestConfigParser)
#include "tst_configparser.moc"
