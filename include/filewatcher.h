#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QStringList>
#include <QHash>
#include <QDateTime>
#include <QTimer>
#include <QVariant>

class FileWatcher : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool watching READ isWatching NOTIFY watchingChanged)
    Q_PROPERTY(int watchedFileCount READ watchedFileCount NOTIFY watchedFilesChanged)
    Q_PROPERTY(QStringList watchedFiles READ watchedFiles NOTIFY watchedFilesChanged)

public:
    explicit FileWatcher(QObject* parent = nullptr);
    ~FileWatcher();

    static FileWatcher* instance();

    bool isWatching() const { return m_watching; }
    int watchedFileCount() const { return m_filePaths.size(); }
    QStringList watchedFiles() const { return m_filePaths; }

    Q_INVOKABLE bool addWatch(const QString& filePath);
    Q_INVOKABLE bool addWatchDirectory(const QString& dirPath, const QStringList& filters = QStringList());
    Q_INVOKABLE bool removeWatch(const QString& filePath);
    Q_INVOKABLE void clearWatches();
    Q_INVOKABLE void pauseWatching();
    Q_INVOKABLE void resumeWatching();

    Q_INVOKABLE QVariantList getChangedFiles();
    Q_INVOKABLE void clearChangedFiles();
    Q_INVOKABLE QVariantList getFileHistory(const QString& filePath, int limit = 10);

signals:
    void fileChanged(const QString& filePath, const QString& changeType);
    void directoryChanged(const QString& dirPath);
    void watchingChanged(bool watching);
    void watchedFilesChanged();
    void errorOccurred(const QString& error);

private slots:
    void onFileChanged(const QString& path);
    void onDirectoryChanged(const QString& path);
    void onDebounceTimer();

private:
    void recordChange(const QString& filePath, const QString& changeType);
    bool matchesFilter(const QString& fileName) const;

private:
    QFileSystemWatcher* m_watcher;
    bool m_watching;
    bool m_paused;
    QStringList m_filePaths;
    QStringList m_directoryPaths;
    QStringList m_fileFilters;
    
    QHash<QString, QDateTime> m_lastModifiedTimes;
    QHash<QString, QVariantList> m_changeHistory;
    QVariantList m_pendingChanges;
    
    QTimer* m_debounceTimer;
    QHash<QString, QString> m_pendingFileChanges;
    
    static FileWatcher* s_instance;
};

#endif // FILEWATCHER_H
