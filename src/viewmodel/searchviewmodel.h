#ifndef SEARCHVIEWMODEL_H
#define SEARCHVIEWMODEL_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QVariantList>
#include <QMutex>
#include <QSharedPointer>
#include "configparser.h"
#include "configentry.h"
#include "databasemanager.h"

class SearchViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY searchTextChanged)
    Q_PROPERTY(QVariantList searchResults READ searchResults NOTIFY searchResultsChanged)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY isLoadingChanged)
    Q_PROPERTY(int loadProgress READ loadProgress NOTIFY loadProgressChanged)
    Q_PROPERTY(int searchMode READ searchMode WRITE setSearchMode NOTIFY searchModeChanged)
    Q_PROPERTY(int currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)
    Q_PROPERTY(int totalPages READ totalPages NOTIFY totalPagesChanged)
    Q_PROPERTY(int pageSize READ pageSize CONSTANT)

public:
    explicit SearchViewModel(QObject *parent = nullptr);
    ~SearchViewModel() override;

    QString searchText() const { return m_searchText; }
    void setSearchText(const QString& text);

    QVariantList searchResults() const;
    void setSearchResults(const QVariantList& results);

    bool isLoading() const { return m_isLoading; }
    void setIsLoading(bool loading);

    int loadProgress() const { return m_loadProgress; }
    void setLoadProgress(int progress);

    int searchMode() const { return m_searchMode; }
    void setSearchMode(int mode);

    int currentPage() const { return m_currentPage; }
    void setCurrentPage(int page);

    int totalPages() const { return m_totalPages; }
    void setTotalPages(int pages);

    int pageSize() const { return m_pageSize; }

    Q_INVOKABLE QString pickConfigFile();
    Q_INVOKABLE QVariantList readConfigFile(const QString& filePath);
    Q_INVOKABLE bool writeConfigFile(const QString& filePath, const QVariantList& entries);

    Q_INVOKABLE QString selectDirectory();
    Q_INVOKABLE void loadConfigFiles(const QStringList& filePaths);
    Q_INVOKABLE void openConfigFile(const QString& filePath);
    Q_INVOKABLE bool initializeDatabase(const QString& dbPath);
    Q_INVOKABLE void buildKeyIndex();
    Q_INVOKABLE QStringList suggestKeys(const QString& prefix, int maxResults = 10);
    Q_INVOKABLE QVariantList suggestClusters(const QString& prefix, int maxClusters = 8, int maxPerCluster = 8);
    Q_INVOKABLE void requestSuggestClusters(const QString &prefix, int maxClusters = 8, int maxPerCluster = 6);
    
    // 分页控制
    Q_INVOKABLE void nextPage();
    Q_INVOKABLE void previousPage();
    Q_INVOKABLE void goToPage(int page);
    
    // 更新分页结果（内部方法）
    void updatePaginatedResults();

public slots:
    void updateSearchResults();
    void deliverSuggestClusters(const QVariantList &clusters);
    void openFileRequested(const QString &filePath);
    void onParserError(const QString& message);

signals:
    void searchTextChanged();
    void searchResultsChanged();
    void isLoadingChanged();
    void loadProgressChanged();
    void suggestClustersReady(QVariantList clusters);
    void searchModeChanged();
    void currentPageChanged();
    void totalPagesChanged();

private:
    QString m_searchText;
    QVariantList m_searchResults;
    QVariantList m_allSearchResults;  // 缓存全部结果用于分页
    bool m_isLoading = false;
    int m_loadProgress = 0;
    int m_searchMode = 0;  // 0: 模糊搜索，1: 精准搜索
    int m_currentPage = 0;
    int m_totalPages = 0;
    const int m_pageSize = 100;  // 每页显示 100 条

    ConfigParser* m_parser;
    DatabaseManager* m_dbManager = nullptr;
    mutable QMutex m_resultsMutex;
    
    // suggestion cache
    QStringList m_allKeys;
    bool m_keyIndexBuilt = false;
    
    // 辅助函数：将 ConfigEntry 转换为 QVariantMap
    static QVariantMap entryToMap(const QSharedPointer<ConfigEntry>& entry);
};

#endif // SEARCHVIEWMODEL_H
