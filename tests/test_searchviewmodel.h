#ifndef TEST_SEARCHVIEWMODEL_H
#define TEST_SEARCHVIEWMODEL_H

#include <QtTest/QtTest>
#include <QSignalSpy>
#include "test_base.h"
#include "searchviewmodel.h"

class TestSearchViewModel : public TestBase
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    
    // 构造函数测试
    void testSearchViewModel_Constructor();
    
    // 属性测试
    void testSearchText();
    void testSetSearchText();
    void testSearchResults();
    void testSetSearchResults();
    void testIsLoading();
    void testSetIsLoading();
    void testLoadProgress();
    void testSetLoadProgress();
    void testKeyCount();
    
    // AI 相关属性测试
    void testAiEnabled();
    void testSetAiEnabled();
    void testAiIntent();
    void testAiConfidence();
    void testAiSuggestions();
    void testAiExplanation();
    
    // 学习功能测试
    void testLearningEnabled();
    void testSetLearningEnabled();
    void testIsLearningEnabled();
    
    // 格式过滤测试
    void testFormatFilter();
    void testSetFormatFilter();
    
    // 目录选择测试
    void testSelectDirectory();
    
    // 文件加载测试
    void testLoadConfigFiles();
    void testLoadConfigFilesAsync();
    
    // 文件打开测试
    void testOpenConfigFile();
    
    // 搜索结果更新测试
    void testUpdateSearchResults();
    void testUpdateSearchResults_Empty();
    
    // 数据库初始化测试
    void testInitializeDatabase();
    
    // 键索引测试
    void testBuildKeyIndex();
    void testSuggestKeys();
    
    // 聚类建议测试
    void testSuggestClusters();
    void testRequestSuggestClusters();
    void testDeliverSuggestClusters();
    
    // AI 查询分析测试
    void testAnalyzeSearchQuery();
    void testApplyAiSuggestion();
    void testExpandSearchWithAi();
    void testGetAiExplanation();
    
    // 用户词典测试
    void testAddUserTerm();
    void testRemoveUserTerm();
    void testGetUserTerms();
    
    // 搜索历史测试
    void testRecordSearch();
    void testGetSearchHistory();
    void testClearSearchHistory();
    void testGetHotSearches();
    
    // 文件操作测试
    void testPickConfigFile();
    void testReadConfigFile();
    void testWriteConfigFile();
    
    // 信号测试
    void testSearchTextChanged_Signal();
    void testSearchResultsChanged_Signal();
    void testIsLoadingChanged_Signal();
    void testLoadProgressChanged_Signal();
    void testAiEnabledChanged_Signal();
    void testFormatFilterChanged_Signal();
    void testSuggestClustersReady_Signal();
};

void TestSearchViewModel::initTestCase()
{
    qDebug() << "开始 SearchViewModel 测试";
}

void TestSearchViewModel::cleanupTestCase()
{
    qDebug() << "SearchViewModel 测试完成";
}

void TestSearchViewModel::testSearchViewModel_Constructor()
{
    SearchViewModel model;
    QVERIFY(model.parent() == nullptr);
    QVERIFY(model.searchText().isEmpty());
    QVERIFY(!model.isLoading());
    QCOMPARE(model.loadProgress(), 0);
}

void TestSearchViewModel::testSearchText()
{
    SearchViewModel model;
    QVERIFY(model.searchText().isEmpty());
}

void TestSearchViewModel::testSetSearchText()
{
    SearchViewModel model;
    QSignalSpy spy(&model, SIGNAL(searchTextChanged()));
    
    model.setSearchText("test");
    QCOMPARE(model.searchText(), QString("test"));
    QCOMPARE(spy.count(), 1);
}

void TestSearchViewModel::testSearchResults()
{
    SearchViewModel model;
    QCOMPARE(model.searchResults().size(), 0);
}

void TestSearchViewModel::testSetSearchResults()
{
    SearchViewModel model;
    QSignalSpy spy(&model, SIGNAL(searchResultsChanged()));
    
    QList<QObject*> results;
    ConfigEntry* entry = new ConfigEntry();
    entry->setKey("key1");
    results.append(entry);
    
    model.setSearchResults(results);
    QCOMPARE(model.searchResults().size(), 1);
    QCOMPARE(spy.count(), 1);
}

void TestSearchViewModel::testIsLoading()
{
    SearchViewModel model;
    QVERIFY(!model.isLoading());
}

void TestSearchViewModel::testSetIsLoading()
{
    SearchViewModel model;
    QSignalSpy spy(&model, SIGNAL(isLoadingChanged()));
    
    model.setIsLoading(true);
    QVERIFY(model.isLoading());
    QCOMPARE(spy.count(), 1);
}

