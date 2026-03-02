#ifndef SEARCHVIEWMODEL_H
#define SEARCHVIEWMODEL_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QWidget>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QVariantList>
#include "configparser.h"
#include "configentry.h"
#include "databasemanager.h"
#include "aiservice.h"

class SearchViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY searchTextChanged)
    Q_PROPERTY(QList<QObject*> searchResults READ searchResults NOTIFY searchResultsChanged)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY isLoadingChanged)
    Q_PROPERTY(int loadProgress READ loadProgress NOTIFY loadProgressChanged)
    Q_PROPERTY(int keyCount READ keyCount NOTIFY keyCountChanged)
    
    // AI 相关属性
    Q_PROPERTY(bool aiEnabled READ aiEnabled WRITE setAiEnabled NOTIFY aiEnabledChanged)
    Q_PROPERTY(QString aiIntent READ aiIntent NOTIFY aiIntentChanged)
    Q_PROPERTY(double aiConfidence READ aiConfidence NOTIFY aiConfidenceChanged)
    Q_PROPERTY(QVariantList aiSuggestions READ aiSuggestions NOTIFY aiSuggestionsChanged)
    Q_PROPERTY(QString aiExplanation READ aiExplanation NOTIFY aiExplanationChanged)
    Q_PROPERTY(bool learningEnabled READ isLearningEnabled WRITE setLearningEnabled NOTIFY learningEnabledChanged)
    Q_PROPERTY(QString formatFilter READ formatFilter WRITE setFormatFilter NOTIFY formatFilterChanged)

public:
    explicit SearchViewModel(QObject *parent = nullptr);

    QString searchText() const { return m_searchText; }
    void setSearchText(const QString& text);

    QList<QObject*> searchResults() const { return m_searchResults; }
    void setSearchResults(const QList<QObject*>& results);

    bool isLoading() const { return m_isLoading; }
    void setIsLoading(bool loading);

    int loadProgress() const { return m_loadProgress; }
    void setLoadProgress(int progress);

    int keyCount() const { return m_allKeys.size(); }
    
    // AI 相关方法
    bool aiEnabled() const { return m_aiEnabled; }
    void setAiEnabled(bool enabled);
    
    QString aiIntent() const { return m_aiIntent; }
    double aiConfidence() const { return m_aiConfidence; }
    QVariantList aiSuggestions() const { return m_aiSuggestions; }
    QString aiExplanation() const { return m_aiExplanation; }

    QString formatFilter() const { return m_formatFilter; }
    void setFormatFilter(const QString& filter);

    Q_INVOKABLE QString selectDirectory();
    Q_INVOKABLE void loadConfigFiles(const QStringList& filePaths);
    Q_INVOKABLE void openConfigFile(const QString& filePath);
    Q_INVOKABLE QString pickConfigFile();
    Q_INVOKABLE QVariantList readConfigFile(const QString& filePath);
    Q_INVOKABLE bool writeConfigFile(const QString& filePath, const QVariantList& entries);
    Q_INVOKABLE bool initializeDatabase(const QString& dbPath);
    Q_INVOKABLE void buildKeyIndex();
    Q_INVOKABLE QStringList suggestKeys(const QString& prefix, int maxResults = 10);
    Q_INVOKABLE QVariantList suggestClusters(const QString &prefix, int maxClusters = 8, int maxPerCluster = 6);
    Q_INVOKABLE void requestSuggestClusters(const QString &prefix, int maxClusters = 8, int maxPerCluster = 6);
    
    // AI 增强搜索方法
    Q_INVOKABLE void analyzeSearchQuery(const QString& query);
    Q_INVOKABLE void applyAiSuggestion(const QString& suggestion);
    Q_INVOKABLE void expandSearchWithAi(const QString& query);
    Q_INVOKABLE QString getAiExplanation(const QString& query);
    
    // 用户词典方法
    Q_INVOKABLE void addUserTerm(const QString& key, const QString& chinese, const QVariantList& synonyms);
    Q_INVOKABLE void removeUserTerm(const QString& key);
    Q_INVOKABLE QVariantList getUserTerms() const;
    
    // 搜索历史方法
    Q_INVOKABLE void recordSearch(const QString& query, int resultCount, bool selected);
    Q_INVOKABLE QVariantList getSearchHistory(int limit);
    Q_INVOKABLE void clearSearchHistory();
    Q_INVOKABLE QVariantList getHotSearches(int limit);
    
    // 设置
    Q_INVOKABLE void setLearningEnabled(bool enabled);
    Q_INVOKABLE bool isLearningEnabled() const;

public slots:
    void updateSearchResults();
    void deliverSuggestClusters(const QVariantList &clusters);
    void openFileRequested(const QString &filePath);

signals:
    void searchTextChanged();
    void searchResultsChanged();
    void isLoadingChanged();
    void loadProgressChanged();
    void suggestClustersReady(QVariantList clusters);
    void keyCountChanged();
    void aiEnabledChanged(bool enabled);
    void aiIntentChanged();
    void aiConfidenceChanged();
    void aiSuggestionsChanged();
    void aiExplanationChanged();
    void learningEnabledChanged(bool enabled);
    void formatFilterChanged();

private:
    QString m_searchText;
    QList<QObject*> m_searchResults;
    bool m_isLoading = false;
    int m_loadProgress = 0;

    ConfigParser* m_parser;
    DatabaseManager* m_dbManager = nullptr;
    AiService* m_aiService = nullptr;
    
    // suggestion cache
    QStringList m_allKeys;
    bool m_keyIndexBuilt = false;
    
    // AI 状态
    bool m_aiEnabled = true;
    QString m_aiIntent;
    double m_aiConfidence = 0.0;
    QVariantList m_aiSuggestions;
    QString m_aiExplanation;
    bool m_learningEnabled = true;
    QString m_formatFilter;  // 文件类型过滤: "ini", "json", "xml", "" (all)
};

#endif // SEARCHVIEWMODEL_H