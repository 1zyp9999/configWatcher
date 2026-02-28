#include "appconfig.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>

AppConfig::AppConfig(QObject *parent) : QObject(parent)
{
    loadConfig();
}

QString AppConfig::expandPath(const QString& path)
{
    QString result = path;
    if (result.startsWith("~")) {
        result.replace(0, 1, QDir::homePath());
    }
    return result;
}

void AppConfig::loadConfig()
{
    // 默认值
    m_configSearchPath = QDir::homePath() + "/.config/Leichen";
    m_databasePath = QDir::homePath() + "/.config/ConfigWatcher/configwatcher.db";
    m_logPath = QDir::homePath() + "/.config/log/configwatcher.log";
    m_defaultUsername = "admin";
    m_minPasswordLength = 6;
    m_sessionTimeout = 30;
    m_defaultWidth = 1200;
    m_defaultHeight = 800;
    m_pageSize = 100;
    m_maxSearchResults = 500;
    m_maxImportFiles = 1000;
    m_searchTimeout = 5000;

    // 尝试从配置文件加载
    QString configPath = "appconfig.ini";
    if (!QFile::exists(configPath)) {
        configPath = QCoreApplication::applicationDirPath() + "/appconfig.ini";
    }
    
    if (QFile::exists(configPath)) {
        QSettings settings(configPath, QSettings::IniFormat);
        
        settings.beginGroup("Paths");
        if (settings.contains("ConfigSearchPath"))
            m_configSearchPath = expandPath(settings.value("ConfigSearchPath").toString());
        if (settings.contains("DatabasePath"))
            m_databasePath = expandPath(settings.value("DatabasePath").toString());
        if (settings.contains("LogPath"))
            m_logPath = expandPath(settings.value("LogPath").toString());
        settings.endGroup();
        
        settings.beginGroup("Security");
        if (settings.contains("DefaultUsername"))
            m_defaultUsername = settings.value("DefaultUsername").toString();
        if (settings.contains("MinPasswordLength"))
            m_minPasswordLength = settings.value("MinPasswordLength").toInt();
        if (settings.contains("SessionTimeout"))
            m_sessionTimeout = settings.value("SessionTimeout").toInt();
        settings.endGroup();
        
        settings.beginGroup("UI");
        if (settings.contains("DefaultWidth"))
            m_defaultWidth = settings.value("DefaultWidth").toInt();
        if (settings.contains("DefaultHeight"))
            m_defaultHeight = settings.value("DefaultHeight").toInt();
        if (settings.contains("PageSize"))
            m_pageSize = settings.value("PageSize").toInt();
        if (settings.contains("MaxSearchResults"))
            m_maxSearchResults = settings.value("MaxSearchResults").toInt();
        settings.endGroup();
        
        settings.beginGroup("Performance");
        if (settings.contains("MaxImportFiles"))
            m_maxImportFiles = settings.value("MaxImportFiles").toInt();
        if (settings.contains("SearchTimeout"))
            m_searchTimeout = settings.value("SearchTimeout").toInt();
        settings.endGroup();
    }
    
    // 确保目录存在
    QDir().mkpath(QFileInfo(m_databasePath).absoluteDir().absolutePath());
    QDir().mkpath(QFileInfo(m_logPath).absoluteDir().absolutePath());
}