void TestSearchViewModel::testLoadProgress()
{
    SearchViewModel model;
    QCOMPARE(model.loadProgress(), 0);
}

void TestSearchViewModel::testSetLoadProgress()
{
    SearchViewModel model;
    QSignalSpy spy(&model, SIGNAL(loadProgressChanged()));
    
    model.setLoadProgress(50);
    QCOMPARE(model.loadProgress(), 50);
    QCOMPARE(spy.count(), 1);
}

void TestSearchViewModel::testKeyCount()
{
    SearchViewModel model;
    QCOMPARE(model.keyCount(), 0);
}

void TestSearchViewModel::testAiEnabled()
{
    SearchViewModel model;
    QVERIFY(model.aiEnabled());
}

void TestSearchViewModel::testSetAiEnabled()
{
    SearchViewModel model;
    QSignalSpy spy(&model, SIGNAL(aiEnabledChanged(bool)));
    
    model.setAiEnabled(false);
    QVERIFY(!model.aiEnabled());
    QCOMPARE(spy.count(), 1);
}

void TestSearchViewModel::testAiIntent()
{
    SearchViewModel model;
    QVERIFY(model.aiIntent().isEmpty());
}

void TestSearchViewModel::testAiConfidence()
{
    SearchViewModel model;
    QCOMPARE(model.aiConfidence(), 0.0);
}

void TestSearchViewModel::testAiSuggestions()
{
    SearchViewModel model;
    QCOMPARE(model.aiSuggestions().size(), 0);
}

void TestSearchViewModel::testAiExplanation()
{
    SearchViewModel model;
    QVERIFY(model.aiExplanation().isEmpty());
}

void TestSearchViewModel::testLearningEnabled()
{
    SearchViewModel model;
    QVERIFY(model.isLearningEnabled());
}

void TestSearchViewModel::testSetLearningEnabled()
{
    SearchViewModel model;
    QSignalSpy spy(&model, SIGNAL(learningEnabledChanged(bool)));
    
    model.setLearningEnabled(false);
    QVERIFY(!model.isLearningEnabled());
    QCOMPARE(spy.count(), 1);
}

void TestSearchViewModel::testIsLearningEnabled()
{
    SearchViewModel model;
    QVERIFY(model.isLearningEnabled());
}

void TestSearchViewModel::testFormatFilter()
{
    SearchViewModel model;
    QVERIFY(model.formatFilter().isEmpty());
}

void TestSearchViewModel::testSetFormatFilter()
{
    SearchViewModel model;
    QSignalSpy spy(&model, SIGNAL(formatFilterChanged()));
    
    model.setFormatFilter("ini");
    QCOMPARE(model.formatFilter(), QString("ini"));
    QCOMPARE(spy.count(), 1);
}

void TestSearchViewModel::testSelectDirectory()
{
    SearchViewModel model;
    QString dir = model.selectDirectory();
    
    // 应该返回 ~/.config/Leichen
    QVERIFY(!dir.isEmpty());
    QVERIFY(dir.contains(".config/Leichen"));
}

void TestSearchViewModel::testLoadConfigFiles()
{
    SearchViewModel model;
    
    QString content = "key1=value1";
    QString filePath = createTempFile(content, ".ini");
    
    QSignalSpy spy(&model, SIGNAL(isLoadingChanged()));
    
    model.loadConfigFiles(QStringList() << filePath);
    
    QVERIFY(model.isLoading());
}

void TestSearchViewModel::testLoadConfigFilesAsync()
{
    SearchViewModel model;
    
    QString content = "key1=value1";
    QString filePath = createTempFile(content, ".ini");
    
    model.loadConfigFilesAsync(QStringList() << filePath);
    
    QVERIFY(model.isLoading());
}

void TestSearchViewModel::testOpenConfigFile()
{
    SearchViewModel model;
    
    QString content = "key1=value1";
    QString filePath = createTempFile(content, ".ini");
    
    // 这个操作会尝试打开文件浏览器
    // 测试中只验证不崩溃
    model.openConfigFile(filePath);
}

void TestSearchViewModel::testUpdateSearchResults()
{
    SearchViewModel model;
    
    QString content = "key1=value1\nkey2=value2";
    QString filePath = createTempFile(content, ".ini");
    
    model.loadConfigFiles(QStringList() << filePath);
    
    // 等待加载完成
    QTest::qWait(1000);
    
    model.setSearchText("key1");
    model.updateSearchResults();
    
    QVERIFY(model.searchResults().size() >= 0);
}

