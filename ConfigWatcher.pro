QT += core gui quick quickcontrols2 concurrent widgets sql  # 新增：widgets、sql 模块（QFileDialog 与 SQLite 依赖）

CONFIG += c++11

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
           src/aiservice.cpp

# 头文件
HEADERS += include/configentry.h \
           src/model/configparser.h \
           src/viewmodel/loginviewmodel.h \
           include/searchviewmodel.h \
           include/databasemanager.h \
           include/aiservice.h

# 资源文件
RESOURCES += res/qml.qrc

# 移除QML类型生成配置（消除警告）
# QT += qml
# CONFIG += qmltypes
# QML_IMPORT_NAME = ConfigWatcher
# QML_IMPORT_MAJOR_VERSION = 1

#  打包相关（Windows）
win32 {
    RC_ICONS = res/images/app.ico
}
