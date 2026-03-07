#include "aiclient.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QSettings>
#include <QDebug>

AiClient* AiClient::s_instance = nullptr;

AiClient::AiClient(QObject* parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
    , m_currentReply(nullptr)
    , m_timeoutTimer(new QTimer(this))
    , m_enabled(false)
    , m_isProcessing(false)
    , m_provider("openai")
    , m_model("gpt-3.5-turbo")
    , m_baseUrl("https://api.openai.com/v1")
    , m_maxTokens(1000)
    , m_temperature(0.7)
    , m_timeout(30000)
{
    m_timeoutTimer->setSingleShot(true);
    connect(m_timeoutTimer, &QTimer::timeout, this, &AiClient::onTimeout);
    
    loadSettings();
}

AiClient::~AiClient()
{
    saveSettings();
}

AiClient* AiClient::instance()
{
    if (!s_instance) {
        s_instance = new AiClient();
    }
    return s_instance;
}

void AiClient::setEnabled(bool enabled)
{
    if (m_enabled != enabled) {
        m_enabled = enabled;
        emit enabledChanged(enabled);
    }
}

void AiClient::setProvider(const QString& provider)
{
    if (m_provider != provider) {
        m_provider = provider.toLower();
        
        if (m_provider == "openai") {
            m_baseUrl = "https://api.openai.com/v1";
            m_model = "gpt-3.5-turbo";
        } else if (m_provider == "azure") {
            m_baseUrl = "https://YOUR_RESOURCE.openai.azure.com";
            m_model = "gpt-35-turbo";
        } else if (m_provider == "ollama") {
            m_baseUrl = "http://localhost:11434/api";
            m_model = "llama2";
        }
        
        emit providerChanged(m_provider);
        emit baseUrlChanged(m_baseUrl);
        emit modelChanged(m_model);
    }
}

void AiClient::setApiKey(const QString& key)
{
    if (m_apiKey != key) {
        m_apiKey = key;
        emit apiKeyChanged(key);
    }
}

void AiClient::setModel(const QString& model)
{
    if (m_model != model) {
        m_model = model;
        emit modelChanged(model);
    }
}

void AiClient::setBaseUrl(const QString& url)
{
    if (m_baseUrl != url) {
        m_baseUrl = url;
        emit baseUrlChanged(url);
    }
}

void AiClient::setTemperature(double temp)
{
    if (!qFuzzyCompare(m_temperature, temp)) {
        m_temperature = temp;
        emit temperatureChanged(temp);
    }
}

void AiClient::setMaxTokens(int tokens)
{
    if (m_maxTokens != tokens) {
        m_maxTokens = tokens;
        emit maxTokensChanged(tokens);
    }
}

void AiClient::analyzeIntent(const QString& query)
{
    if (!m_enabled || m_apiKey.isEmpty()) {
        emit intentAnalyzed("search_key", 0.5, tr("AI 未配置或未启用"));
        return;
    }
    
    m_currentTask = "intent";
    QString systemPrompt = getSystemPrompt("intent");
    QString userMessage = QString("分析以下配置搜索查询的意图：\n%1\n\n请返回 JSON 格式：{\"intent\": \"search_key|search_value|search_chinese|navigate\", \"confidence\": 0.0-1.0, \"explanation\": \"解释\"}").arg(query);
    
    QJsonObject body = buildRequestBody(systemPrompt, userMessage);
    sendRequest("/chat/completions", body);
}

void AiClient::expandKeywords(const QString& query)
{
    if (!m_enabled || m_apiKey.isEmpty()) {
        emit keywordsExpanded(QVariantList());
        return;
    }
    
    m_currentTask = "keywords";
    QString systemPrompt = getSystemPrompt("keywords");
    QString userMessage = QString("扩展以下配置搜索关键词，提供相关的同义词和相关术语：\n%1\n\n请返回 JSON 数组格式：[{\"term\": \"关键词\", \"type\": \"synonym|related|translation\"}]").arg(query);
    
    QJsonObject body = buildRequestBody(systemPrompt, userMessage);
    sendRequest("/chat/completions", body);
}

void AiClient::suggestSearchTerms(const QString& context)
{
    if (!m_enabled || m_apiKey.isEmpty()) {
        emit searchTermsSuggested(QVariantList());
        return;
    }
    
    m_currentTask = "suggest";
    QString systemPrompt = getSystemPrompt("suggest");
    QString userMessage = QString("基于以下上下文，建议可能的配置搜索词：\n%1\n\n请返回 JSON 数组格式：[\"搜索词1\", \"搜索词2\", ...]").arg(context);
    
    QJsonObject body = buildRequestBody(systemPrompt, userMessage);
    sendRequest("/chat/completions", body);
}

void AiClient::explainConfig(const QString& key, const QString& value)
{
    if (!m_enabled || m_apiKey.isEmpty()) {
        emit configExplained(tr("AI 未配置或未启用"));
        return;
    }
    
    m_currentTask = "explain";
    QString systemPrompt = getSystemPrompt("explain");
    QString userMessage = QString("解释以下配置参数的含义和作用：\n键名：%1\n值：%2\n\n请用简洁的中文解释，包括参数用途、取值范围、注意事项等。").arg(key, value);
    
    QJsonObject body = buildRequestBody(systemPrompt, userMessage);
    sendRequest("/chat/completions", body);
}

void AiClient::validateConfig(const QVariantMap& config)
{
    if (!m_enabled || m_apiKey.isEmpty()) {
        emit configValidated(QVariantList());
        return;
    }
    
    m_currentTask = "validate";
    QString systemPrompt = getSystemPrompt("validate");
    QString configJson = QString::fromUtf8(QJsonDocument::fromVariant(config).toJson(QJsonDocument::Indented));
    QString userMessage = QString("验证以下配置是否合理，检查是否有错误或不推荐的设置：\n%1\n\n请返回 JSON 数组格式：[{\"key\": \"键名\", \"issue\": \"问题描述\", \"severity\": \"error|warning|info\", \"suggestion\": \"建议值\"}]")
        .arg(configJson);
    
    QJsonObject body = buildRequestBody(systemPrompt, userMessage);
    sendRequest("/chat/completions", body);
}

void AiClient::chat(const QString& message, const QVariantList& history)
{
    if (!m_enabled || m_apiKey.isEmpty()) {
        emit chatResponse(tr("AI 未配置或未启用"));
        return;
    }
    
    m_currentTask = "chat";
    QString systemPrompt = getSystemPrompt("chat");
    
    QJsonArray messages;
    messages.append(QJsonObject{{"role", "system"}, {"content", systemPrompt}});
    
    for (const QVariant& item : history) {
        QVariantMap msg = item.toMap();
        messages.append(QJsonObject{
            {"role", msg["role"].toString()},
            {"content", msg["content"].toString()}
        });
    }
    
    messages.append(QJsonObject{{"role", "user"}, {"content", message}});
    
    QJsonObject body;
    body["model"] = m_model;
    body["messages"] = messages;
    body["max_tokens"] = m_maxTokens;
    body["temperature"] = m_temperature;
    
    sendRequest("/chat/completions", body);
}

void AiClient::completePrompt(const QString& prompt)
{
    if (!m_enabled || m_apiKey.isEmpty()) {
        emit promptCompleted(tr("AI 未配置或未启用"));
        return;
    }
    
    m_currentTask = "complete";
    QString systemPrompt = getSystemPrompt("complete");
    
    QJsonObject body = buildRequestBody(systemPrompt, prompt);
    sendRequest("/chat/completions", body);
}

QVariantList AiClient::getConversationHistory()
{
    return m_conversationHistory;
}

void AiClient::clearConversationHistory()
{
    m_conversationHistory.clear();
}

void AiClient::abortRequest()
{
    if (m_currentReply) {
        m_currentReply->abort();
        m_currentReply->deleteLater();
        m_currentReply = nullptr;
    }
    
    m_timeoutTimer->stop();
    m_isProcessing = false;
    emit processingChanged(false);
}

bool AiClient::loadSettings()
{
    QString path = getSettingsPath();
    QSettings settings(path, QSettings::IniFormat);
    
    m_enabled = settings.value("ai/enabled", false).toBool();
    m_provider = settings.value("ai/provider", "openai").toString();
    m_apiKey = settings.value("ai/apiKey").toString();
    m_model = settings.value("ai/model", "gpt-3.5-turbo").toString();
    m_baseUrl = settings.value("ai/baseUrl", "https://api.openai.com/v1").toString();
    m_maxTokens = settings.value("ai/maxTokens", 1000).toInt();
    m_temperature = settings.value("ai/temperature", 0.7).toDouble();
    
    return true;
}

bool AiClient::saveSettings()
{
    QString path = getSettingsPath();
    QSettings settings(path, QSettings::IniFormat);
    
    settings.setValue("ai/enabled", m_enabled);
    settings.setValue("ai/provider", m_provider);
    settings.setValue("ai/apiKey", m_apiKey);
    settings.setValue("ai/model", m_model);
    settings.setValue("ai/baseUrl", m_baseUrl);
    settings.setValue("ai/maxTokens", m_maxTokens);
    settings.setValue("ai/temperature", m_temperature);
    
    settings.sync();
    return true;
}

void AiClient::onReplyFinished()
{
    m_timeoutTimer->stop();
    m_isProcessing = false;
    emit processingChanged(false);
    
    if (!m_currentReply) return;
    
    QByteArray data = m_currentReply->readAll();
    QNetworkReply::NetworkError error = m_currentReply->error();
    m_currentReply->deleteLater();
    m_currentReply = nullptr;
    
    if (error != QNetworkReply::NoError) {
        m_lastError = m_currentReply ? m_currentReply->errorString() : "Network error";
        emit errorOccurred(m_lastError);
        return;
    }
    
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    
    if (parseError.error != QJsonParseError::NoError) {
        m_lastError = "JSON parse error: " + parseError.errorString();
        emit errorOccurred(m_lastError);
        return;
    }
    
    QJsonObject response = doc.object();
    
    if (m_provider == "ollama") {
        QString content = response["response"].toString();
        
        if (m_currentTask == "intent") {
            parseIntentResponse(QJsonObject{{"content", content}});
        } else if (m_currentTask == "keywords") {
            parseKeywordsResponse(QJsonObject{{"content", content}});
        } else if (m_currentTask == "chat") {
            emit chatResponse(content);
        } else if (m_currentTask == "explain") {
            emit configExplained(content);
        } else if (m_currentTask == "validate") {
            parseValidationResponse(QJsonObject{{"content", content}});
        } else {
            emit promptCompleted(content);
        }
    } else {
        QJsonObject choice = response["choices"].toArray()[0].toObject();
        QJsonObject message = choice["message"].toObject();
        QString content = message["content"].toString();
        
        if (m_currentTask == "intent") {
            parseIntentResponse(QJsonObject{{"content", content}});
        } else if (m_currentTask == "keywords") {
            parseKeywordsResponse(QJsonObject{{"content", content}});
        } else if (m_currentTask == "chat") {
            QVariantMap userMsg;
            userMsg["role"] = "user";
            userMsg["content"] = m_conversationHistory.isEmpty() ? "" : 
                m_conversationHistory.last().toMap()["content"].toString();
            
            QVariantMap assistantMsg;
            assistantMsg["role"] = "assistant";
            assistantMsg["content"] = content;
            
            m_conversationHistory.append(userMsg);
            m_conversationHistory.append(assistantMsg);
            
            emit chatResponse(content);
        } else if (m_currentTask == "explain") {
            emit configExplained(content);
        } else if (m_currentTask == "validate") {
            parseValidationResponse(QJsonObject{{"content", content}});
        } else {
            emit promptCompleted(content);
        }
    }
}

void AiClient::onReplyError(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error);
    m_lastError = m_currentReply ? m_currentReply->errorString() : "Unknown error";
    emit errorOccurred(m_lastError);
}

