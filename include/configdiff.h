#ifndef CONFIGDIFF_H
#define CONFIGDIFF_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>

struct DiffEntry {
    QString key;
    QString oldValue;
    QString newValue;
    QString section;
    QString changeType; // "added", "removed", "modified", "unchanged"
};

class ConfigDiff : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList diffResults READ diffResults NOTIFY diffResultsChanged)
    Q_PROPERTY(int addedCount READ addedCount NOTIFY diffResultsChanged)
    Q_PROPERTY(int removedCount READ removedCount NOTIFY diffResultsChanged)
    Q_PROPERTY(int modifiedCount READ modifiedCount NOTIFY diffResultsChanged)
    Q_PROPERTY(int unchangedCount READ unchangedCount NOTIFY diffResultsChanged)

public:
    explicit ConfigDiff(QObject* parent = nullptr);
    ~ConfigDiff();

    Q_INVOKABLE QVariantList compareFiles(const QString& file1Path, const QString& file2Path);
    Q_INVOKABLE QVariantList compareWithDatabase(const QString& filePath);
    Q_INVOKABLE QVariantList compareConfigs(const QVariantList& config1, const QVariantList& config2);
    Q_INVOKABLE QVariantList compareSnapshots(const QString& filePath, const QString& snapshot1, const QString& snapshot2);
    
    Q_INVOKABLE bool createSnapshot(const QString& filePath);
    Q_INVOKABLE QVariantList listSnapshots(const QString& filePath);
    Q_INVOKABLE bool deleteSnapshot(const QString& filePath, const QString& snapshotTime);
    Q_INVOKABLE bool restoreSnapshot(const QString& filePath, const QString& snapshotTime);
    
    Q_INVOKABLE QVariantList diffResults() const { return m_diffResults; }
    Q_INVOKABLE QString generateDiffReport(const QString& format = "text");
    Q_INVOKABLE bool exportDiffReport(const QString& outputPath, const QString& format = "text");
    
    Q_INVOKABLE QVariantList getFilteredResults(const QString& changeType);
    Q_INVOKABLE QVariantMap getDiffStatistics();

    int addedCount() const;
    int removedCount() const;
    int modifiedCount() const;
    int unchangedCount() const;

signals:
    void diffResultsChanged();
    void snapshotCreated(const QString& filePath);
    void snapshotRestored(const QString& filePath);
    void errorOccurred(const QString& error);

private:
    QVariantList parseConfigFile(const QString& filePath);
    QString detectFormat(const QString& filePath);
    QVariantList parseIniFile(const QString& filePath);
    QVariantList parseJsonFile(const QString& filePath);
    QVariantList parseXmlFile(const QString& filePath);
    QString getSnapshotPath(const QString& filePath, const QString& snapshotTime);
    QString getSnapshotsDir();

private:
    QVariantList m_diffResults;
    QString m_lastFile1;
    QString m_lastFile2;
};

#endif // CONFIGDIFF_H
