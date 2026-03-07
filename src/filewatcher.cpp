#include "filewatcher.h"
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QRegularExpression>

FileWatcher* FileWatcher::s_instance = nullptr;

FileWatcher::FileWatcher(QObject* parent)
    : QObject(parent)
    , m_watcher(new QFileSystemWatcher(this))
    , m_watching(false)
    , m_paused(false)
    , m_debounceTimer(new QTimer(this))
{
    m_fileFilters << "*.ini" << "*.json" << "*.xml";
    
    m_debounceTimer->setSingleShot(true);
    m_debounceTimer->setInterval(500);
    
    connect(m_watcher, &QFileSystemWatcher::fileChanged, this, &FileWatcher::onFileChanged);
    connect(m_watcher, &QFileSystemWatcher::directoryChanged, this, &FileWatcher::onDirectoryChanged);
    connect(m_debounceTimer, &QTimer::timeout, this, &FileWatcher::onDebounceTimer);
}

FileWatcher::~FileWatcher()
{
    clearWatches();
}

FileWatcher* FileWatcher::instance()
{
    if (!s_instance) {
        s_instance = new FileWatcher();
    }
    return s_instance;
}

bool FileWatcher::addWatch(const QString& filePath)
{
    QFileInfo fi(filePath);
    if (!fi.exists()) {
        emit errorOccurred(tr("文件不存在: ") + filePath);
        return false;
    }
    
    if (!matchesFilter(fi.fileName())) {
        return false;
    }
    
    if (m_filePaths.contains(filePath)) {
        return true;
    }
    
    if (!m_watcher->addPath(filePath)) {
        emit errorOccurred(tr("无法监控文件: ") + filePath);
        return false;
    }
    
    m_filePaths.append(filePath);
    m_lastModifiedTimes[filePath] = fi.lastModified();
    m_watching = true;
    
    emit watchedFilesChanged();
    emit watchingChanged(true);
    
    qDebug() << "[FileWatcher] Added watch:" << filePath;
    return true;
}

bool FileWatcher::addWatchDirectory(const QString& dirPath, const QStringList& filters)
{
    QDir dir(dirPath);
    if (!dir.exists()) {
        emit errorOccurred(tr("目录不存在: ") + dirPath);
        return false;
    }
    
    QStringList useFilters = filters.isEmpty() ? m_fileFilters : filters;
    
    if (!m_directoryPaths.contains(dirPath)) {
        m_watcher->addPath(dirPath);
        m_directoryPaths.append(dirPath);
    }
    
    int addedCount = 0;
    for (const QString& filter : useFilters) {
        QStringList files = dir.entryList(QStringList() << filter, QDir::Files);
        for (const QString& fileName : files) {
            QString fullPath = dir.absoluteFilePath(fileName);
            if (addWatch(fullPath)) {
                addedCount++;
            }
        }
    }
    
    qDebug() << "[FileWatcher] Added" << addedCount << "files from directory:" << dirPath;
    return addedCount > 0;
}

bool FileWatcher::removeWatch(const QString& filePath)
{
    if (!m_filePaths.contains(filePath)) {
        return false;
    }
    
    m_watcher->removePath(filePath);
    m_filePaths.removeAll(filePath);
    m_lastModifiedTimes.remove(filePath);
    
    emit watchedFilesChanged();
    
    if (m_filePaths.isEmpty()) {
        m_watching = false;
        emit watchingChanged(false);
    }
    
    qDebug() << "[FileWatcher] Removed watch:" << filePath;
    return true;
}

void FileWatcher::clearWatches()
{
    if (!m_filePaths.isEmpty()) {
        m_watcher->removePaths(m_filePaths);
        m_filePaths.clear();
    }
    
    if (!m_directoryPaths.isEmpty()) {
        m_watcher->removePaths(m_directoryPaths);
        m_directoryPaths.clear();
    }
    
    m_lastModifiedTimes.clear();
    m_changeHistory.clear();
    m_pendingChanges.clear();
    m_pendingFileChanges.clear();
    
    m_watching = false;
    emit watchedFilesChanged();
    emit watchingChanged(false);
}

void FileWatcher::pauseWatching()
{
    m_paused = true;
    qDebug() << "[FileWatcher] Paused";
}

void FileWatcher::resumeWatching()
{
    m_paused = false;
    qDebug() << "[FileWatcher] Resumed";
}

QVariantList FileWatcher::getChangedFiles()
{
    return m_pendingChanges;
}

void FileWatcher::clearChangedFiles()
{
    m_pendingChanges.clear();
}

QVariantList FileWatcher::getFileHistory(const QString& filePath, int limit)
{
    if (!m_changeHistory.contains(filePath)) {
        return QVariantList();
    }
    
    QVariantList history = m_changeHistory[filePath];
    if (limit > 0 && history.size() > limit) {
        return history.mid(0, limit);
    }
    return history;
}

void FileWatcher::onFileChanged(const QString& path)
{
    if (m_paused) {
        return;
    }
    
    QFileInfo fi(path);
    if (!fi.exists()) {
        recordChange(path, "deleted");
        removeWatch(path);
        return;
    }
    
    QDateTime lastModified = m_lastModifiedTimes.value(path);
    QDateTime currentModified = fi.lastModified();
    
    if (lastModified.isValid() && currentModified > lastModified) {
        m_lastModifiedTimes[path] = currentModified;
        
        m_pendingFileChanges[path] = "modified";
        m_debounceTimer->start();
    }
}

void FileWatcher::onDirectoryChanged(const QString& path)
{
    if (m_paused) {
        return;
    }
    
    emit directoryChanged(path);
    
    QDir dir(path);
    for (const QString& filter : m_fileFilters) {
        QStringList files = dir.entryList(QStringList() << filter, QDir::Files);
        for (const QString& fileName : files) {
            QString fullPath = dir.absoluteFilePath(fileName);
            if (!m_filePaths.contains(fullPath)) {
                addWatch(fullPath);
                recordChange(fullPath, "created");
            }
        }
    }
}

void FileWatcher::onDebounceTimer()
{
    for (auto it = m_pendingFileChanges.begin(); it != m_pendingFileChanges.end(); ++it) {
        recordChange(it.key(), it.value());
        emit fileChanged(it.key(), it.value());
    }
    m_pendingFileChanges.clear();
}

void FileWatcher::recordChange(const QString& filePath, const QString& changeType)
{
    QVariantMap change;
    change["filePath"] = filePath;
    change["changeType"] = changeType;
    change["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    
    m_pendingChanges.append(change);
    
    if (!m_changeHistory.contains(filePath)) {
        m_changeHistory[filePath] = QVariantList();
    }
    m_changeHistory[filePath].prepend(change);
    
    while (m_changeHistory[filePath].size() > 100) {
        m_changeHistory[filePath].removeLast();
    }
    
    qDebug() << "[FileWatcher] Recorded change:" << filePath << changeType;
}

bool FileWatcher::matchesFilter(const QString& fileName) const
{
    for (const QString& filter : m_fileFilters) {
        QRegularExpression re(QRegularExpression::wildcardToRegularExpression(filter));
        if (re.match(fileName).hasMatch()) {
            return true;
        }
    }
    return false;
}
