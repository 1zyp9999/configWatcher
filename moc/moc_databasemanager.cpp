/****************************************************************************
** Meta object code from reading C++ file 'databasemanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/databasemanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'databasemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DatabaseManager_t {
    QByteArrayData data[48];
    char stringdata0[629];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DatabaseManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DatabaseManager_t qt_meta_stringdata_DatabaseManager = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DatabaseManager"
QT_MOC_LITERAL(1, 16, 14), // "importProgress"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 7), // "current"
QT_MOC_LITERAL(4, 40, 5), // "total"
QT_MOC_LITERAL(5, 46, 11), // "currentFile"
QT_MOC_LITERAL(6, 58, 14), // "importFinished"
QT_MOC_LITERAL(7, 73, 12), // "successCount"
QT_MOC_LITERAL(8, 86, 9), // "failCount"
QT_MOC_LITERAL(9, 96, 13), // "importIniFile"
QT_MOC_LITERAL(10, 110, 8), // "filePath"
QT_MOC_LITERAL(11, 119, 6), // "device"
QT_MOC_LITERAL(12, 126, 14), // "importJsonFile"
QT_MOC_LITERAL(13, 141, 13), // "importXmlFile"
QT_MOC_LITERAL(14, 155, 16), // "importFilesAsync"
QT_MOC_LITERAL(15, 172, 9), // "filePaths"
QT_MOC_LITERAL(16, 182, 16), // "listTranslations"
QT_MOC_LITERAL(17, 199, 14), // "setTranslation"
QT_MOC_LITERAL(18, 214, 3), // "key"
QT_MOC_LITERAL(19, 218, 7), // "chinese"
QT_MOC_LITERAL(20, 226, 29), // "applyTranslationsToParameters"
QT_MOC_LITERAL(21, 256, 16), // "searchParameters"
QT_MOC_LITERAL(22, 273, 5), // "query"
QT_MOC_LITERAL(23, 279, 4), // "mode"
QT_MOC_LITERAL(24, 284, 12), // "formatFilter"
QT_MOC_LITERAL(25, 297, 11), // "listAllKeys"
QT_MOC_LITERAL(26, 309, 9), // "listFiles"
QT_MOC_LITERAL(27, 319, 12), // "addChangeLog"
QT_MOC_LITERAL(28, 332, 8), // "oldValue"
QT_MOC_LITERAL(29, 341, 8), // "newValue"
QT_MOC_LITERAL(30, 350, 13), // "getChangeLogs"
QT_MOC_LITERAL(31, 364, 5), // "limit"
QT_MOC_LITERAL(32, 370, 20), // "getChangeLogsForFile"
QT_MOC_LITERAL(33, 391, 15), // "deleteChangeLog"
QT_MOC_LITERAL(34, 407, 9), // "changedAt"
QT_MOC_LITERAL(35, 417, 15), // "clearChangeLogs"
QT_MOC_LITERAL(36, 433, 16), // "setFieldReadOnly"
QT_MOC_LITERAL(37, 450, 8), // "readOnly"
QT_MOC_LITERAL(38, 459, 15), // "isFieldReadOnly"
QT_MOC_LITERAL(39, 475, 17), // "getReadOnlyFields"
QT_MOC_LITERAL(40, 493, 20), // "getAllReadOnlyFields"
QT_MOC_LITERAL(41, 514, 14), // "importTemplate"
QT_MOC_LITERAL(42, 529, 16), // "templateFilePath"
QT_MOC_LITERAL(43, 546, 14), // "targetFilePath"
QT_MOC_LITERAL(44, 561, 13), // "applyTemplate"
QT_MOC_LITERAL(45, 575, 16), // "getTemplateFiles"
QT_MOC_LITERAL(46, 592, 14), // "deleteTemplate"
QT_MOC_LITERAL(47, 607, 21) // "getTemplateFieldCount"

    },
    "DatabaseManager\0importProgress\0\0current\0"
    "total\0currentFile\0importFinished\0"
    "successCount\0failCount\0importIniFile\0"
    "filePath\0device\0importJsonFile\0"
    "importXmlFile\0importFilesAsync\0filePaths\0"
    "listTranslations\0setTranslation\0key\0"
    "chinese\0applyTranslationsToParameters\0"
    "searchParameters\0query\0mode\0formatFilter\0"
    "listAllKeys\0listFiles\0addChangeLog\0"
    "oldValue\0newValue\0getChangeLogs\0limit\0"
    "getChangeLogsForFile\0deleteChangeLog\0"
    "changedAt\0clearChangeLogs\0setFieldReadOnly\0"
    "readOnly\0isFieldReadOnly\0getReadOnlyFields\0"
    "getAllReadOnlyFields\0importTemplate\0"
    "templateFilePath\0targetFilePath\0"
    "applyTemplate\0getTemplateFiles\0"
    "deleteTemplate\0getTemplateFieldCount"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DatabaseManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,  184,    2, 0x06 /* Public */,
       6,    2,  191,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       9,    2,  196,    2, 0x02 /* Public */,
       9,    1,  201,    2, 0x22 /* Public | MethodCloned */,
      12,    2,  204,    2, 0x02 /* Public */,
      12,    1,  209,    2, 0x22 /* Public | MethodCloned */,
      13,    2,  212,    2, 0x02 /* Public */,
      13,    1,  217,    2, 0x22 /* Public | MethodCloned */,
      14,    2,  220,    2, 0x02 /* Public */,
      14,    1,  225,    2, 0x22 /* Public | MethodCloned */,
      16,    0,  228,    2, 0x02 /* Public */,
      17,    2,  229,    2, 0x02 /* Public */,
      20,    0,  234,    2, 0x02 /* Public */,
      21,    3,  235,    2, 0x02 /* Public */,
      21,    2,  242,    2, 0x22 /* Public | MethodCloned */,
      21,    1,  247,    2, 0x22 /* Public | MethodCloned */,
      25,    0,  250,    2, 0x02 /* Public */,
      26,    0,  251,    2, 0x02 /* Public */,
      27,    4,  252,    2, 0x02 /* Public */,
      30,    1,  261,    2, 0x02 /* Public */,
      30,    0,  264,    2, 0x22 /* Public | MethodCloned */,
      32,    2,  265,    2, 0x02 /* Public */,
      32,    1,  270,    2, 0x22 /* Public | MethodCloned */,
      33,    3,  273,    2, 0x02 /* Public */,
      35,    0,  280,    2, 0x02 /* Public */,
      36,    3,  281,    2, 0x02 /* Public */,
      38,    2,  288,    2, 0x02 /* Public */,
      39,    1,  293,    2, 0x02 /* Public */,
      40,    0,  296,    2, 0x02 /* Public */,
      41,    2,  297,    2, 0x02 /* Public */,
      44,    1,  302,    2, 0x02 /* Public */,
      45,    0,  305,    2, 0x02 /* Public */,
      46,    1,  306,    2, 0x02 /* Public */,
      47,    1,  309,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,

 // methods: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Bool, QMetaType::QString,   10,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Bool, QMetaType::QString,   10,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Bool, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QStringList, QMetaType::QString,   15,   11,
    QMetaType::Void, QMetaType::QStringList,   15,
    QMetaType::QVariantList,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   18,   19,
    QMetaType::Bool,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::Int, QMetaType::QString,   22,   23,   24,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::Int,   22,   23,
    QMetaType::QVariantList, QMetaType::QString,   22,
    QMetaType::QStringList,
    QMetaType::QVariantList,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   10,   18,   28,   29,
    QMetaType::QVariantList, QMetaType::Int,   31,
    QMetaType::QVariantList,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::Int,   10,   31,
    QMetaType::QVariantList, QMetaType::QString,   10,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString,   10,   18,   34,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::Bool,   10,   18,   37,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   10,   18,
    QMetaType::QVariantList, QMetaType::QString,   10,
    QMetaType::QVariantList,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   42,   43,
    QMetaType::Bool, QMetaType::QString,   42,
    QMetaType::QVariantList,
    QMetaType::Bool, QMetaType::QString,   42,
    QMetaType::Int, QMetaType::QString,   42,

       0        // eod
};

void DatabaseManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DatabaseManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->importProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 1: _t->importFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: { bool _r = _t->importIniFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->importIniFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->importJsonFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->importJsonFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->importXmlFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->importXmlFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->importFilesAsync((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->importFilesAsync((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 10: { QVariantList _r = _t->listTranslations();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->setTranslation((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->applyTranslationsToParameters();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { QVariantList _r = _t->searchParameters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 14: { QVariantList _r = _t->searchParameters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 15: { QVariantList _r = _t->searchParameters((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 16: { QStringList _r = _t->listAllKeys();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 17: { QVariantList _r = _t->listFiles();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 18: { bool _r = _t->addChangeLog((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 19: { QVariantList _r = _t->getChangeLogs((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 20: { QVariantList _r = _t->getChangeLogs();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 21: { QVariantList _r = _t->getChangeLogsForFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 22: { QVariantList _r = _t->getChangeLogsForFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 23: { bool _r = _t->deleteChangeLog((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 24: _t->clearChangeLogs(); break;
        case 25: { bool _r = _t->setFieldReadOnly((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 26: { bool _r = _t->isFieldReadOnly((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 27: { QVariantList _r = _t->getReadOnlyFields((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 28: { QVariantList _r = _t->getAllReadOnlyFields();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 29: { bool _r = _t->importTemplate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 30: { bool _r = _t->applyTemplate((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 31: { QVariantList _r = _t->getTemplateFiles();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 32: { bool _r = _t->deleteTemplate((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 33: { int _r = _t->getTemplateFieldCount((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DatabaseManager::*)(int , int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DatabaseManager::importProgress)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DatabaseManager::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DatabaseManager::importFinished)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DatabaseManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DatabaseManager.data,
    qt_meta_data_DatabaseManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DatabaseManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DatabaseManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DatabaseManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DatabaseManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 34)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 34;
    }
    return _id;
}

// SIGNAL 0
void DatabaseManager::importProgress(int _t1, int _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DatabaseManager::importFinished(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