void AiClient::onTimeout()
{
    abortRequest();
    m_lastError = tr("请求超时");
    emit errorOccurred(m_lastError);
}

void AiClient::sendRequest(const QString& endpoint, const QJsonObject& payload)
{
    if (m_currentReply) {
        m_currentReply->abort();
        m_currentReply->deleteLater();
    }
    
    QString url = m_baseUrl + endpoint;
    QUrl requestUrl(url);
    QNetworkRequest request(requestUrl);
    
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    if (m_provider == "openai" || m_provider == "custom") {
        request.setRawHeader("Authorization", QString("Bearer %1").arg(m_apiKey).toUtf8());
    } else if (m_provider == "azure") {
        request.setRawHeader("api-key", m_apiKey.toUtf8());
    }
    
    m_isProcessing = true;
    emit processingChanged(true);
    
    m_currentReply = m_networkManager->post(request, QJsonDocument(payload).toJson());
    
    connect(m_currentReply, &QNetworkReply::finished, this, &AiClient::onReplyFinished);
    connect(m_currentReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::errorOccurred),
            this, &AiClient::onReplyError);
    
    m_timeoutTimer->start(m_timeout);
}

QJsonObject AiClient::buildRequestBody(const QString& systemPrompt, const QString& userMessage)
{
    QJsonObject body;
    body["model"] = m_model;
    
    QJsonArray messages;
    messages.append(QJsonObject{{"role", "system"}, {"content", systemPrompt}});
    messages.append(QJsonObject{{"role", "user"}, {"content", userMessage}});
    
    body["messages"] = messages;
    body["max_tokens"] = m_maxTokens;
    body["temperature"] = m_temperature;
    
    return body;
}

