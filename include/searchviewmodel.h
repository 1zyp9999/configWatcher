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

class SearchViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY searchTextChanged)
    Q_PROPERTY(QList<QObject*> searchResults READ searchResults NOTIFY searchResultsChanged)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY isLoadingChanged)
    Q_PROPERTY(int loadProgress READ loadProgress NOTIFY loadProgressChanged)
    Q_PROPERTY(int keyCount READ keyCount NOTIFY keyCountChanged)

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

private:
    QString m_searchText;
    QList<QObject*> m_searchResults;
    bool m_isLoading = false;
    int m_loadProgress = 0;

    ConfigParser* m_parser;
    DatabaseManager* m_dbManager = nullptr;
    // suggestion cache
    QStringList m_allKeys;
    bool m_keyIndexBuilt = false;
};

#endif // SEARCHVIEWMODEL_H