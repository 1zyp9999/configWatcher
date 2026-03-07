/****************************************************************************
** Meta object code from reading C++ file 'configdiff.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/configdiff.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configdiff.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConfigDiff_t {
    QByteArrayData data[35];
    char stringdata0[454];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigDiff_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigDiff_t qt_meta_stringdata_ConfigDiff = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ConfigDiff"
QT_MOC_LITERAL(1, 11, 18), // "diffResultsChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 15), // "snapshotCreated"
QT_MOC_LITERAL(4, 47, 8), // "filePath"
QT_MOC_LITERAL(5, 56, 16), // "snapshotRestored"
QT_MOC_LITERAL(6, 73, 13), // "errorOccurred"
QT_MOC_LITERAL(7, 87, 5), // "error"
QT_MOC_LITERAL(8, 93, 12), // "compareFiles"
QT_MOC_LITERAL(9, 106, 9), // "file1Path"
QT_MOC_LITERAL(10, 116, 9), // "file2Path"
QT_MOC_LITERAL(11, 126, 19), // "compareWithDatabase"
QT_MOC_LITERAL(12, 146, 14), // "compareConfigs"
QT_MOC_LITERAL(13, 161, 7), // "config1"
QT_MOC_LITERAL(14, 169, 7), // "config2"
QT_MOC_LITERAL(15, 177, 16), // "compareSnapshots"
QT_MOC_LITERAL(16, 194, 9), // "snapshot1"
QT_MOC_LITERAL(17, 204, 9), // "snapshot2"
QT_MOC_LITERAL(18, 214, 14), // "createSnapshot"
QT_MOC_LITERAL(19, 229, 13), // "listSnapshots"
QT_MOC_LITERAL(20, 243, 14), // "deleteSnapshot"
QT_MOC_LITERAL(21, 258, 12), // "snapshotTime"
QT_MOC_LITERAL(22, 271, 15), // "restoreSnapshot"
QT_MOC_LITERAL(23, 287, 11), // "diffResults"
QT_MOC_LITERAL(24, 299, 18), // "generateDiffReport"
QT_MOC_LITERAL(25, 318, 6), // "format"
QT_MOC_LITERAL(26, 325, 16), // "exportDiffReport"
QT_MOC_LITERAL(27, 342, 10), // "outputPath"
QT_MOC_LITERAL(28, 353, 18), // "getFilteredResults"
QT_MOC_LITERAL(29, 372, 10), // "changeType"
QT_MOC_LITERAL(30, 383, 17), // "getDiffStatistics"
QT_MOC_LITERAL(31, 401, 10), // "addedCount"
QT_MOC_LITERAL(32, 412, 12), // "removedCount"
QT_MOC_LITERAL(33, 425, 13), // "modifiedCount"
QT_MOC_LITERAL(34, 439, 14) // "unchangedCount"

    },
    "ConfigDiff\0diffResultsChanged\0\0"
    "snapshotCreated\0filePath\0snapshotRestored\0"
    "errorOccurred\0error\0compareFiles\0"
    "file1Path\0file2Path\0compareWithDatabase\0"
    "compareConfigs\0config1\0config2\0"
    "compareSnapshots\0snapshot1\0snapshot2\0"
    "createSnapshot\0listSnapshots\0"
    "deleteSnapshot\0snapshotTime\0restoreSnapshot\0"
    "diffResults\0generateDiffReport\0format\0"
    "exportDiffReport\0outputPath\0"
    "getFilteredResults\0changeType\0"
    "getDiffStatistics\0addedCount\0removedCount\0"
    "modifiedCount\0unchangedCount"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigDiff[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       5,  172, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x06 /* Public */,
       3,    1,  110,    2, 0x06 /* Public */,
       5,    1,  113,    2, 0x06 /* Public */,
       6,    1,  116,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       8,    2,  119,    2, 0x02 /* Public */,
      11,    1,  124,    2, 0x02 /* Public */,
      12,    2,  127,    2, 0x02 /* Public */,
      15,    3,  132,    2, 0x02 /* Public */,
      18,    1,  139,    2, 0x02 /* Public */,
      19,    1,  142,    2, 0x02 /* Public */,
      20,    2,  145,    2, 0x02 /* Public */,
      22,    2,  150,    2, 0x02 /* Public */,
      23,    0,  155,    2, 0x02 /* Public */,
      24,    1,  156,    2, 0x02 /* Public */,
      24,    0,  159,    2, 0x22 /* Public | MethodCloned */,
      26,    2,  160,    2, 0x02 /* Public */,
      26,    1,  165,    2, 0x22 /* Public | MethodCloned */,
      28,    1,  168,    2, 0x02 /* Public */,
      30,    0,  171,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    7,

 // methods: parameters
    QMetaType::QVariantList, QMetaType::QString, QMetaType::QString,    9,   10,
    QMetaType::QVariantList, QMetaType::QString,    4,
    QMetaType::QVariantList, QMetaType::QVariantList, QMetaType::QVariantList,   13,   14,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,   16,   17,
    QMetaType::Bool, QMetaType::QString,    4,
    QMetaType::QVariantList, QMetaType::QString,    4,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,    4,   21,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,    4,   21,
    QMetaType::QVariantList,
    QMetaType::QString, QMetaType::QString,   25,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   27,   25,
    QMetaType::Bool, QMetaType::QString,   27,
    QMetaType::QVariantList, QMetaType::QString,   29,
    QMetaType::QVariantMap,

 // properties: name, type, flags
      23, QMetaType::QVariantList, 0x00495001,
      31, QMetaType::Int, 0x00495001,
      32, QMetaType::Int, 0x00495001,
      33, QMetaType::Int, 0x00495001,
      34, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,
       0,

       0        // eod
};

void ConfigDiff::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConfigDiff *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->diffResultsChanged(); break;
        case 1: _t->snapshotCreated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->snapshotRestored((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: { QVariantList _r = _t->compareFiles((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 5: { QVariantList _r = _t->compareWithDatabase((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 6: { QVariantList _r = _t->compareConfigs((*reinterpret_cast< const QVariantList(*)>(_a[1])),(*reinterpret_cast< const QVariantList(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 7: { QVariantList _r = _t->compareSnapshots((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->createSnapshot((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { QVariantList _r = _t->listSnapshots((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->deleteSnapshot((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->restoreSnapshot((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { QVariantList _r = _t->diffResults();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 13: { QString _r = _t->generateDiffReport((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 14: { QString _r = _t->generateDiffReport();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 15: { bool _r = _t->exportDiffReport((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 16: { bool _r = _t->exportDiffReport((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 17: { QVariantList _r = _t->getFilteredResults((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 18: { QVariantMap _r = _t->getDiffStatistics();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConfigDiff::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigDiff::diffResultsChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConfigDiff::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigDiff::snapshotCreated)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ConfigDiff::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigDiff::snapshotRestored)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ConfigDiff::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigDiff::errorOccurred)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ConfigDiff *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantList*>(_v) = _t->diffResults(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->addedCount(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->removedCount(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->modifiedCount(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->unchangedCount(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ConfigDiff::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ConfigDiff.data,
    qt_meta_data_ConfigDiff,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConfigDiff::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigDiff::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigDiff.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ConfigDiff::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ConfigDiff::diffResultsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ConfigDiff::snapshotCreated(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ConfigDiff::snapshotRestored(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ConfigDiff::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
