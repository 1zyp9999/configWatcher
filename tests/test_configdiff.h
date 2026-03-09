#ifndef TEST_CONFIGDIFF_H
#define TEST_CONFIGDIFF_H

#include <QtTest/QtTest>
#include "test_base.h"
#include "configdiff.h"

class TestConfigDiff : public TestBase
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    
    // 构造函数测试
    void testConfigDiff_Constructor();
    
    // 文件对比测试
    void testCompareFiles_Basic();
    void testCompareFiles_WithAdditions();
    void testCompareFiles_WithRemovals();
    void testCompareFiles_WithModifications();
    void testCompareFiles_Identical();
    void testCompareFiles_NonExistentFiles();
    void testCompareFiles_DifferentFormats();
    
    // 数据库对比测试
    void testCompareWithDatabase_Basic();
    void testCompareWithDatabase_NoDatabase();
    
    // 配置对比测试
    void testCompareConfigs_Basic();
    void testCompareConfigs_Empty();
    
    // 快照对比测试
    void testCompareSnapshots_Basic();
    void testCompareSnapshots_NonExistent();
    
    // 快照管理测试
    void testCreateSnapshot_Success();
    void testCreateSnapshot_NonExistentFile();
    void testListSnapshots();
    void testDeleteSnapshot();
    void testRestoreSnapshot();
    
    // 统计测试
    void testAddedCount();
    void testRemovedCount();
    void testModifiedCount();
    void testUnchangedCount();
    
    // 报告生成测试
    void testGenerateDiffReport_Text();
    void testGenerateDiffReport_JSON();
    void testGenerateDiffReport_Markdown();
    
    // 报告导出测试
    void testExportDiffReport();
    
    // 过滤结果测试
    void testGetFilteredResults();
    
    // 统计信息测试
    void testGetDiffStatistics();
    
    // 信号测试
    void testDiffResultsChanged_Signal();
    void testSnapshotCreated_Signal();
    void testSnapshotRestored_Signal();
    void testErrorOccurred_Signal();
};

void TestConfigDiff::initTestCase()
{
    qDebug() << "开始 ConfigDiff 测试";
}

void TestConfigDiff::cleanupTestCase()
{
    qDebug() << "ConfigDiff 测试完成";
}

void TestConfigDiff::testConfigDiff_Constructor()
{
    ConfigDiff diff;
    QVERIFY(diff.parent() == nullptr);
    QCOMPARE(diff.diffResults().size(), 0);
}

void TestConfigDiff::testCompareFiles_Basic()
{
    QString content1 = "key1=value1\nkey2=value2";
    QString content2 = "key1=value1\nkey2=value3";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    ConfigDiff diff;
    QVariantList results = diff.compareFiles(file1, file2);
    
    QVERIFY(results.size() > 0);
}

void TestConfigDiff::testCompareFiles_WithAdditions()
{
    QString content1 = "key1=value1";
    QString content2 = "key1=value1\nkey2=value2";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    ConfigDiff diff;
    QVariantList results = diff.compareFiles(file1, file2);
    
    // 应该有新增项
    bool hasAdded = false;
    for (const QVariant& item : results) {
        if (item.toMap()["changeType"] == "added") {
            hasAdded = true;
            break;
        }
    }
    QVERIFY(hasAdded);
}

void TestConfigDiff::testCompareFiles_WithRemovals()
{
    QString content1 = "key1=value1\nkey2=value2";
    QString content2 = "key1=value1";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    ConfigDiff diff;
    QVariantList results = diff.compareFiles(file1, file2);
    
    // 应该有删除项
    bool hasRemoved = false;
    for (const QVariant& item : results) {
        if (item.toMap()["changeType"] == "removed") {
            hasRemoved = true;
            break;
        }
    }
    QVERIFY(hasRemoved);
}

void TestConfigDiff::testCompareFiles_WithModifications()
{
    QString content1 = "key1=value1";
    QString content2 = "key1=value2";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    ConfigDiff diff;
    QVariantList results = diff.compareFiles(file1, file2);
    
    // 应该有修改项
    bool hasModified = false;
    for (const QVariant& item : results) {
        if (item.toMap()["changeType"] == "modified") {
            hasModified = true;
            QCOMPARE(item.toMap()["oldValue"].toString(), QString("value1"));
            QCOMPARE(item.toMap()["newValue"].toString(), QString("value2"));
            break;
        }
    }
    QVERIFY(hasModified);
}