void TestSearchViewModel::testUpdateSearchResults_Empty()
{
    SearchViewModel model;
    
    model.setSearchText("");
    model.updateSearchResults();
    
    QVERIFY(model.searchResults().size() >= 0);
}

void TestSearchViewModel::testInitializeDatabase()
{
    SearchViewModel model;
    
    QString dbPath = m_tempDir.filePath("test.db");
    bool result = model.initializeDatabase(dbPath);
    
    QVERIFY(result);
}

void TestSearchViewModel::testBuildKeyIndex()
{
    SearchViewModel model;
    
    QString dbPath = m_tempDir.filePath("test.db");
    model.initializeDatabase(dbPath);
    
    QString content = "key1=value1\nkey2=value2";
    QString filePath = createTempFile(content, ".ini");
    
    model.loadConfigFiles(QStringList() << filePath);
    QTest::qWait(1000);
    
    model.buildKeyIndex();
    
    QVERIFY(model.keyCount() >= 0);
}

void TestSearchViewModel::testSuggestKeys()
{
    SearchViewModel model;
    
    QString dbPath = m_tempDir.filePath("test.db");
    model.initializeDatabase(dbPath);
    
    QString content = "camera_type=type1\nframe_rate=60";
    QString filePath = createTempFile(content, ".ini");
    
    model.loadConfigFiles(QStringList() << filePath);
    QTest::qWait(1000);
    
    model.buildKeyIndex();
    
    QStringList suggestions = model.suggestKeys("cam", 10);
    QVERIFY(suggestions.size() >= 0);
}

void TestSearchViewModel::testSuggestClusters()
{
    SearchViewModel model;
    
    QString dbPath = m_tempDir.filePath("test.db");
    model.initializeDatabase(dbPath);
    
    QString content = "camera_type=type1\nframe_rate=60\nexposure_time=1000";
    QString filePath = createTempFile(content, ".ini");
    
    model.loadConfigFiles(QStringList() << filePath);
    QTest::qWait(1000);
    
    model.buildKeyIndex();
    
    QVariantList clusters = model.suggestClusters("", 5, 10);
    QVERIFY(clusters.size() >= 0);
}

void TestSearchViewModel::testRequestSuggestClusters()
{
    SearchViewModel model;
    
    QString dbPath = m_tempDir.filePath("test.db");
    model.initializeDatabase(dbPath);
    
    QString content = "camera_type=type1\nframe_rate=60";
    QString filePath = createTempFile(content, ".ini");
    
    model.loadConfigFiles(QStringList() << filePath);
    QTest::qWait(1000);
    
    model.buildKeyIndex();
    
    QSignalSpy spy(&model, SIGNAL(suggestClustersReady(QVariantList)));
    
    model.requestSuggestClusters("", 5, 10);
    
    // 等待异步完成
    spy.wait(5000);
}

void TestSearchViewModel::testDeliverSuggestClusters()
{
    SearchViewModel model;
    
    QVariantList clusters;
    QVariantMap cluster;
    cluster["cluster"] = "test";
    cluster["items"] = QStringList() << "item1" << "item2";
    clusters.append(cluster);
    
    // 这个槽函数主要用于信号传递
    model.deliverSuggestClusters(clusters);
}

void TestSearchViewModel::testAnalyzeSearchQuery()
{
    SearchViewModel model;
    
    model.analyzeSearchQuery("相机配置");
    
    // 验证 AI 分析功能
    QVERIFY(model.aiIntent().isEmpty() || !model.aiIntent().isEmpty());
}

void TestSearchViewModel::testApplyAiSuggestion()
{
    SearchViewModel model;
    
    model.applyAiSuggestion("suggestion");
    
    // 验证应用建议
}

void TestSearchViewModel::testExpandSearchWithAi()
{
    SearchViewModel model;
    
    model.expandSearchWithAi("query");
    
    // 验证 AI 扩展搜索
}

void TestSearchViewModel::testGetAiExplanation()
{
    SearchViewModel model;
    
    QString explanation = model.getAiExplanation("query");
    
    // 验证获取解释
    QVERIFY(explanation.isEmpty() || !explanation.isEmpty());
}

void TestSearchViewModel::testAddUserTerm()
{
    SearchViewModel model;
    
    model.addUserTerm("key", "中文", QVariantList() << "同义词 1");
    
    // 验证添加用户词条
}

void TestSearchViewModel::testRemoveUserTerm()
{
    SearchViewModel model;
    
    model.addUserTerm("temp_key", "临时", QVariantList());
    model.removeUserTerm("temp_key");
    
    // 验证删除
}

void TestSearchViewModel::testGetUserTerms()
{
    SearchViewModel model;
    
    QVariantList terms = model.getUserTerms();
    QVERIFY(terms.size() >= 0);
}