void AiClient::parseIntentResponse(const QJsonObject& response)
{
    QString content = response["content"].toString();
    
    QRegularExpression jsonRe(R"(\{[^{}]*"intent"[^{}]*\})");
    QRegularExpressionMatch match = jsonRe.match(content);
    
    if (match.hasMatch()) {
        QJsonDocument doc = QJsonDocument::fromJson(match.captured(0).toUtf8());
        QJsonObject obj = doc.object();
        
        QString intent = obj["intent"].toString("search_key");
        double confidence = obj["confidence"].toDouble(0.5);
        QString explanation = obj["explanation"].toString();
        
        emit intentAnalyzed(intent, confidence, explanation);
    } else {
        emit intentAnalyzed("search_key", 0.5, content);
    }
}

void AiClient::parseKeywordsResponse(const QJsonObject& response)
{
    QString content = response["content"].toString();
    
    QRegularExpression jsonRe(R"(\[[^\]]*\])");
    QRegularExpressionMatch match = jsonRe.match(content);
    
    if (match.hasMatch()) {
        QJsonDocument doc = QJsonDocument::fromJson(match.captured(0).toUtf8());
        QVariantList keywords = doc.array().toVariantList();
        emit keywordsExpanded(keywords);
    } else {
        emit keywordsExpanded(QVariantList());
    }
}

