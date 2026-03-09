#ifndef TEST_AICLIENT_H
#define TEST_AICLIENT_H

#include <QtTest/QtTest>
#include "test_base.h"
#include "aiclient.h"

class TestAiClient : public TestBase
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    
    // 构造函数和单例测试
    void testAiClient_Constructor();
    void testAiClient_Instance();
    
    // 属性测试
    void testIsEnabled();
    void testSetEnabled();
    void testProvider();
    void testSetProvider();
    void testApiKey();
    void testSetApiKey();
    void testModel();
    void testSetModel();
    void testBaseUrl();
    void testSetBaseUrl();
    void testIsProcessing();
    void testLastError();
    void testTemperature();
    void testSetTemperature();
    void testMaxTokens();
    void testSetMaxTokens();
    
    // Provider 切换测试
    void testSetProvider_OpenAI();
    void testSetProvider_Azure();
    void testSetProvider_Ollama();
    void testSetProvider_Custom();
    
    // 功能测试（无 API 密钥时的行为）
    void testAnalyzeIntent_NoApiKey();
    void testExpandKeywords_NoApiKey();
    void testSuggestSearchTerms_NoApiKey();
    void testExplainConfig_NoApiKey();
    void testValidateConfig_NoApiKey();
    void testChat_NoApiKey();
    void testCompletePrompt_NoApiKey();
    
    // 对话历史测试
    void testGetConversationHistory();
    void testClearConversationHistory();
    
    // 请求中止测试
    void testAbortRequest();
    
    // 设置保存加载测试
    void testLoadSettings();
    void testSaveSettings();
    
    // 信号测试
    void testEnabledChanged_Signal();
    void testProviderChanged_Signal();
    void testApiKeyChanged_Signal();
    void testModelChanged_Signal();
    void testBaseUrlChanged_Signal();
    void testProcessingChanged_Signal();
    void testErrorOccurred_Signal();
    void testTemperatureChanged_Signal();
    void testMaxTokensChanged_Signal();
};

void TestAiClient::initTestCase()
{
    qDebug() << "开始 AIClient 测试";
}

void TestAiClient::cleanupTestCase()
{
    qDebug() << "AIClient 测试完成";
}

void TestAiClient::testAiClient_Constructor()
{
    AiClient client;
    QVERIFY(client.parent() == nullptr);
    QVERIFY(!client.isEnabled());  // 默认禁用
    QCOMPARE(client.provider(), QString("openai"));
    QVERIFY(client.apiKey().isEmpty());
    QCOMPARE(client.model(), QString("gpt-3.5-turbo"));
    QVERIFY(!client.isProcessing());
}

void TestAiClient::testAiClient_Instance()
{
    AiClient* instance1 = AiClient::instance();
    AiClient* instance2 = AiClient::instance();
    
    QVERIFY(instance1 != nullptr);
    QCOMPARE(instance1, instance2);  // 单例
}

void TestAiClient::testIsEnabled()
{
    AiClient client;
    QVERIFY(!client.isEnabled());
}

void TestAiClient::testSetEnabled()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(enabledChanged(bool)));
    
    client.setEnabled(true);
    QVERIFY(client.isEnabled());
    QCOMPARE(spy.count(), 1);
    
    client.setEnabled(false);
    QVERIFY(!client.isEnabled());
    QCOMPARE(spy.count(), 2);
}

void TestAiClient::testProvider()
{
    AiClient client;
    QCOMPARE(client.provider(), QString("openai"));
}

void TestAiClient::testSetProvider()
{
    AiClient client;
    QSignalSpy providerSpy(&client, SIGNAL(providerChanged(QString)));
    
    client.setProvider("azure");
    QCOMPARE(client.provider(), QString("azure"));
    QCOMPARE(providerSpy.count(), 1);
}

void TestAiClient::testApiKey()
{
    AiClient client;
    QVERIFY(client.apiKey().isEmpty());
}

void TestAiClient::testSetApiKey()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(apiKeyChanged(QString)));
    
    client.setApiKey("test-key-123");
    QCOMPARE(client.apiKey(), QString("test-key-123"));
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testModel()
{
    AiClient client;
    QCOMPARE(client.model(), QString("gpt-3.5-turbo"));
}

void TestAiClient::testSetModel()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(modelChanged(QString)));
    
    client.setModel("gpt-4");
    QCOMPARE(client.model(), QString("gpt-4"));
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testBaseUrl()
{
    AiClient client;
    QVERIFY(!client.baseUrl().isEmpty());
}

void TestAiClient::testSetBaseUrl()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(baseUrlChanged(QString)));
    
    client.setBaseUrl("https://custom.api.com/v1");
    QCOMPARE(client.baseUrl(), QString("https://custom.api.com/v1"));
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testIsProcessing()
{
    AiClient client;
    QVERIFY(!client.isProcessing());
}

void TestAiClient::testLastError()
{
    AiClient client;
    QVERIFY(client.lastError().isEmpty());
}

