#ifndef TEST_FILEWATCHER_H
#define TEST_FILEWATCHER_H

#include <QtTest/QtTest>
#include <QFile>
#include <QTextStream>
#include "test_base.h"
#include "filewatcher.h"

class TestFileWatcher : public TestBase
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    
    // 构造函数和单例测试
    void testFileWatcher_Constructor();
    void testFileWatcher_Instance();
    
    // 添加监控测试
    void testAddWatch_Success();
    void testAddWatch_NonExistentFile();
    void testAddWatch_WrongFormat();
    void testAddWatch_Duplicate();
    
    // 目录监控测试
    void testAddWatchDirectory_Success();
    void testAddWatchDirectory_NonExistent();
    void testAddWatchDirectory_WithFilters();
    
    // 移除监控测试
    void testRemoveWatch_Success();
    void testRemoveWatch_NonExistent();
    
    // 清空监控测试
    void testClearWatches();
    
    // 暂停/恢复监控测试
    void testPauseWatching();
    void testResumeWatching();
    
    // 属性测试
    void testIsWatching();
    void testWatchedFileCount();
    void testWatchedFiles();
    
    // 变更获取测试
    void testGetChangedFiles();
    void testClearChangedFiles();
    
    // 历史记录测试
    void testGetFileHistory();
    
    // 信号测试
    void testFileChanged_Signal();
    void testDirectoryChanged_Signal();
    void testErrorOccurred_Signal();
};

void TestFileWatcher::initTestCase()
{
    qDebug() << "开始 FileWatcher 测试";
}

void TestFileWatcher::cleanupTestCase()
{
    FileWatcher* watcher = FileWatcher::instance();
    if (watcher) {
        watcher->clearWatches();
    }
    qDebug() << "FileWatcher 测试完成";
}

void TestFileWatcher::testFileWatcher_Constructor()
{
    FileWatcher watcher;
    QVERIFY(!watcher.isWatching());
    QCOMPARE(watcher.watchedFileCount(), 0);
    QVERIFY(watcher.watchedFiles().isEmpty());
}

void TestFileWatcher::testFileWatcher_Instance()
{
    FileWatcher* instance1 = FileWatcher::instance();
    FileWatcher* instance2 = FileWatcher::instance();
    
    QVERIFY(instance1 != nullptr);
    QCOMPARE(instance1, instance2);  // 单例
}

void TestFileWatcher::testAddWatch_Success()
{
    FileWatcher watcher;
    
    QString content = "key=value";
    QString filePath = createTempFile(content, ".ini");
    QVERIFY(!filePath.isEmpty());
    
    bool result = watcher.addWatch(filePath);
    QVERIFY(result);
    QVERIFY(watcher.isWatching());
    QCOMPARE(watcher.watchedFileCount(), 1);
}

void TestFileWatcher::testAddWatch_NonExistentFile()
{
    FileWatcher watcher;
    
    QSignalSpy spy(&watcher, SIGNAL(errorOccurred(QString)));
    
    bool result = watcher.addWatch("/non/existent/file.ini");
    QVERIFY(!result);
    QCOMPARE(spy.count(), 1);
}

void TestFileWatcher::testAddWatch_WrongFormat()
{
    FileWatcher watcher;
    
    QString content = "test";
    QString filePath = createTempFile(content, ".txt");
    QVERIFY(!filePath.isEmpty());
    
    // .txt 文件不在过滤列表中
    bool result = watcher.addWatch(filePath);
    QVERIFY(!result);
}

void TestFileWatcher::testAddWatch_Duplicate()
{
    FileWatcher watcher;
    
    QString content = "key=value";
    QString filePath = createTempFile(content, ".ini");
    QVERIFY(!filePath.isEmpty());
    
    watcher.addWatch(filePath);
    bool result = watcher.addWatch(filePath);
    
    // 重复添加应该返回 true（已存在）
    QVERIFY(result);
}

void TestFileWatcher::testAddWatchDirectory_Success()
{
    FileWatcher watcher;
    
    // 创建测试文件
    createTempFile("key1=value1", ".ini");
    createTempFile("key2=value2", ".json");
    
    QString dirPath = m_tempDir.path();
    
    bool result = watcher.addWatchDirectory(dirPath);
    QVERIFY(result);
    QVERIFY(watcher.watchedFileCount() >= 2);
}

void TestFileWatcher::testAddWatchDirectory_NonExistent()
{
    FileWatcher watcher;
    
    QSignalSpy spy(&watcher, SIGNAL(errorOccurred(QString)));
    
    bool result = watcher.addWatchDirectory("/non/existent/directory");
    QVERIFY(!result);
    QCOMPARE(spy.count(), 1);
}

void TestFileWatcher::testAddWatchDirectory_WithFilters()
{
    FileWatcher watcher;
    
    createTempFile("key1=value1", ".ini");
    createTempFile("key2=value2", ".json");
    createTempFile("key3=value3", ".xml");
    
    QString dirPath = m_tempDir.path();
    
    // 只监控.ini 文件
    bool result = watcher.addWatchDirectory(dirPath, QStringList() << "*.ini");
    QVERIFY(result);
    
    // 验证只监控了.ini 文件
    QStringList files = watcher.watchedFiles();
    for (const QString& file : files) {
        QVERIFY(file.endsWith(".ini"));
    }
}