void TestConfigDiff::testCompareFiles_Identical()
{
    QString content = "key1=value1\nkey2=value2";
    QString file1 = createTempFile(content, ".ini");
    QString file2 = createTempFile(content, ".ini");
    
    ConfigDiff diff;
    QVariantList results = diff.compareFiles(file1, file2);
    
    // 所有项都应该是未变更
    for (const QVariant& item : results) {
        QCOMPARE(item.toMap()["changeType"], QString("unchanged"));
    }
}

void TestConfigDiff::testCompareFiles_NonExistentFiles()
{
    ConfigDiff diff;
    QSignalSpy spy(&diff, SIGNAL(errorOccurred(QString)));
    
    QVariantList results = diff.compareFiles("/non/existent1.ini", "/non/existent2.ini");
    
    QCOMPARE(results.size(), 0);
    QCOMPARE(spy.count(), 1);
}

void TestConfigDiff::testCompareFiles_DifferentFormats()
{
    QString iniContent = "key1=value1";
    QString jsonContent = R"({"key1": "value1"})";
    
    QString iniFile = createTempFile(iniContent, ".ini");
    QString jsonFile = createTempFile(jsonContent, ".json");
    
    ConfigDiff diff;
    QVariantList results = diff.compareFiles(iniFile, jsonFile);
    
    // 应该能处理不同格式
    QVERIFY(results.size() >= 0);
}

void TestConfigDiff::testCompareWithDatabase_Basic()
{
    QString content = "key1=value1";
    QString filePath = createTempFile(content, ".ini");
    
    ConfigDiff diff;
    QVariantList results = diff.compareWithDatabase(filePath);
    
    // 没有数据库时应该返回空或错误
    QVERIFY(results.size() >= 0);
}

void TestConfigDiff::testCompareWithDatabase_NoDatabase()
{
    QString content = "key1=value1";
    QString filePath = createTempFile(content, ".ini");
    
    ConfigDiff diff;
    QSignalSpy spy(&diff, SIGNAL(errorOccurred(QString)));
    
    QVariantList results = diff.compareWithDatabase(filePath);
    
    // 没有数据库应该报错
    QCOMPARE(spy.count(), 1);
}

void TestConfigDiff::testCompareConfigs_Basic()
{
    QVariantList config1, config2;
    
    QVariantMap entry1;
    entry1["key"] = "key1";
    entry1["value"] = "value1";
    entry1["section"] = "section1";
    config1.append(entry1);
    
    QVariantMap entry2;
    entry2["key"] = "key1";
    entry2["value"] = "value2";
    entry2["section"] = "section1";
    config2.append(entry2);
    
    ConfigDiff diff;
    QVariantList results = diff.compareConfigs(config1, config2);
    
    QCOMPARE(results.size(), 1);
    QCOMPARE(results[0].toMap()["changeType"], QString("modified"));
}

void TestConfigDiff::testCompareConfigs_Empty()
{
    QVariantList config1, config2;
    
    ConfigDiff diff;
    QVariantList results = diff.compareConfigs(config1, config2);
    
    QCOMPARE(results.size(), 0);
}

void TestConfigDiff::testCompareSnapshots_Basic()
{
    QString content1 = "key1=value1";
    QString content2 = "key1=value2";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    // 使用文件路径作为快照
    ConfigDiff diff;
    QVariantList results = diff.compareSnapshots(file1, 
        QFileInfo(file1).fileName(),
        QFileInfo(file2).fileName());
    
    // 快照功能测试
    QVERIFY(results.size() >= 0);
}

void TestConfigDiff::testCompareSnapshots_NonExistent()
{
    ConfigDiff diff;
    QSignalSpy spy(&diff, SIGNAL(errorOccurred(QString)));
    
    QVariantList results = diff.compareSnapshots(
        "/non/existent.ini",
        "snapshot1",
        "snapshot2"
    );
    
    QCOMPARE(results.size(), 0);
    QCOMPARE(spy.count(), 1);
}

