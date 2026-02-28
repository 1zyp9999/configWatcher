QT += core gui quick quickcontrols2 concurrent widgets sql

CONFIG += c++11

# 项目名称与输出路径
TARGET = ConfigWatcher
DESTDIR = ./bin
OBJECTS_DIR = ./obj
MOC_DIR = ./moc
RCC_DIR = ./rcc

# 头文件路径
INCLUDEPATH += ./include ./src ./src/model ./src/viewmodel

# 源文件
SOURCES += main.cpp \
           src/appconfig.cpp \
           src/model/configparser.cpp \
           src/viewmodel/loginviewmodel.cpp \
           src/viewmodel/searchviewmodel.cpp \
           src/viewmodel/databasemanager.cpp

# 头文件
HEADERS += include/configentry.h \
           include/appconfig.h \
           include/databasemanager.h \
           include/searchviewmodel.h \
           src/model/configparser.h \
           src/viewmodel/loginviewmodel.h \
           src/viewmodel/searchviewmodel.h

# QML 文件（用于 Qt Creator 识别）
QML_FILES += res/qml/main.qml \
             res/qml/LoginPage.qml \
             res/qml/MainPage.qml \
             res/qml/Styles.qml \
             res/qml/TopMenuBar.qml \
             res/qml/ToolbarCard.qml \
             res/qml/ResultListView.qml \
             res/qml/PaginationControl.qml \
             res/qml/DetailDialog.qml

# 资源文件
RESOURCES += res/qml.qrc

# 移除 QML 类型生成配置（消除警告）
# QT += qml
# CONFIG += qmltypes
# QML_IMPORT_NAME = ConfigWatcher
# QML_IMPORT_MAJOR_VERSION = 1

# 打包相关（Windows）
win32 {
    RC_ICONS = res/images/app.ico
}

# 测试配置
unittest {
    QT += testlib
    CONFIG += qtestlib
    SOURCES += tests/tst_configparser.cpp \
               tests/tst_databasemanager.cpp
}
