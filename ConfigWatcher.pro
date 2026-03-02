QT += core gui quick quickcontrols2 concurrent widgets sql

CONFIG += c++11

# Linux X11 支持全局快捷键
linux {
    LIBS += -lX11 -lxcb
}

# 项目名称与输出路径
TARGET = ConfigWatcher
DESTDIR = ./bin
OBJECTS_DIR = ./obj
MOC_DIR = ./moc
RCC_DIR = ./rcc

# 头文件路径
INCLUDEPATH += ./include ./src/model ./src/viewmodel

# 源文件
SOURCES += main.cpp \
           src/model/configparser.cpp \
           src/viewmodel/loginviewmodel.cpp \
           src/viewmodel/searchviewmodel.cpp \
           src/viewmodel/databasemanager.cpp \
           src/aiservice.cpp \
           src/globalhotkey.cpp

# 头文件
HEADERS += include/configentry.h \
           src/model/configparser.h \
           src/viewmodel/loginviewmodel.h \
           include/searchviewmodel.h \
           include/databasemanager.h \
           include/aiservice.h \
           include/globalhotkey.h

# 资源文件
RESOURCES += res/qml.qrc

# QML 文件
QML_FILES += res/qml/main.qml \
             res/qml/MainPage.qml \
             res/qml/LoginPage.qml \
             res/qml/MiniWindow.qml

# 移除QML类型生成配置（消除警告）
# QT += qml
# CONFIG += qmltypes
# QML_IMPORT_NAME = ConfigWatcher
# QML_IMPORT_MAJOR_VERSION = 1

#  打包相关（Windows）
win32 {
    RC_ICONS = res/images/app.ico
}
