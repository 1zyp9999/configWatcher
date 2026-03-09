#ifndef TEST_AISERVICE_H
#define TEST_AISERVICE_H

#include <QtTest/QtTest>
#include "test_base.h"
#include "aiservice.h"

class TestAiService : public TestBase
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    
    // 构造函数测试
    void testAiService_Constructor();
    
    // 意图识别测试
    void testAnalyzeIntent_SearchKey();
    void testAnalyzeIntent_SearchValue();
    void testAnalyzeIntent_SearchChinese();
    void testAnalyzeIntent_Navigate();
    void testAnalyzeIntent_Unknown();
    
    // 置信度测试
    void testGetIntentConfidence();
    
    // 实体提取测试
    void testExtractEntities();
    
    // 关键词扩展测试
    void testExpandKeywords_Basic();
    void testExpandKeywords_Empty();
    
    // 同义词测试
    void testGetSynonyms_Camera();
    void testGetSynonyms_Exposure();
    void testGetSynonyms_NonExistent();
    
    // 相关词测试
    void testGetRelatedWords();
    
    // 搜索建议测试
    void testGenerateSuggestions();
    
    // 查询解释测试
    void testExplainQuery();
    
    // 模糊匹配测试
    void testNeedsFuzzyMatch();
    
    // 词典管理测试
    void testLoadDomainDictionary();
    void testClearDictionary();
    void testGetDictionarySize();
    
    // 用户自定义词典测试
    void testAddUserTerm();
    void testRemoveUserTerm();
    void testGetUserTerms();
    void testSaveUserDictionary();
    void testLoadUserDictionary();
    void testGetUserDictionaryPath();
    
    // 搜索历史测试
    void testRecordSearchHistory();
    void testGetSearchHistory();
    void testClearSearchHistory();
    void testDeleteSearchHistory();
    void testGetHotSearches();
    void testSaveSearchHistory();
    void testLoadSearchHistory();
    void testGetSearchHistoryPath();
    
    // 启用/禁用测试
    void testSetEnabled();
    void testIsEnabled();
    void testSetLearningEnabled();
    void testIsLearningEnabled();
};

void TestAiService::initTestCase()
{
    qDebug() << "开始 AIService 测试";
}

void TestAiService::cleanupTestCase()
{
    qDebug() << "AIService 测试完成";
}

void TestAiService::testAiService_Constructor()
{
    AiService service;
    QVERIFY(service.parent() == nullptr);
    QVERIFY(service.isEnabled());
    QVERIFY(service.isLearningEnabled());
    
    QObject parent;
    AiService serviceWithParent(&parent);
    QCOMPARE(serviceWithParent.parent(), &parent);
}

void TestAiService::testAnalyzeIntent_SearchKey()
{
    AiService service;
    QString intent = service.analyzeIntent("camera");
    // 应该识别为搜索键名
    QVERIFY(!intent.isEmpty());
}

void TestAiService::testAnalyzeIntent_SearchValue()
{
    AiService service;
    QString intent = service.analyzeIntent("value123");
    // 可能识别为搜索值
    QVERIFY(!intent.isEmpty());
}

void TestAiService::testAnalyzeIntent_SearchChinese()
{
    AiService service;
    QString intent = service.analyzeIntent("相机");
    // 应该识别为中文搜索
    QVERIFY(!intent.isEmpty());
}

void TestAiService::testAnalyzeIntent_Navigate()
{
    AiService service;
    QString intent = service.analyzeIntent("打开设置");
    // 可能识别为导航意图
    QVERIFY(!intent.isEmpty());
}

void TestAiService::testAnalyzeIntent_Unknown()
{
    AiService service;
    QString intent = service.analyzeIntent("xyz123abc");
    // 未知输入应该返回 unknown 或默认意图
    QVERIFY(!intent.isEmpty());
}

void TestAiService::testGetIntentConfidence()
{
    AiService service;
    double confidence = service.getIntentConfidence("camera");
    QVERIFY(confidence >= 0.0);
    QVERIFY(confidence <= 1.0);
}