void TestAiClient::testTemperature()
{
    AiClient client;
    QCOMPARE(client.temperature(), 0.7);
}

void TestAiClient::testSetTemperature()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(temperatureChanged(double)));
    
    client.setTemperature(0.5);
    QCOMPARE(client.temperature(), 0.5);
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testMaxTokens()
{
    AiClient client;
    QCOMPARE(client.maxTokens(), 1000);
}

void TestAiClient::testSetMaxTokens()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(maxTokensChanged(int)));
    
    client.setMaxTokens(500);
    QCOMPARE(client.maxTokens(), 500);
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testSetProvider_OpenAI()
{
    AiClient client;
    client.setProvider("openai");
    
    QCOMPARE(client.provider(), QString("openai"));
    QCOMPARE(client.model(), QString("gpt-3.5-turbo"));
    QVERIFY(client.baseUrl().contains("api.openai.com"));
}

void TestAiClient::testSetProvider_Azure()
{
    AiClient client;
    client.setProvider("azure");
    
    QCOMPARE(client.provider(), QString("azure"));
    QVERIFY(client.model().contains("gpt"));
    QVERIFY(client.baseUrl().contains("azure.com"));
}

void TestAiClient::testSetProvider_Ollama()
{
    AiClient client;
    client.setProvider("ollama");
    
    QCOMPARE(client.provider(), QString("ollama"));
    QCOMPARE(client.model(), QString("llama2"));
    QVERIFY(client.baseUrl().contains("localhost:11434"));
}

void TestAiClient::testSetProvider_Custom()
{
    AiClient client;
    client.setProvider("custom");
    
    QCOMPARE(client.provider(), QString("custom"));
}

void TestAiClient::testAnalyzeIntent_NoApiKey()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(intentAnalyzed(QString, double, QString)));
    
    client.analyzeIntent("test query");
    
    // 没有 API 密钥时应该返回默认结果
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testExpandKeywords_NoApiKey()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(keywordsExpanded(QVariantList)));
    
    client.expandKeywords("test");
    
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testSuggestSearchTerms_NoApiKey()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(searchTermsSuggested(QVariantList)));
    
    client.suggestSearchTerms("context");
    
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testExplainConfig_NoApiKey()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(configExplained(QString)));
    
    client.explainConfig("key", "value");
    
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testValidateConfig_NoApiKey()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(configValidated(QVariantList)));
    
    QVariantMap config;
    client.validateConfig(config);
    
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testChat_NoApiKey()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(chatResponse(QString)));
    
    client.chat("hello", QVariantList());
    
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testCompletePrompt_NoApiKey()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(promptCompleted(QString)));
    
    client.completePrompt("complete this");
    
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testGetConversationHistory()
{
    AiClient client;
    QVariantList history = client.getConversationHistory();
    QCOMPARE(history.size(), 0);
}

void TestAiClient::testClearConversationHistory()
{
    AiClient client;
    client.clearConversationHistory();
    QCOMPARE(client.getConversationHistory().size(), 0);
}

void TestAiClient::testAbortRequest()
{
    AiClient client;
    
    // 没有活动请求时调用应该不报错
    client.abortRequest();
    
    QVERIFY(!client.isProcessing());
}

void TestAiClient::testLoadSettings()
{
    AiClient client;
    bool result = client.loadSettings();
    QVERIFY(result);
}

void TestAiClient::testSaveSettings()
{
    AiClient client;
    client.setEnabled(true);
    client.setApiKey("test-key");
    
    bool result = client.saveSettings();
    QVERIFY(result);
}

void TestAiClient::testEnabledChanged_Signal()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(enabledChanged(bool)));
    
    client.setEnabled(true);
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testProviderChanged_Signal()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(providerChanged(QString)));
    
    client.setProvider("azure");
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testApiKeyChanged_Signal()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(apiKeyChanged(QString)));
    
    client.setApiKey("new-key");
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testModelChanged_Signal()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(modelChanged(QString)));
    
    client.setModel("gpt-4");
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testBaseUrlChanged_Signal()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(baseUrlChanged(QString)));
    
    client.setBaseUrl("https://new.api.com");
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testProcessingChanged_Signal()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(processingChanged(bool)));
    
    // 没有实际请求时不会触发
    QVERIFY(spy.count() == 0);
}

void TestAiClient::testErrorOccurred_Signal()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(errorOccurred(QString)));
    
    // 没有实际请求时不会触发
    QVERIFY(spy.count() == 0);
}

void TestAiClient::testTemperatureChanged_Signal()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(temperatureChanged(double)));
    
    client.setTemperature(0.9);
    QCOMPARE(spy.count(), 1);
}

void TestAiClient::testMaxTokensChanged_Signal()
{
    AiClient client;
    QSignalSpy spy(&client, SIGNAL(maxTokensChanged(int)));
    
    client.setMaxTokens(2000);
    QCOMPARE(spy.count(), 1);
}

#endif // TEST_AICLIENT_H
