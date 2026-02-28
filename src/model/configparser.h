#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <QObject>
#include <QStringList>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QIODevice>
#include <QtConcurrent>
#include <QByteArray>
#include <QMutex>
#include <QSharedPointer>
#include "configentry.h"

class ConfigParser : public QObject
{
    Q_OBJECT
public:
    explicit ConfigParser(QObject *parent = nullptr);
    ~ConfigParser() override;

    // 加载配置文件
    void loadConfigFiles(const QStringList& filePaths);
    // 搜索配置项
    QList<QSharedPointer<ConfigEntry>> search(const QString& keyword);
    // 获取所有条目
    QList<QSharedPointer<ConfigEntry>> allEntries() const { return m_allEntries; }

signals:
    void loadFinished();
    void loadProgress(int progress);
    void errorOccurred(const QString& message);

private:
    QList<QSharedPointer<ConfigEntry>> m_allEntries;
    mutable QMutex m_entriesMutex;

    // 解析 INI 文件
    bool parseIniFile(const QString& filePath);
    // 解析 JSON 文件
    bool parseJsonFile(const QString& filePath);
    // 递归遍历目录
    QStringList getConfigFiles(const QString& dirPath);
};

#endif // CONFIGPARSER_H