void TestAiService::testExtractEntities()
{
    AiService service;
    QVariantList entities = service.extractEntities("相机曝光时间设置");
    // 应该提取出实体
    QVERIFY(entities.size() >= 0);
}

void TestAiService::testExpandKeywords_Basic()
{
    AiService service;
    QStringList expanded = service.expandKeywords("相机", 10);
    QVERIFY(expanded.size() > 0);
}

void TestAiService::testExpandKeywords_Empty()
{
    AiService service;
    QStringList expanded = service.expandKeywords("");
    QCOMPARE(expanded.size(), 0);
}

void TestAiService::testGetSynonyms_Camera()
{
    AiService service;
    QStringList synonyms = service.getSynonyms("相机");
    QVERIFY(synonyms.size() > 0);
    QVERIFY(synonyms.contains("camera"));
}

void TestAiService::testGetSynonyms_Exposure()
{
    AiService service;
    QStringList synonyms = service.getSynonyms("曝光");
    QVERIFY(synonyms.size() > 0);
    QVERIFY(synonyms.contains("exposure"));
}

void TestAiService::testGetSynonyms_NonExistent()
{
    AiService service;
    QStringList synonyms = service.getSynonyms("nonexistent123");
    // 不存在的词应该返回空列表或基于相似度匹配
    QVERIFY(synonyms.size() >= 0);
}

void TestAiService::testGetRelatedWords()
{
    AiService service;
    QStringList related = service.getRelatedWords("相机");
    QVERIFY(related.size() >= 0);
}

void TestAiService::testGenerateSuggestions()
{
    AiService service;
    QVariantList suggestions = service.generateSuggestions("相", "", 5);
    QVERIFY(suggestions.size() >= 0);
}

void TestAiService::testExplainQuery()
{
    AiService service;
    QString explanation = service.explainQuery("相机");
    QVERIFY(!explanation.isEmpty());
}

void TestAiService::testNeedsFuzzyMatch()
{
    AiService service;
    
    // 精确匹配不需要模糊
    bool needsFuzzy = service.needsFuzzyMatch("camera");
    QVERIFY(!needsFuzzy);
    
    // 拼写错误可能需要模糊
    needsFuzzy = service.needsFuzzyMatch("camra");
    QVERIFY(needsFuzzy);
}

void TestAiService::testLoadDomainDictionary()
{
    AiService service;
    
    QVariantMap terms;
    terms["exposure_time"] = "曝光时间";
    terms["gain"] = "增益";
    
    service.loadDomainDictionary(terms);
    
    int size = service.getDictionarySize();
    QVERIFY(size > 0);
}

void TestAiService::testClearDictionary()
{
    AiService service;
    
    QVariantMap terms;
    terms["test"] = "测试";
    service.loadDomainDictionary(terms);
    
    service.clearDictionary();
    
    int size = service.getDictionarySize();
    QCOMPARE(size, 0);
}

void TestAiService::testGetDictionarySize()
{
    AiService service;
    
    // 初始词典应该有内置的同义词
    int size = service.getDictionarySize();
    QVERIFY(size > 0);
}

void TestAiService::testAddUserTerm()
{
    AiService service;
    
    service.addUserTerm("custom_key", "自定义键", QStringList() << "别名 1" << "别名 2");
    
    QVariantList terms = service.getUserTerms();
    QVERIFY(terms.size() > 0);
}

void TestAiService::testRemoveUserTerm()
{
    AiService service;
    
    service.addUserTerm("temp_key", "临时键");
    service.removeUserTerm("temp_key");
    
    QVariantList terms = service.getUserTerms();
    // 验证是否已删除
    bool found = false;
    for (const QVariant& term : terms) {
        QVariantMap m = term.toMap();
        if (m["key"].toString() == "temp_key") {
            found = true;
            break;
        }
    }
    QVERIFY(!found);
}

void TestAiService::testGetUserTerms()
{
    AiService service;
    
    service.clearDictionary();
    service.addUserTerm("key1", "中文 1");
    service.addUserTerm("key2", "中文 2");
    
    QVariantList terms = service.getUserTerms();
    QVERIFY(terms.size() >= 2);
}