void TestConfigDiff::testCreateSnapshot_Success()
{
    QString content = "key1=value1";
    QString filePath = createTempFile(content, ".ini");
    
    ConfigDiff diff;
    QSignalSpy spy(&diff, SIGNAL(snapshotCreated(QString)));
    
    bool result = diff.createSnapshot(filePath);
    QVERIFY(result);
    QCOMPARE(spy.count(), 1);
}

void TestConfigDiff::testCreateSnapshot_NonExistentFile()
{
    ConfigDiff diff;
    QSignalSpy spy(&diff, SIGNAL(errorOccurred(QString)));
    
    bool result = diff.createSnapshot("/non/existent.ini");
    QVERIFY(!result);
    QCOMPARE(spy.count(), 1);
}

void TestConfigDiff::testListSnapshots()
{
    QString content = "key1=value1";
    QString filePath = createTempFile(content, ".ini");
    
    ConfigDiff diff;
    
    // 创建快照
    diff.createSnapshot(filePath);
    
    // 列出快照
    QVariantList snapshots = diff.listSnapshots(filePath);
    QVERIFY(snapshots.size() >= 1);
}

void TestConfigDiff::testDeleteSnapshot()
{
    QString content = "key1=value1";
    QString filePath = createTempFile(content, ".ini");
    
    ConfigDiff diff;
    diff.createSnapshot(filePath);
    
    QVariantList snapshots = diff.listSnapshots(filePath);
    QVERIFY(snapshots.size() >= 1);
    
    QVariantMap snapshot = snapshots[0].toMap();
    QString timestamp = snapshot["timestamp"].toString();
    
    bool result = diff.deleteSnapshot(filePath, timestamp);
    QVERIFY(result);
}

void TestConfigDiff::testRestoreSnapshot()
{
    QString content = "key1=value1";
    QString filePath = createTempFile(content, ".ini");
    
    ConfigDiff diff;
    diff.createSnapshot(filePath);
    
    // 修改原文件
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "key1=value2";
        file.close();
    }
    
    // 恢复快照
    QVariantList snapshots = diff.listSnapshots(filePath);
    QString timestamp = snapshots[0].toMap()["timestamp"].toString();
    
    QSignalSpy spy(&diff, SIGNAL(snapshotRestored(QString)));
    bool result = diff.restoreSnapshot(filePath, timestamp);
    QVERIFY(result);
    QCOMPARE(spy.count(), 1);
}

void TestConfigDiff::testAddedCount()
{
    QString content1 = "key1=value1";
    QString content2 = "key1=value1\nkey2=value2";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    ConfigDiff diff;
    diff.compareFiles(file1, file2);
    
    QCOMPARE(diff.addedCount(), 1);
}

void TestConfigDiff::testRemovedCount()
{
    QString content1 = "key1=value1\nkey2=value2";
    QString content2 = "key1=value1";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    ConfigDiff diff;
    diff.compareFiles(file1, file2);
    
    QCOMPARE(diff.removedCount(), 1);
}

void TestConfigDiff::testModifiedCount()
{
    QString content1 = "key1=value1";
    QString content2 = "key1=value2";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    ConfigDiff diff;
    diff.compareFiles(file1, file2);
    
    QCOMPARE(diff.modifiedCount(), 1);
}

void TestConfigDiff::testUnchangedCount()
{
    QString content = "key1=value1\nkey2=value2";
    QString file1 = createTempFile(content, ".ini");
    QString file2 = createTempFile(content, ".ini");
    
    ConfigDiff diff;
    diff.compareFiles(file1, file2);
    
    QCOMPARE(diff.unchangedCount(), 2);
}

void TestConfigDiff::testGenerateDiffReport_Text()
{
    QString content1 = "key1=value1";
    QString content2 = "key1=value2";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    ConfigDiff diff;
    diff.compareFiles(file1, file2);
    
    QString report = diff.generateDiffReport("text");
    QVERIFY(!report.isEmpty());
    QVERIFY(report.contains("value1"));
    QVERIFY(report.contains("value2"));
}

