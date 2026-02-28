#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>
#include <QString>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>

class AppConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString configSearchPath READ configSearchPath CONSTANT)
    Q_PROPERTY(QString databasePath READ databasePath CONSTANT)
    Q_PROPERTY(QString logPath READ logPath CONSTANT)
    Q_PROPERTY(QString defaultUsername READ defaultUsername CONSTANT)
    Q_PROPERTY(int minPasswordLength READ minPasswordLength CONSTANT)
    Q_PROPERTY(int sessionTimeout READ sessionTimeout CONSTANT)
    Q_PROPERTY(int defaultWidth READ defaultWidth CONSTANT)
    Q_PROPERTY(int defaultHeight READ defaultHeight CONSTANT)
    Q_PROPERTY(int pageSize READ pageSize CONSTANT)
    Q_PROPERTY(int maxSearchResults READ maxSearchResults CONSTANT)
    Q_PROPERTY(int maxImportFiles READ maxImportFiles CONSTANT)
    Q_PROPERTY(int searchTimeout READ searchTimeout CONSTANT)

public:
    explicit AppConfig(QObject *parent = nullptr);

    QString configSearchPath() const { return m_configSearchPath; }
    QString databasePath() const { return m_databasePath; }
    QString logPath() const { return m_logPath; }
    QString defaultUsername() const { return m_defaultUsername; }
    int minPasswordLength() const { return m_minPasswordLength; }
    int sessionTimeout() const { return m_sessionTimeout; }
    int defaultWidth() const { return m_defaultWidth; }
    int defaultHeight() const { return m_defaultHeight; }
    int pageSize() const { return m_pageSize; }
    int maxSearchResults() const { return m_maxSearchResults; }
    int maxImportFiles() const { return m_maxImportFiles; }
    int searchTimeout() const { return m_searchTimeout; }

    // 辅助函数：展开路径中的~
    static QString expandPath(const QString& path);

private:
    void loadConfig();

    QString m_configSearchPath;
    QString m_databasePath;
    QString m_logPath;
    QString m_defaultUsername;
    int m_minPasswordLength;
    int m_sessionTimeout;
    int m_defaultWidth;
    int m_defaultHeight;
    int m_pageSize;
    int m_maxSearchResults;
    int m_maxImportFiles;
    int m_searchTimeout;
};

#endif // APPCONFIG_H