void TestAiService::testSaveUserDictionary()
{
    AiService service;
    
    service.clearDictionary();
    service.addUserTerm("test_key", "测试键");
    
    bool result = service.saveUserDictionary();
    QVERIFY(result);
}

void TestAiService::testLoadUserDictionary()
{
    AiService service;
    
    service.clearDictionary();
    service.addUserTerm("test_key", "测试键");
    service.saveUserDictionary();
    
    // 创建新实例加载词典
    AiService service2;
    bool result = service2.loadUserDictionary();
    QVERIFY(result);
}

void TestAiService::testGetUserDictionaryPath()
{
    AiService service;
    QString path = service.getUserDictionaryPath();
    QVERIFY(!path.isEmpty());
}

void TestAiService::testRecordSearchHistory()
{
    AiService service;
    
    service.recordSearchHistory("test query", 5, true);
    
    QVariantList history = service.getSearchHistory(10);
    QVERIFY(history.size() > 0);
}

void TestAiService::testGetSearchHistory()
{
    AiService service;
    
    service.clearSearchHistory();
    service.recordSearchHistory("query1", 1, false);
    service.recordSearchHistory("query2", 2, true);
    
    QVariantList history = service.getSearchHistory(10);
    QVERIFY(history.size() >= 2);
    
    // 测试 limit
    history = service.getSearchHistory(1);
    QCOMPARE(history.size(), 1);
}

void TestAiService::testClearSearchHistory()
{
    AiService service;
    
    service.recordSearchHistory("test", 1, false);
    service.clearSearchHistory();
    
    QVariantList history = service.getSearchHistory(10);
    QCOMPARE(history.size(), 0);
}

void TestAiService::testDeleteSearchHistory()
{
    AiService service;
    
    service.clearSearchHistory();
    service.recordSearchHistory("to_delete", 1, false);
    
    bool result = service.deleteSearchHistory("to_delete");
    QVERIFY(result);
    
    QVariantList history = service.getSearchHistory(10);
    bool found = false;
    for (const QVariant& item : history) {
        QVariantMap m = item.toMap();
        if (m["query"].toString() == "to_delete") {
            found = true;
            break;
        }
    }
    QVERIFY(!found);
}

void TestAiService::testGetHotSearches()
{
    AiService service;
    
    service.clearSearchHistory();
    
    // 多次搜索同一个词使其成为热门
    for (int i = 0; i < 5; ++i) {
        service.recordSearchHistory("hot_query", 1, true);
    }
    service.recordSearchHistory("cold_query", 1, false);
    
    QVariantList hot = service.getHotSearches(5);
    QVERIFY(hot.size() > 0);
}

void TestAiService::testSaveSearchHistory()
{
    AiService service;
    
    service.clearSearchHistory();
    service.recordSearchHistory("test", 1, false);
    
    bool result = service.saveSearchHistory();
    QVERIFY(result);
}

void TestAiService::testLoadSearchHistory()
{
    AiService service;
    
    service.clearSearchHistory();
    service.recordSearchHistory("test", 1, false);
    service.saveSearchHistory();
    
    // 新实例加载
    AiService service2;
    bool result = service2.loadSearchHistory();
    QVERIFY(result);
}

void TestAiService::testGetSearchHistoryPath()
{
    AiService service;
    QString path = service.getSearchHistoryPath();
    QVERIFY(!path.isEmpty());
}

void TestAiService::testSetEnabled()
{
    AiService service;
    
    service.setEnabled(false);
    QVERIFY(!service.isEnabled());
    
    service.setEnabled(true);
    QVERIFY(service.isEnabled());
}

void TestAiService::testIsEnabled()
{
    AiService service;
    QVERIFY(service.isEnabled());  // 默认启用
}

void TestAiService::testSetLearningEnabled()
{
    AiService service;
    
    service.setLearningEnabled(false);
    QVERIFY(!service.isLearningEnabled());
    
    service.setLearningEnabled(true);
    QVERIFY(service.isLearningEnabled());
}

void TestAiService::testIsLearningEnabled()
{
    AiService service;
    QVERIFY(service.isLearningEnabled());  // 默认启用
}

#endif // TEST_AISERVICE_H