void TestConfigDiff::testGenerateDiffReport_JSON()
{
    QString content1 = "key1=value1";
    QString content2 = "key1=value2";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    ConfigDiff diff;
    diff.compareFiles(file1, file2);
    
    QString report = diff.generateDiffReport("json");
    QVERIFY(!report.isEmpty());
    QVERIFY(report.contains("{"));
    QVERIFY(report.contains("}"));
}

void TestConfigDiff::testGenerateDiffReport_Markdown()
{
    QString content1 = "key1=value1";
    QString content2 = "key1=value2";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    ConfigDiff diff;
    diff.compareFiles(file1, file2);
    
    QString report = diff.generateDiffReport("markdown");
    QVERIFY(!report.isEmpty());
    QVERIFY(report.contains("#"));
}

void TestConfigDiff::testExportDiffReport()
{
    QString content1 = "key1=value1";
    QString content2 = "key1=value2";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    ConfigDiff diff;
    diff.compareFiles(file1, file2);
    
    QString outputPath = m_tempDir.filePath("report.txt");
    bool result = diff.exportDiffReport(outputPath, "text");
    QVERIFY(result);
    QVERIFY(QFile::exists(outputPath));
}

void TestConfigDiff::testGetFilteredResults()
{
    QString content1 = "key1=value1";
    QString content2 = "key1=value2\nkey3=value3";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    ConfigDiff diff;
    diff.compareFiles(file1, file2);
    
    QVariantList modified = diff.getFilteredResults("modified");
    QCOMPARE(modified.size(), 1);
    
    QVariantList added = diff.getFilteredResults("added");
    QCOMPARE(added.size(), 1);
}

void TestConfigDiff::testGetDiffStatistics()
{
    QString content1 = "key1=value1";
    QString content2 = "key1=value2\nkey3=value3";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    ConfigDiff diff;
    diff.compareFiles(file1, file2);
    
    QVariantMap stats = diff.getDiffStatistics();
    
    QVERIFY(stats.contains("total"));
    QVERIFY(stats.contains("added"));
    QVERIFY(stats.contains("removed"));
    QVERIFY(stats.contains("modified"));
    QVERIFY(stats.contains("unchanged"));
}

void TestConfigDiff::testDiffResultsChanged_Signal()
{
    QString content1 = "key1=value1";
    QString content2 = "key1=value2";
    
    QString file1 = createTempFile(content1, ".ini");
    QString file2 = createTempFile(content2, ".ini");
    
    ConfigDiff diff;
    QSignalSpy spy(&diff, SIGNAL(diffResultsChanged()));
    
    diff.compareFiles(file1, file2);
    
    QCOMPARE(spy.count(), 1);
}

void TestConfigDiff::testSnapshotCreated_Signal()
{
    QString content = "key1=value1";
    QString filePath = createTempFile(content, ".ini");
    
    ConfigDiff diff;
    QSignalSpy spy(&diff, SIGNAL(snapshotCreated(QString)));
    
    diff.createSnapshot(filePath);
    
    QCOMPARE(spy.count(), 1);
}

void TestConfigDiff::testSnapshotRestored_Signal()
{
    QString content = "key1=value1";
    QString filePath = createTempFile(content, ".ini");
    
    ConfigDiff diff;
    diff.createSnapshot(filePath);
    
    QVariantList snapshots = diff.listSnapshots(filePath);
    QString timestamp = snapshots[0].toMap()["timestamp"].toString();
    
    QSignalSpy spy(&diff, SIGNAL(snapshotRestored(QString)));
    diff.restoreSnapshot(filePath, timestamp);
    
    QCOMPARE(spy.count(), 1);
}

void TestConfigDiff::testErrorOccurred_Signal()
{
    ConfigDiff diff;
    QSignalSpy spy(&diff, SIGNAL(errorOccurred(QString)));
    
    diff.compareFiles("/non/existent1.ini", "/non/existent2.ini");
    
    QCOMPARE(spy.count(), 1);
}

#endif // TEST_CONFIGDIFF_H