void TestFileWatcher::testRemoveWatch_Success()
{
    FileWatcher watcher;
    
    QString content = "key=value";
    QString filePath = createTempFile(content, ".ini");
    QVERIFY(!filePath.isEmpty());
    
    watcher.addWatch(filePath);
    bool result = watcher.removeWatch(filePath);
    
    QVERIFY(result);
    QCOMPARE(watcher.watchedFileCount(), 0);
}

void TestFileWatcher::testRemoveWatch_NonExistent()
{
    FileWatcher watcher;
    
    bool result = watcher.removeWatch("/non/existent/file.ini");
    QVERIFY(!result);
}

void TestFileWatcher::testClearWatches()
{
    FileWatcher watcher;
    
    createTempFile("key1=value1", ".ini");
    createTempFile("key2=value2", ".ini");
    
    QString dirPath = m_tempDir.path();
    watcher.addWatchDirectory(dirPath);
    
    QVERIFY(watcher.watchedFileCount() > 0);
    
    watcher.clearWatches();
    
    QCOMPARE(watcher.watchedFileCount(), 0);
    QVERIFY(!watcher.isWatching());
}

void TestFileWatcher::testPauseWatching()
{
    FileWatcher watcher;
    
    QString content = "key=value";
    QString filePath = createTempFile(content, ".ini");
    
    watcher.addWatch(filePath);
    watcher.pauseWatching();
    
    // 暂停后文件变更不应该触发信号
    // 这主要通过等待来验证
}

void TestFileWatcher::testResumeWatching()
{
    FileWatcher watcher;
    
    watcher.pauseWatching();
    watcher.resumeWatching();
    
    // 恢复后应该可以正常监控
}

void TestFileWatcher::testIsWatching()
{
    FileWatcher watcher;
    
    QVERIFY(!watcher.isWatching());
    
    QString content = "key=value";
    QString filePath = createTempFile(content, ".ini");
    watcher.addWatch(filePath);
    
    QVERIFY(watcher.isWatching());
}

void TestFileWatcher::testWatchedFileCount()
{
    FileWatcher watcher;
    
    QCOMPARE(watcher.watchedFileCount(), 0);
    
    QString file1 = createTempFile("key1=value1", ".ini");
    QString file2 = createTempFile("key2=value2", ".ini");
    
    watcher.addWatch(file1);
    watcher.addWatch(file2);
    
    QCOMPARE(watcher.watchedFileCount(), 2);
}

void TestFileWatcher::testWatchedFiles()
{
    FileWatcher watcher;
    
    QString file1 = createTempFile("key1=value1", ".ini");
    QString file2 = createTempFile("key2=value2", ".ini");
    
    watcher.addWatch(file1);
    watcher.addWatch(file2);
    
    QStringList files = watcher.watchedFiles();
    QCOMPARE(files.size(), 2);
    QVERIFY(files.contains(file1));
    QVERIFY(files.contains(file2));
}

void TestFileWatcher::testGetChangedFiles()
{
    FileWatcher watcher;
    
    QString content = "key=value";
    QString filePath = createTempFile(content, ".ini");
    
    watcher.addWatch(filePath);
    
    // 初始应该没有变更
    QVariantList changes = watcher.getChangedFiles();
    QCOMPARE(changes.size(), 0);
}

void TestFileWatcher::testClearChangedFiles()
{
    FileWatcher watcher;
    
    watcher.clearChangedFiles();
    
    QVariantList changes = watcher.getChangedFiles();
    QCOMPARE(changes.size(), 0);
}

void TestFileWatcher::testGetFileHistory()
{
    FileWatcher watcher;
    
    QString content = "key=value";
    QString filePath = createTempFile(content, ".ini");
    
    watcher.addWatch(filePath);
    
    // 初始没有历史记录
    QVariantList history = watcher.getFileHistory(filePath, 10);
    QCOMPARE(history.size(), 0);
}

void TestFileWatcher::testFileChanged_Signal()
{
    FileWatcher watcher;
    
    QString content = "key=value";
    QString filePath = createTempFile(content, ".ini");
    
    watcher.addWatch(filePath);
    
    QSignalSpy spy(&watcher, SIGNAL(fileChanged(QString, QString)));
    
    // 修改文件
    QFile file(filePath);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "\nkey2=value2";
        file.close();
    }
    
    // 等待信号（防抖 500ms）
    QVERIFY(spy.wait(2000));
    QCOMPARE(spy.count(), 1);
}

void TestFileWatcher::testDirectoryChanged_Signal()
{
    FileWatcher watcher;
    
    QString dirPath = m_tempDir.path();
    watcher.addWatchDirectory(dirPath);
    
    QSignalSpy spy(&watcher, SIGNAL(directoryChanged(QString)));
    
    // 在目录中创建新文件
    createTempFile("newfile=value", ".ini");
    
    // 等待信号
    QVERIFY(spy.wait(2000));
}

void TestFileWatcher::testErrorOccurred_Signal()
{
    FileWatcher watcher;
    
    QSignalSpy spy(&watcher, SIGNAL(errorOccurred(QString)));
    
    watcher.addWatch("/non/existent/file.ini");
    
    QCOMPARE(spy.count(), 1);
}

#endif // TEST_FILEWATCHER_H
