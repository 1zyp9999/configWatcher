#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QWindow>
#include <QUrl>
#include <QFileInfo>
#include <QDateTime>
#include "databasemanager.h"
#include "appconfig.h"
#include <QStandardPaths>
#include <QDirIterator>
#include <QtConcurrent>
#include "loginviewmodel.h"
#include "searchviewmodel.h"

#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMutex>
#include <QMutexLocker>

// Logging helper
static QFile g_logFile;
static QMutex g_logMutex;

static void configWatcherMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QMutexLocker locker(&g_logMutex);
    if (!g_logFile.isOpen()) return;
    
    QTextStream ts(&g_logFile);
    ts << QDateTime::currentDateTime().toString(Qt::ISODate) << " ";
    
    switch (type) {
    case QtDebugMsg: ts << "DEBUG: "; break;
#if (QT_VERSION >= QT_VERSION_CHECK(5, 5, 0))
    case QtInfoMsg: ts << "INFO: "; break;
#endif
    case QtWarningMsg: ts << "WARN: "; break;
    case QtCriticalMsg: ts << "CRITICAL: "; break;
    case QtFatalMsg: ts << "FATAL: "; break;
    }
    
    ts << msg;
    if (context.file && context.line) {
        ts << " (" << context.file << ":" << context.line << ")";
    }
    ts << Qt::endl;
    ts.flush();
    
    if (type == QtFatalMsg) abort();
}

static void setupLogging(const QString& logPath)
{
    QDir dir;
    QString logDir = QFileInfo(logPath).absoluteDir().path();
    
    if (!dir.exists(logDir)) {
        if (!dir.mkpath(logDir)) {
            qWarning() << "Failed to create log directory:" << logDir;
            return;
        }
    }
    
    g_logFile.setFileName(logPath);
    if (!g_logFile.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Failed to open log file:" << logPath;
        return;
    }
    
    qInstallMessageHandler(configWatcherMessageHandler);
    qDebug() << "Logging initialized to:" << logPath;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("ConfigWatcher");
    QCoreApplication::setApplicationVersion("v0.1.0");
    QCoreApplication::setOrganizationName("ConfigWatcher");

    // 加载应用配置
    AppConfig appConfig;
    
    // 启动时设置文件日志
    setupLogging(appConfig.logPath());

    // 设置 Qt 5.15 原生样式
    QQuickStyle::setStyle("Basic");

    // 注册 QML 类型
    qmlRegisterType<LoginViewModel>("ConfigWatcher", 1, 0, "LoginViewModel");
    qmlRegisterType<SearchViewModel>("ConfigWatcher", 1, 0, "SearchViewModel");
    qmlRegisterUncreatableType<AppConfig>("ConfigWatcher", 1, 0, "AppConfig", 
        "AppConfig is provided via context property");

    QQmlApplicationEngine engine;

    // 将应用配置注入 QML 上下文
    engine.rootContext()->setContextProperty("AppConfig", &appConfig);

    // 将编译时间等注入 QML 上下文
    QString buildTime;
    QFileInfo exeInfo(QCoreApplication::applicationFilePath());
    if (exeInfo.exists()) {
        buildTime = exeInfo.lastModified().toString(Qt::DefaultLocaleLongDate);
    } else {
        buildTime = QStringLiteral("%1 %2").arg(QLatin1String(__DATE__)).arg(QLatin1String(__TIME__));
    }
    engine.rootContext()->setContextProperty("APP_BUILD_TIME", buildTime);
    engine.rootContext()->setContextProperty("APP_VERSION", QStringLiteral("v0.1.0"));
    engine.rootContext()->setContextProperty("APP_NAME", QStringLiteral("ConfigWatcher"));
    engine.rootContext()->setContextProperty("APP_AUTHOR", QStringLiteral("张宇鹏"));

    // 初始化数据库并在后台导入配置文件到 DB
    auto db = new DatabaseManager(&app);
    if (db->openDatabase(appConfig.databasePath())) {
        engine.rootContext()->setContextProperty("DB", db);

        // 异步导入配置文件（递归）
        QString baseDir = appConfig.configSearchPath();
        int maxFiles = appConfig.maxImportFiles();
        QtConcurrent::run([db, baseDir, maxFiles]() {
            if (!QDir(baseDir).exists()) {
                qWarning() << "Config directory does not exist:" << baseDir;
                return;
            }
            
            QDirIterator it(baseDir, QStringList() << "*.ini" << "*.json", 
                           QDir::Files, QDirIterator::Subdirectories);
            
            int count = 0;
            while (it.hasNext() && count < maxFiles) {
                const QString f = it.next();
                db->importIniFile(f);
                count++;
            }
            
            qDebug() << "Imported" << count << "config files";
        });
    } else {
        qWarning() << "Failed to open DB at" << appConfig.databasePath();
    }

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            qCritical() << "Failed to load QML";
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);

    engine.load(url);

    // 获取主窗口对象并最大化
    QObject *topLevel = nullptr;
    const auto rootObjects = engine.rootObjects();
    if (!rootObjects.isEmpty()) {
        topLevel = rootObjects.first();
        QWindow *window = qobject_cast<QWindow *>(topLevel);
        if (window) {
            window->showMaximized();
        }
    }

    qDebug() << "Application started successfully";
    return app.exec();
}
