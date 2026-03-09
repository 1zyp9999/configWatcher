#ifndef TEST_CONFIGENTRY_H
#define TEST_CONFIGENTRY_H

#include <QtTest/QtTest>
#include "test_base.h"
#include "configentry.h"

class TestConfigEntry : public TestBase
{
    Q_OBJECT

private slots:
    // 初始化
    void initTestCase();
    void cleanupTestCase();
    
    // ConfigEntry 基本功能测试
    void testConfigEntry_Constructor();
    void testConfigEntry_Key();
    void testConfigEntry_Value();
    void testConfigEntry_FilePath();
    void testConfigEntry_Format();
    void testConfigEntry_ChineseKey();
    
    // ConfigEntry 重置功能测试
    void testConfigEntry_Reset();
    
    // ConfigEntry 信号测试
    void testConfigEntry_Signals();
    
    // ConfigEntryPool 测试
    void testConfigEntryPool_Acquire();
    void testConfigEntryPool_Release();
    void testConfigEntryPool_MultipleAcquire();
    void testConfigEntryPool_PoolSizeLimit();
    void testConfigEntryPool_Clear();
    
    // ConfigEntry 对象池集成测试
    void testConfigEntryPool_Integration();
};

void TestConfigEntry::initTestCase()
{
    // 测试前初始化
    qDebug() << "开始 ConfigEntry 测试";
}

void TestConfigEntry::cleanupTestCase()
{
    // 测试后清理
    ConfigEntryPool::instance().clear();
    qDebug() << "ConfigEntry 测试完成";
}

void TestConfigEntry::testConfigEntry_Constructor()
{
    // 测试默认构造函数
    ConfigEntry entry;
    QVERIFY(entry.key().isEmpty());
    QVERIFY(entry.value().isEmpty());
    QVERIFY(entry.filePath().isEmpty());
    QVERIFY(entry.format().isEmpty());
    QVERIFY(entry.chineseKey().isEmpty());
    
    // 测试带父对象的构造函数
    QObject parent;
    ConfigEntry entryWithParent(&parent);
    QCOMPARE(entryWithParent.parent(), &parent);
}

void TestConfigEntry::testConfigEntry_Key()
{
    ConfigEntry entry;
    
    // 测试设置和获取 key
    entry.setKey("test.key");
    QCOMPARE(entry.key(), QString("test.key"));
    
    // 测试空 key
    entry.setKey("");
    QVERIFY(entry.key().isEmpty());
    
    // 测试特殊字符
    entry.setKey("section.subsection.key");
    QCOMPARE(entry.key(), QString("section.subsection.key"));
}

void TestConfigEntry::testConfigEntry_Value()
{
    ConfigEntry entry;
    
    // 测试设置和获取 value
    entry.setValue("test value");
    QCOMPARE(entry.value(), QString("test value"));
    
    // 测试空 value
    entry.setValue("");
    QVERIFY(entry.value().isEmpty());
    
    // 测试特殊字符
    entry.setValue("value with = and : symbols");
    QCOMPARE(entry.value(), QString("value with = and : symbols"));
}

void TestConfigEntry::testConfigEntry_FilePath()
{
    ConfigEntry entry;
    
    // 测试设置和获取 filePath
    entry.setFilePath("/path/to/config.ini");
    QCOMPARE(entry.filePath(), QString("/path/to/config.ini"));
    
    // 测试空 filePath
    entry.setFilePath("");
    QVERIFY(entry.filePath().isEmpty());
}

void TestConfigEntry::testConfigEntry_Format()
{
    ConfigEntry entry;
    
    // 测试设置和获取 format
    entry.setFormat("ini");
    QCOMPARE(entry.format(), QString("ini"));
    
    entry.setFormat("json");
    QCOMPARE(entry.format(), QString("json"));
    
    entry.setFormat("xml");
    QCOMPARE(entry.format(), QString("xml"));
}

void TestConfigEntry::testConfigEntry_ChineseKey()
{
    ConfigEntry entry;
    
    // 测试设置和获取 chineseKey
    entry.setChineseKey("相机");
    QCOMPARE(entry.chineseKey(), QString("相机"));
    
    entry.setChineseKey("曝光时间");
    QCOMPARE(entry.chineseKey(), QString("曝光时间"));
}

void TestConfigEntry::testConfigEntry_Reset()
{
    ConfigEntry entry;
    
    // 设置值
    entry.setKey("test.key");
    entry.setValue("value");
    entry.setFilePath("/path/to/file.ini");
    entry.setFormat("ini");
    entry.setChineseKey("测试键");
    
    // 验证值已设置
    QCOMPARE(entry.key(), QString("test.key"));
    QCOMPARE(entry.value(), QString("value"));
    QCOMPARE(entry.filePath(), QString("/path/to/file.ini"));
    QCOMPARE(entry.format(), QString("ini"));
    QCOMPARE(entry.chineseKey(), QString("测试键"));
    
    // 重置
    entry.reset();
    
    // 验证所有值已清空
    QVERIFY(entry.key().isEmpty());
    QVERIFY(entry.value().isEmpty());
    QVERIFY(entry.filePath().isEmpty());
    QVERIFY(entry.format().isEmpty());
    QVERIFY(entry.chineseKey().isEmpty());
}

