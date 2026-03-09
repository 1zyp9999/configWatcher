# ConfigWatcher 核心测试项目

QT += core sql testlib concurrent network

CONFIG += c++11 testcase

TARGET = ConfigWatcherTests
DESTDIR = ../bin/tests
OBJECTS_DIR = ../obj/tests
MOC_DIR = ../moc/tests

INCLUDEPATH += ../include \
               ../src/model \
               ../src/viewmodel \
               ../src

# 核心模块
HEADERS += \
    ../include/configentry.h \
    ../src/model/configparser.h \
    ../include/databasemanager.h \
    ../include/aiservice.h \
    ../include/filewatcher.h \
    ../include/configdiff.h \
    ../include/batchoperation.h \
    ../include/configvalidator.h \
    ../include/aiclient.h

SOURCES += \
    ../src/model/configparser.cpp \
    ../src/viewmodel/databasemanager.cpp \
    ../src/aiservice.cpp \
    ../src/filewatcher.cpp \
    ../src/configdiff.cpp \
    ../src/batchoperation.cpp \
    ../src/configvalidator.cpp \
    ../src/aiclient.cpp \
    main.cpp

# 测试数据
DIST += \
    test_data/test_config.ini \
    test_data/test_config.json \
    test_data/test_config.xml \
    test_data/test_schema.json