void AiClient::parseValidationResponse(const QJsonObject& response)
{
    QString content = response["content"].toString();
    
    QRegularExpression jsonRe(R"(\[[^\]]*\])");
    QRegularExpressionMatch match = jsonRe.match(content);
    
    if (match.hasMatch()) {
        QJsonDocument doc = QJsonDocument::fromJson(match.captured(0).toUtf8());
        QVariantList issues = doc.array().toVariantList();
        emit configValidated(issues);
    } else {
        emit configValidated(QVariantList());
    }
}

QString AiClient::getSystemPrompt(const QString& task)
{
    static QHash<QString, QString> prompts = {
        {"intent", 
         "你是一个 AOI（自动光学检测）设备配置管理助手。分析用户的搜索意图，判断他们想要："
         "- search_key: 搜索配置项名称"
         "- search_value: 搜索配置值"
         "- search_chinese: 用中文描述搜索"
         "- navigate: 导航到某个配置区域\n"
         "返回 JSON 格式结果。"},
        
        {"keywords",
         "你是一个 AOI 设备配置专家。根据用户的搜索词，提供相关的同义词、翻译和相关术语。"
         "领域包括：相机参数、光源配置、标定参数、运动控制、图像处理等。返回 JSON 数组。"},
        
        {"suggest",
         "你是 AOI 设备配置助手。根据上下文建议用户可能想要搜索的配置项。返回 JSON 数组。"},
        
        {"explain",
         "你是 AOI 设备配置专家。用简洁的中文解释配置参数的含义、作用、取值范围和注意事项。"},
        
        {"validate",
         "你是 AOI 设备配置验证专家。检查配置是否合理，识别错误或不推荐的设置。"
         "返回 JSON 数组，每项包含 key, issue, severity, suggestion。"},
        
        {"chat",
         "你是 ConfigWatcher 配置管理工具的 AI 助手。帮助用户管理 AOI 设备的配置文件，"
         "回答关于配置参数的问题，提供专业建议。用中文回答。"},
        
        {"complete",
         "你是配置管理助手。根据用户的提示完成文本。"}
    };
    
    return prompts.value(task, prompts["chat"]);
}

QString AiClient::getSettingsPath()
{
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataDir);
    return dataDir + "/ai_settings.ini";
}
