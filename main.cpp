#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QWindow>
#include <QUrl>  // 新增：QUrl 头文件
#include <QFileInfo>
#include <QDateTime>
#include "databasemanager.h"
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

// Logging helper: 将 Qt 日志写入 $HOME/.config/log/configwatcher.log（若不存在则创建）
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
    ts << endl;
    ts.flush();
    if (type == QtFatalMsg) abort();
}

static void setupLogging()
{
    QString logDir = QDir::homePath() + "/.config/log";
    QDir dir;
    if (!dir.exists(logDir)) {
        if (!dir.mkpath(logDir)) {
            qWarning() << "Failed to create log directory:" << logDir;
            return;
        }
    }
    QString logPath = logDir + "/configwatcher.log";
    g_logFile.setFileName(logPath);
    if (!g_logFile.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Failed to open log file:" << logPath;
        return;
    }
    qInstallMessageHandler(configWatcherMessageHandler);
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    // 启动时设置文件日志（越早越好，以便捕获后续的 qWarning/qDebug）
    setupLogging();

    // 设置Qt 5.15 原生样式
    QQuickStyle::setStyle("Basic");

    // 注册QML类型
    qmlRegisterType<LoginViewModel>("ConfigWatcher", 1, 0, "LoginViewModel");
    qmlRegisterType<SearchViewModel>("ConfigWatcher", 1, 0, "SearchViewModel");

    QQmlApplicationEngine engine;

    // 将编译时间等注入 QML 上下文，方便在 About 弹窗中显示
    // 优先使用当前可执行文件的最后修改时间（通常位于 bin/ 下）作为“最近编译时间”显示
    QString buildTime;
    QFileInfo exeInfo(QCoreApplication::applicationFilePath());
    if (exeInfo.exists()) {
        buildTime = exeInfo.lastModified().toString(Qt::DefaultLocaleLongDate);
    } else {
        // 回退到编译时间常量
        buildTime = QStringLiteral("%1 %2").arg(QLatin1String(__DATE__)).arg(QLatin1String(__TIME__));
    }
    engine.rootContext()->setContextProperty("APP_BUILD_TIME", buildTime);
    engine.rootContext()->setContextProperty("APP_VERSION", QStringLiteral("v0.0.1"));
    engine.rootContext()->setContextProperty("APP_NAME", QStringLiteral("ConfigWatcher"));
    engine.rootContext()->setContextProperty("APP_AUTHOR", QStringLiteral("张宇鹏"));

    // 初始化数据库并在后台导入配置文件到 DB，供搜索使用
    DatabaseManager *db = new DatabaseManager(&app);
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/Leichen/configwatcher.db";
    if (db->openDatabase(dbPath)) {
        engine.rootContext()->setContextProperty("DB", db);

        // 异步导入 ~/.config/Leichen 下的所有 ini/json 文件（递归）
        QString baseDir = QDir::homePath() + "/.config/Leichen";
        QtConcurrent::run([db, baseDir]() {
            QDirIterator it(baseDir, QStringList() << "*.ini" << "*.json", QDir::Files, QDirIterator::Subdirectories);
            while (it.hasNext()) {
                const QString f = it.next();
                db->importIniFile(f);
            }
        });
    } else {
        qWarning() << "Failed to open DB at" << dbPath;
    }

    // 修复：Qt 5.15 不支持 _qs 字面量，改用 QUrl 构造函数 + 普通字符串
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    // 获取主窗口对象并最大化（Qt 5.15 ApplicationWindow）
    QObject *topLevel = nullptr;
    const auto rootObjects = engine.rootObjects();
    if (!rootObjects.isEmpty()) {
        topLevel = rootObjects.first();
        QWindow *window = qobject_cast<QWindow *>(topLevel);
        if (window) {
            window->showMaximized();
        }
    }

    return app.exec();
}