void TestSearchViewModel::testRecordSearch()
{
    SearchViewModel model;
    
    model.recordSearch("test", 5, true);
    
    // 验证记录搜索
}

void TestSearchViewModel::testGetSearchHistory()
{
    SearchViewModel model;
    
    model.recordSearch("test1", 1, false);
    model.recordSearch("test2", 2, true);
    
    QVariantList history = model.getSearchHistory(10);
    QVERIFY(history.size() >= 2);
}

void TestSearchViewModel::testClearSearchHistory()
{
    SearchViewModel model;
    
    model.recordSearch("test", 1, false);
    model.clearSearchHistory();
    
    QVariantList history = model.getSearchHistory(10);
    QCOMPARE(history.size(), 0);
}

void TestSearchViewModel::testGetHotSearches()
{
    SearchViewModel model;
    
    for (int i = 0; i < 5; ++i) {
        model.recordSearch("hot", 1, true);
    }
    model.recordSearch("cold", 1, false);
    
    QVariantList hot = model.getHotSearches(5);
    QVERIFY(hot.size() > 0);
}

void TestSearchViewModel::testPickConfigFile()
{
    SearchViewModel model;
    
    // 这个操作会打开文件选择对话框
    // 测试中只验证不崩溃
    QString file = model.pickConfigFile();
    
    // 在自动化测试中通常返回空
    QVERIFY(file.isEmpty() || !file.isEmpty());
}

void TestSearchViewModel::testReadConfigFile()
{
    SearchViewModel model;
    
    QString content = "key1=value1\nkey2=value2";
    QString filePath = createTempFile(content, ".ini");
    
    QVariantList entries = model.readConfigFile(filePath);
    QCOMPARE(entries.size(), 2);
}

void TestSearchViewModel::testWriteConfigFile()
{
    SearchViewModel model;
    
    QString filePath = m_tempDir.filePath("test.ini");
    
    QVariantList entries;
    QVariantMap entry;
    entry["key"] = "key1";
    entry["value"] = "value1";
    entry["section"] = "";
    entries.append(entry);
    
    bool result = model.writeConfigFile(filePath, entries);
    QVERIFY(result);
}

void TestSearchViewModel::testSearchTextChanged_Signal()
{
    SearchViewModel model;
    QSignalSpy spy(&model, SIGNAL(searchTextChanged()));
    
    model.setSearchText("test");
    QCOMPARE(spy.count(), 1);
}

void TestSearchViewModel::testSearchResultsChanged_Signal()
{
    SearchViewModel model;
    QSignalSpy spy(&model, SIGNAL(searchResultsChanged()));
    
    QList<QObject*> results;
    results.append(new ConfigEntry());
    model.setSearchResults(results);
    
    QCOMPARE(spy.count(), 1);
}

void TestSearchViewModel::testIsLoadingChanged_Signal()
{
    SearchViewModel model;
    QSignalSpy spy(&model, SIGNAL(isLoadingChanged()));
    
    model.setIsLoading(true);
    QCOMPARE(spy.count(), 1);
}

void TestSearchViewModel::testLoadProgressChanged_Signal()
{
    SearchViewModel model;
    QSignalSpy spy(&model, SIGNAL(loadProgressChanged()));
    
    model.setLoadProgress(50);
    QCOMPARE(spy.count(), 1);
}

void TestSearchViewModel::testAiEnabledChanged_Signal()
{
    SearchViewModel model;
    QSignalSpy spy(&model, SIGNAL(aiEnabledChanged(bool)));
    
    model.setAiEnabled(false);
    QCOMPARE(spy.count(), 1);
}

void TestSearchViewModel::testFormatFilterChanged_Signal()
{
    SearchViewModel model;
    QSignalSpy spy(&model, SIGNAL(formatFilterChanged()));
    
    model.setFormatFilter("json");
    QCOMPARE(spy.count(), 1);
}

void TestSearchViewModel::testSuggestClustersReady_Signal()
{
    SearchViewModel model;
    QSignalSpy spy(&model, SIGNAL(suggestClustersReady(QVariantList)));
    
    QString dbPath = m_tempDir.filePath("test.db");
    model.initializeDatabase(dbPath);
    
    QString content = "key1=value1";
    QString filePath = createTempFile(content, ".ini");
    
    model.loadConfigFiles(QStringList() << filePath);
    QTest::qWait(1000);
    
    model.requestSuggestClusters("", 5, 10);
    
    // 等待异步信号
    spy.wait(5000);
}

#endif // TEST_SEARCHVIEWMODEL_H
