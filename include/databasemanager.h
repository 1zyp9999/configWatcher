#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>
#include <QVariant>
#include <QMap>
#include <QDateTime>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject* parent = nullptr);
    ~DatabaseManager();

    bool openDatabase(const QString& path, const QString& connectionName = QString(), bool setAsGlobalInstance = true);
    void closeDatabase();
    void invalidateCache();

    bool saveConfigEntry(const QString& key, const QString& value, const QString& filePath, const QString& format, const QString& chineseKey);

    // 导入配置文件
    Q_INVOKABLE bool importIniFile(const QString& filePath, const QString& device = QString());
    Q_INVOKABLE bool importJsonFile(const QString& filePath, const QString& device = QString());
    Q_INVOKABLE bool importXmlFile(const QString& filePath, const QString& device = QString());
    
    // 异步导入配置文件
    Q_INVOKABLE void importFilesAsync(const QStringList& filePaths, const QString& device = QString());

signals:
    void importProgress(int current, int total, const QString& currentFile);
    void importFinished(int successCount, int failCount);

public:

    // 翻译表管理：列出、设置并将翻译应用到 parameters
    Q_INVOKABLE QVariantList listTranslations();
    Q_INVOKABLE bool setTranslation(const QString& key, const QString& chinese);
    Q_INVOKABLE bool applyTranslationsToParameters();

    // 搜索（支持 FTS5 或回退到 LIKE），formatFilter 为空则不过滤
    Q_INVOKABLE QVariantList searchParameters(const QString& query, int mode = 0, const QString& formatFilter = QString()); // mode:0 fuzzy,1 exact
    Q_INVOKABLE QStringList listAllKeys();
    Q_INVOKABLE QVariantList listFiles();

    // 修改记录
    Q_INVOKABLE bool addChangeLog(const QString& filePath, const QString& key, const QString& oldValue, const QString& newValue);
    Q_INVOKABLE QVariantList getChangeLogs(int limit = 50);
    Q_INVOKABLE QVariantList getChangeLogsForFile(const QString& filePath, int limit = 50);
    Q_INVOKABLE bool deleteChangeLog(const QString& filePath, const QString& key, const QString& changedAt);
    Q_INVOKABLE void clearChangeLogs();

    // 只读字段管理
    Q_INVOKABLE bool setFieldReadOnly(const QString& filePath, const QString& key, bool readOnly);
    Q_INVOKABLE bool isFieldReadOnly(const QString& filePath, const QString& key);
    Q_INVOKABLE QVariantList getReadOnlyFields(const QString& filePath);
    Q_INVOKABLE QVariantList getAllReadOnlyFields();

    // 模板管理
    Q_INVOKABLE bool importTemplate(const QString& templateFilePath, const QString& targetFilePath);
    Q_INVOKABLE bool applyTemplate(const QString& templateFilePath);
    Q_INVOKABLE QVariantList getTemplateFiles();
    Q_INVOKABLE bool deleteTemplate(const QString& templateFilePath);
    Q_INVOKABLE int getTemplateFieldCount(const QString& templateFilePath);

    // Global instance accessor (set when openDatabase is called)
    static DatabaseManager* instance();

private:
    // helper declarations used by implementation
    int ensureFile(const QString& path, const QString& format);
    int ensureSection(int fileId, const QString& name, int itemIndex = -1);
    bool upsertParameter(int fileId,
                         int sectionId,
                         const QString& key,
                         const QString& rawValue,
                         const QString& valueType,
                         double num1,
                         double num2,
                         const QString& device,
                         const QString& chineseName,
                         const QString& description);

private:
    QSqlDatabase m_db;
    QString m_connectionName;
    bool m_useFts5 = false;
    static DatabaseManager* s_instance;
    
    struct QueryCache {
        QString key;
        QVariantList result;
        qint64 timestamp;
    };
    QMap<QString, QueryCache> m_queryCache;
    qint64 m_cacheTtl = 5000;
    int m_maxCacheSize = 100;
    
    QString makeCacheKey(const QString& query, int mode, const QString& formatFilter);
    bool isCacheValid(const QueryCache& cache);
    void cleanOldCache();
};

#endif // DATABASEMANAGER_H
