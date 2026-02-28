#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>
#include <QVariant>
#include <QMutex>
#include <QSharedPointer>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject* parent = nullptr);
    ~DatabaseManager() override;

    bool openDatabase(const QString& path);
    void closeDatabase();

    bool saveConfigEntry(const QString& key, const QString& value, const QString& filePath, const QString& format, const QString& chineseKey);

    // 导入 ini 文件
    Q_INVOKABLE bool importIniFile(const QString& filePath, const QString& device = QString());

    // 翻译表管理
    Q_INVOKABLE QVariantList listTranslations();
    Q_INVOKABLE bool setTranslation(const QString& key, const QString& chinese);
    Q_INVOKABLE bool applyTranslationsToParameters();

    // 搜索（支持 FTS5 或回退到 LIKE）
    Q_INVOKABLE QVariantList searchParameters(const QString& query, int mode = 0);
    Q_INVOKABLE QStringList listAllKeys();
    Q_INVOKABLE QVariantList listFiles();

    // Global instance accessor
    static DatabaseManager* instance();

private:
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
    bool m_useFts5 = false;
    mutable QMutex m_dbMutex;  // 线程安全保护
    static QSharedPointer<DatabaseManager> s_instance;  // 使用智能指针管理单例
};

#endif // DATABASEMANAGER_H
