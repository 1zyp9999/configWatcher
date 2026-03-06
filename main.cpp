#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQuickStyle>
#include <QWindow>
#include <QQuickWindow>
#include <QUrl>
#include <QFileInfo>
#include <QDateTime>
#include <QStandardPaths>
#include <QDirIterator>
#include <QtConcurrent>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTimer>

#include "databasemanager.h"
#include "loginviewmodel.h"
#include "searchviewmodel.h"
#include "globalhotkey.h"

#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMutex>
#include <QMutexLocker>

// 日志输出到文件
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
    case QtWarningMsg: ts << "WARN: "; break;
    case QtCriticalMsg: ts << "CRITICAL: "; break;
    case QtFatalMsg: ts << "FATAL: "; break;
    default: break;
    }
    ts << msg << Qt::endl;
    ts.flush();
    if (type == QtFatalMsg) abort();
}

static void setupLogging()
{
    QString logDir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/log";
    QDir().mkpath(logDir);
    QString logPath = logDir + "/configwatcher.log";
    g_logFile.setFileName(logPath);
    if (!g_logFile.open(QIODevice::Append | QIODevice::Text)) {
        return;
    }
    qInstallMessageHandler(configWatcherMessageHandler);
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    setupLogging();
    QQuickStyle::setStyle("Basic");

    qmlRegisterType<LoginViewModel>("ConfigWatcher", 1, 0, "LoginViewModel");
    qmlRegisterType<SearchViewModel>("ConfigWatcher", 1, 0, "SearchViewModel");

    QQmlApplicationEngine engine;

    QString buildTime = QFileInfo(QCoreApplication::applicationFilePath()).lastModified().toString(Qt::DefaultLocaleLongDate);
    engine.rootContext()->setContextProperty("APP_BUILD_TIME", buildTime);
    engine.rootContext()->setContextProperty("APP_VERSION", "v0.0.1");
    engine.rootContext()->setContextProperty("APP_NAME", "ConfigWatcher");
    engine.rootContext()->setContextProperty("APP_AUTHOR", "张宇鹏");

    DatabaseManager *db = new DatabaseManager(&app);
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/Leichen/configwatcher.db";
    qDebug() << "[DEBUG] main: Opening database at" << dbPath;
    if (db->openDatabase(dbPath)) {
        qDebug() << "[DEBUG] main: Database opened successfully, exposing to QML as 'DB'";
        engine.rootContext()->setContextProperty("DB", db);
        QString baseDir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/Leichen";
        QtConcurrent::run([dbPath, baseDir]() {
            // Use a separate DB connection for the background thread
            DatabaseManager bgDb;
            if (!bgDb.openDatabase(dbPath, QStringLiteral("bg_import"), false /* don't set as global instance */)) {
                qWarning() << "Failed to open background DB connection";
                return;
            }
            QDirIterator it(baseDir, QStringList() << "*.ini" << "*.json" << "*.xml", QDir::Files, QDirIterator::Subdirectories);
            while (it.hasNext()) {
                const QString f = it.next();
                if (f.endsWith(".ini", Qt::CaseInsensitive)) bgDb.importIniFile(f);
                else if (f.endsWith(".json", Qt::CaseInsensitive)) bgDb.importJsonFile(f);
                else if (f.endsWith(".xml", Qt::CaseInsensitive)) bgDb.importXmlFile(f);
            }
            bgDb.closeDatabase();
        });
    }

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QWindow *fullWindow = nullptr;
    QQuickWindow *miniWindow = nullptr;
    const auto rootObjects = engine.rootObjects();
    if (!rootObjects.isEmpty()) {
        fullWindow = qobject_cast<QWindow *>(rootObjects.first());
        if (fullWindow) {
            fullWindow->showMaximized();
        }
    }

    // 创建精简模式窗口
    QQmlComponent miniComponent(&engine, QUrl(QStringLiteral("qrc:/qml/MiniMode.qml")));
    if (miniComponent.status() == QQmlComponent::Ready) {
        QObject *miniObj = miniComponent.create();
        if (miniObj) {
            miniWindow = qobject_cast<QQuickWindow *>(miniObj);
            if (miniWindow) {
                // 精简模式请求切换到完整模式
                QObject::connect(miniObj, SIGNAL(requestFullMode()), miniObj, SLOT(hide()));
                QObject::connect(miniObj, SIGNAL(requestFullMode()), fullWindow, SLOT(showMaximized()));
            }
        }
    } else {
        qWarning() << "MiniMode.qml load error:" << miniComponent.errorString();
    }

    // 完整模式中点击按钮请求切换到精简模式
    if (fullWindow && miniWindow) {
        QObject::connect(fullWindow, SIGNAL(requestMiniMode()), fullWindow, SLOT(hide()));
        QObject::connect(fullWindow, SIGNAL(requestMiniMode()), miniWindow, SLOT(show()));
    }

    // ========== 全局快捷键：Ctrl+Alt+M 切换模式 ==========
    GlobalHotkey *globalHotkey = new GlobalHotkey(&app);
    if (globalHotkey->registerHotkey("Ctrl+Alt+M")) {
        qApp->installNativeEventFilter(globalHotkey);

        QObject::connect(globalHotkey, &GlobalHotkey::activated, [fullWindow, miniWindow]() {
            if (!miniWindow || !fullWindow) return;

            if (miniWindow->isVisible()) {
                // 精简可见 → 隐藏精简，恢复完整
                miniWindow->hide();
                fullWindow->showMaximized();
                fullWindow->raise();
                fullWindow->requestActivate();
            } else {
                // 完整可见（或两者都隐藏）→ 隐藏完整，显示精简
                fullWindow->hide();
                miniWindow->show();
                miniWindow->raise();
                miniWindow->requestActivate();
            }
        });
        qDebug() << "Global hotkey enabled: Ctrl+Alt+M (toggle full/mini)";
    }

    // ========== 系统托盘 ==========
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(&app);
    QPixmap pixmap(32, 32);
    pixmap.fill(QColor("#2563EB"));
    trayIcon->setIcon(QIcon(pixmap));
    trayIcon->setToolTip("ConfigWatcher - 配置搜索工具\nCtrl+Alt+M 切换精简模式");
    
    QMenu *trayMenu = new QMenu();
    QAction *showMiniAction = trayMenu->addAction("精简模式");
    QAction *showFullAction = trayMenu->addAction("完整模式");
    QAction *quitAction = trayMenu->addAction("退出");
    
    QObject::connect(showMiniAction, &QAction::triggered, [=]() {
        if (fullWindow) fullWindow->hide();
        if (miniWindow) { miniWindow->show(); miniWindow->raise(); miniWindow->requestActivate(); }
    });
    QObject::connect(showFullAction, &QAction::triggered, [=]() {
        if (miniWindow) miniWindow->hide();
        if (fullWindow) { fullWindow->show(); fullWindow->raise(); fullWindow->requestActivate(); }
    });
    QObject::connect(quitAction, &QAction::triggered, &app, &QApplication::quit);
    QObject::connect(trayIcon, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::DoubleClick && miniWindow) {
            miniWindow->show(); miniWindow->raise(); miniWindow->requestActivate();
        }
    });
    
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    return app.exec();
}
