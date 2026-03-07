#ifndef AICLIENT_H
#define AICLIENT_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>

class AiClient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString provider READ provider WRITE setProvider NOTIFY providerChanged)
    Q_PROPERTY(QString apiKey READ apiKey WRITE setApiKey NOTIFY apiKeyChanged)
    Q_PROPERTY(QString model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QString baseUrl READ baseUrl WRITE setBaseUrl NOTIFY baseUrlChanged)
    Q_PROPERTY(bool isProcessing READ isProcessing NOTIFY processingChanged)
    Q_PROPERTY(QString lastError READ lastError NOTIFY errorOccurred)

public:
    enum Provider {
        OpenAI,
        Azure,
        Ollama,
        Custom
    };
    Q_ENUM(Provider)

    explicit AiClient(QObject* parent = nullptr);
    ~AiClient();

    static AiClient* instance();

    bool isEnabled() const { return m_enabled; }
    void setEnabled(bool enabled);

    QString provider() const { return m_provider; }
    void setProvider(const QString& provider);

    QString apiKey() const { return m_apiKey; }
    void setApiKey(const QString& key);

    QString model() const { return m_model; }
    void setModel(const QString& model);

    QString baseUrl() const { return m_baseUrl; }
    void setBaseUrl(const QString& url);

    bool isProcessing() const { return m_isProcessing; }
    QString lastError() const { return m_lastError; }

    Q_INVOKABLE void analyzeIntent(const QString& query);
    Q_INVOKABLE void expandKeywords(const QString& query);
    Q_INVOKABLE void suggestSearchTerms(const QString& context);
    Q_INVOKABLE void explainConfig(const QString& key, const QString& value);
    Q_INVOKABLE void validateConfig(const QVariantMap& config);
    Q_INVOKABLE void chat(const QString& message, const QVariantList& history = QVariantList());
    Q_INVOKABLE void completePrompt(const QString& prompt);
    
    Q_INVOKABLE QVariantList getConversationHistory();
    Q_INVOKABLE void clearConversationHistory();
    Q_INVOKABLE void abortRequest();
    
    Q_INVOKABLE bool loadSettings();
    Q_INVOKABLE bool saveSettings();

signals:
    void enabledChanged(bool enabled);
    void providerChanged(const QString& provider);
    void apiKeyChanged(const QString& key);
    void modelChanged(const QString& model);
    void baseUrlChanged(const QString& url);
    void processingChanged(bool processing);
    void errorOccurred(const QString& error);
    
    void intentAnalyzed(const QString& intent, double confidence, const QString& explanation);
    void keywordsExpanded(const QVariantList& keywords);
    void searchTermsSuggested(const QVariantList& terms);
    void configExplained(const QString& explanation);
    void configValidated(const QVariantList& issues);
    void chatResponse(const QString& response);
    void promptCompleted(const QString& result);

private slots:
    void onReplyFinished();
    void onReplyError(QNetworkReply::NetworkError error);
    void onTimeout();

private:
    void sendRequest(const QString& endpoint, const QJsonObject& payload);
    QJsonObject buildRequestBody(const QString& systemPrompt, const QString& userMessage);
    void parseIntentResponse(const QJsonObject& response);
    void parseKeywordsResponse(const QJsonObject& response);
    void parseValidationResponse(const QJsonObject& response);
    QString getSystemPrompt(const QString& task);
    QString getSettingsPath();

private:
    QNetworkAccessManager* m_networkManager;
    QNetworkReply* m_currentReply;
    QTimer* m_timeoutTimer;
    
    bool m_enabled;
    bool m_isProcessing;
    QString m_provider;
    QString m_apiKey;
    QString m_model;
    QString m_baseUrl;
    QString m_lastError;
    QString m_currentTask;
    QVariantList m_conversationHistory;
    
    int m_maxTokens;
    double m_temperature;
    int m_timeout;
    
    static AiClient* s_instance;
};

#endif // AICLIENT_H
