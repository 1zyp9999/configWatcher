#ifndef BATCHOPERATION_H
#define BATCHOPERATION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariantList>
#include <QVariantMap>

class BatchOperation : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int totalOperations READ totalOperations NOTIFY operationsChanged)
    Q_PROPERTY(int completedOperations READ completedOperations NOTIFY progressChanged)
    Q_PROPERTY(int failedOperations READ failedOperations NOTIFY progressChanged)
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY runningChanged)
    Q_PROPERTY(QString currentOperation READ currentOperation NOTIFY currentOperationChanged)

public:
    explicit BatchOperation(QObject* parent = nullptr);
    ~BatchOperation();

    int totalOperations() const { return m_totalOperations; }
    int completedOperations() const { return m_completedOperations; }
    int failedOperations() const { return m_failedOperations; }
    bool isRunning() const { return m_isRunning; }
    QString currentOperation() const { return m_currentOperation; }

    Q_INVOKABLE bool batchUpdateValues(const QVariantList& entries);
    Q_INVOKABLE bool batchUpdateValue(const QString& key, const QString& newValue, const QStringList& filePaths);
    Q_INVOKABLE bool batchDelete(const QStringList& keys, const QString& filePath);
    Q_INVOKABLE bool batchAddSection(const QString& sectionName, const QVariantList& entries, const QString& filePath);
    
    Q_INVOKABLE bool batchImport(const QString& sourceDir, const QString& targetDir, const QStringList& filters);
    Q_INVOKABLE bool batchExport(const QStringList& filePaths, const QString& targetDir, const QString& format = "original");
    Q_INVOKABLE bool exportToCsv(const QString& filePath, const QString& outputPath);
    Q_INVOKABLE bool exportToJson(const QString& filePath, const QString& outputPath);
    Q_INVOKABLE bool importFromCsv(const QString& csvPath, const QString& targetFilePath);
    Q_INVOKABLE bool importFromJson(const QString& jsonPath, const QString& targetFilePath);
    
    Q_INVOKABLE bool batchReplace(const QString& searchText, const QString& replaceText, const QStringList& keys, const QString& filePath);
    Q_INVOKABLE bool batchApplyTemplate(const QString& templateFilePath, const QStringList& targetFilePaths);
    Q_INVOKABLE bool batchSetReadOnly(const QStringList& keys, const QString& filePath, bool readOnly);
    
    Q_INVOKABLE QVariantList getOperationLog();
    Q_INVOKABLE void clearOperationLog();
    Q_INVOKABLE bool undoLastOperation();
    Q_INVOKABLE bool canUndo() const;

signals:
    void operationsChanged();
    void progressChanged(int completed, int total);
    void runningChanged(bool running);
    void currentOperationChanged(const QString& operation);
    void operationCompleted(const QString& operation, bool success, const QString& message);
    void batchFinished(int successCount, int failCount);

private:
    bool writeIniFile(const QString& filePath, const QVariantList& entries);
    bool writeJsonFile(const QString& filePath, const QVariantList& entries);
    bool writeXmlFile(const QString& filePath, const QVariantList& entries);
    QVariantList readConfigFile(const QString& filePath);
    QString detectFormat(const QString& filePath);
    void logOperation(const QString& type, const QString& target, bool success, const QString& message);
    void backupFile(const QString& filePath);

private:
    int m_totalOperations;
    int m_completedOperations;
    int m_failedOperations;
    bool m_isRunning;
    QString m_currentOperation;
    QVariantList m_operationLog;
    QVariantMap m_lastBackup;
};

#endif // BATCHOPERATION_H