void TestConfigEntry::testConfigEntry_Signals()
{
    ConfigEntry entry;
    QSignalSpy keySpy(&entry, SIGNAL(keyChanged()));
    QSignalSpy valueSpy(&entry, SIGNAL(valueChanged()));
    QSignalSpy filePathSpy(&entry, SIGNAL(filePathChanged()));
    QSignalSpy formatSpy(&entry, SIGNAL(formatChanged()));
    QSignalSpy chineseKeySpy(&entry, SIGNAL(chineseKeyChanged()));
    
    // 测试 keyChanged 信号
    entry.setKey("test.key");
    QCOMPARE(keySpy.count(), 1);
    
    // 测试 valueChanged 信号
    entry.setValue("value");
    QCOMPARE(valueSpy.count(), 1);
    
    // 测试 filePathChanged 信号
    entry.setFilePath("/path/to/file");
    QCOMPARE(filePathSpy.count(), 1);
    
    // 测试 formatChanged 信号
    entry.setFormat("json");
    QCOMPARE(formatSpy.count(), 1);
    
    // 测试 chineseKeyChanged 信号
    entry.setChineseKey("测试");
    QCOMPARE(chineseKeySpy.count(), 1);
}

void TestConfigEntry::testConfigEntryPool_Acquire()
{
    // 清空对象池
    ConfigEntryPool::instance().clear();
    
    // 从对象池获取对象
    ConfigEntry* entry = ConfigEntryPool::instance().acquire();
    QVERIFY(entry != nullptr);
    
    // 验证获取的对象是干净的
    QVERIFY(entry->key().isEmpty());
    QVERIFY(entry->value().isEmpty());
    
    delete entry;
}

void TestConfigEntry::testConfigEntryPool_Release()
{
    ConfigEntryPool::instance().clear();
    
    // 获取并释放对象
    ConfigEntry* entry = ConfigEntryPool::instance().acquire();
    entry->setKey("test.key");
    entry->setValue("value");
    
    ConfigEntryPool::instance().release(entry);
    
    // 验证对象池大小
    QCOMPARE(ConfigEntryPool::instance().size(), 1);
}

void TestConfigEntry::testConfigEntryPool_MultipleAcquire()
{
    ConfigEntryPool::instance().clear();
    
    // 获取多个对象
    QList<ConfigEntry*> entries;
    for (int i = 0; i < 5; ++i) {
        entries.append(ConfigEntryPool::instance().acquire());
    }
    
    // 验证对象池大小
    QCOMPARE(ConfigEntryPool::instance().size(), 0);
    
    // 清理
    for (ConfigEntry* entry : entries) {
        delete entry;
    }
}

void TestConfigEntry::testConfigEntryPool_PoolSizeLimit()
{
    ConfigEntryPool::instance().clear();
    
    // 获取并释放超过池大小限制的对象
    int poolLimit = 100;
    for (int i = 0; i < 150; ++i) {
        ConfigEntry* entry = ConfigEntryPool::instance().acquire();
        ConfigEntryPool::instance().release(entry);
    }
    
    // 验证对象池大小不超过限制
    QVERIFY(ConfigEntryPool::instance().size() <= poolLimit);
}

void TestConfigEntry::testConfigEntryPool_Clear()
{
    ConfigEntryPool::instance().clear();
    
    // 获取并释放一些对象
    for (int i = 0; i < 10; ++i) {
        ConfigEntry* entry = ConfigEntryPool::instance().acquire();
        ConfigEntryPool::instance().release(entry);
    }
    
    QVERIFY(ConfigEntryPool::instance().size() > 0);
    
    // 清空对象池
    ConfigEntryPool::instance().clear();
    
    // 验证对象池已清空
    QCOMPARE(ConfigEntryPool::instance().size(), 0);
}

void TestConfigEntry::testConfigEntryPool_Integration()
{
    ConfigEntryPool::instance().clear();
    
    // 获取对象并设置值
    ConfigEntry* entry1 = ConfigEntryPool::instance().acquire();
    entry1->setKey("key1");
    entry1->setValue("value1");
    
    // 释放对象
    ConfigEntryPool::instance().release(entry1);
    
    // 再次获取对象，验证是否复用
    ConfigEntry* entry2 = ConfigEntryPool::instance().acquire();
    QCOMPARE(entry2, entry1);  // 应该是同一个对象
    
    // 验证对象已被重置
    QVERIFY(entry2->key().isEmpty());
    QVERIFY(entry2->value().isEmpty());
}

#endif // TEST_CONFIGENTRY_H
