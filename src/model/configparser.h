#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <QObject>
#include <QStringList>
#include <QList>
#include <QFile>          // 新增
#include <QFileInfo>      // 新增
#include <QTextStream>    // 新增
#include <QJsonDocument>  // 新增
#include <QJsonObject>    // 新增
#include <QJsonArray>     // 新增
#include <QDir>           // 新增
#include <QIODevice>      // 新增
#include <QtConcurrent>   // 新增
#include <QByteArray>     // 新增
#include "configentry.h"

class ConfigParser : public QObject
{
    Q_OBJECT
public:
    explicit ConfigParser(QObject *parent = nullptr);

    // 加载配置文件
    void loadConfigFiles(const QStringList& filePaths);
    // 搜索配置项
    QList<ConfigEntry*> search(const QString& keyword);

signals:
    void loadFinished();
    void loadProgress(int progress);

private:
    QList<ConfigEntry*> m_allEntries;

    // 解析INI文件
    void parseIniFile(const QString& filePath);
    // 解析JSON文件
    void parseJsonFile(const QString& filePath);
    // 补充声明：递归遍历目录（之前缺失）
    QStringList getConfigFiles(const QString& dirPath);
};

#endif // CONFIGPARSER_H
