# ConfigWatcher 测试项目
QT += core gui quick sql network testlib concurrent widgets

CONFIG += c++11 testcase

# 启用 C++11 支持
QMAKE_CXXFLAGS += -std=c++11

# 项目名称
TARGET = ConfigWatcherTests
DESTDIR = ../bin/tests
OBJECTS_DIR = ../obj/tests
MOC_DIR = ../moc/tests
RCC_DIR = ../rcc/tests

# 头文件路径
INCLUDEPATH += ../include \
               ../src/model \
               ../src/viewmodel \
               ../src

# 主项目源文件（用于测试）
SOURCES += ../src/model/configparser.cpp \
           ../src/viewmodel/databasemanager.cpp \
           ../src/viewmodel/searchviewmodel.cpp \
           ../src/aiservice.cpp \
           ../src/filewatcher.cpp \
           ../src/configdiff.cpp \
           ../src/batchoperation.cpp \
           ../src/configvalidator.cpp \
           ../src/aiclient.cpp \
           ../src/globalhotkey.cpp

# 测试源文件
SOURCES += main.cpp

# 测试头文件（包含测试代码）
HEADERS += test_base.h \
           test_configentry.h \
           test_configparser.h \
           test_databasemanager.h \
           test_aiservice.h \
           test_filewatcher.h \
           test_configdiff.h \
           test_batchoperation.h \
           test_configvalidator.h \
           test_aiclient.h \
           test_searchviewmodel.h

# 测试数据文件
DIST += \
    test_data/test_config.ini \
    test_data/test_config.json \
    test_data/test_config.xml \
    test_data/test_schema.json

# 编译后运行测试
QMAKE_POST_LINK = $$quote($$DESTDIR/$$TARGET)
