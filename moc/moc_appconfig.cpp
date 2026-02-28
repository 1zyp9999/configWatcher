/****************************************************************************
** Meta object code from reading C++ file 'appconfig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/appconfig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appconfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AppConfig_t {
    QByteArrayData data[13];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AppConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AppConfig_t qt_meta_stringdata_AppConfig = {
    {
QT_MOC_LITERAL(0, 0, 9), // "AppConfig"
QT_MOC_LITERAL(1, 10, 16), // "configSearchPath"
QT_MOC_LITERAL(2, 27, 12), // "databasePath"
QT_MOC_LITERAL(3, 40, 7), // "logPath"
QT_MOC_LITERAL(4, 48, 15), // "defaultUsername"
QT_MOC_LITERAL(5, 64, 17), // "minPasswordLength"
QT_MOC_LITERAL(6, 82, 14), // "sessionTimeout"
QT_MOC_LITERAL(7, 97, 12), // "defaultWidth"
QT_MOC_LITERAL(8, 110, 13), // "defaultHeight"
QT_MOC_LITERAL(9, 124, 8), // "pageSize"
QT_MOC_LITERAL(10, 133, 16), // "maxSearchResults"
QT_MOC_LITERAL(11, 150, 14), // "maxImportFiles"
QT_MOC_LITERAL(12, 165, 13) // "searchTimeout"

    },
    "AppConfig\0configSearchPath\0databasePath\0"
    "logPath\0defaultUsername\0minPasswordLength\0"
    "sessionTimeout\0defaultWidth\0defaultHeight\0"
    "pageSize\0maxSearchResults\0maxImportFiles\0"
    "searchTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AppConfig[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
      12,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QString, 0x00095401,
       2, QMetaType::QString, 0x00095401,
       3, QMetaType::QString, 0x00095401,
       4, QMetaType::QString, 0x00095401,
       5, QMetaType::Int, 0x00095401,
       6, QMetaType::Int, 0x00095401,
       7, QMetaType::Int, 0x00095401,
       8, QMetaType::Int, 0x00095401,
       9, QMetaType::Int, 0x00095401,
      10, QMetaType::Int, 0x00095401,
      11, QMetaType::Int, 0x00095401,
      12, QMetaType::Int, 0x00095401,

       0        // eod
};

void AppConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AppConfig *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->configSearchPath(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->databasePath(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->logPath(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->defaultUsername(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->minPasswordLength(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->sessionTimeout(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->defaultWidth(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->defaultHeight(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->pageSize(); break;
        case 9: *reinterpret_cast< int*>(_v) = _t->maxSearchResults(); break;
        case 10: *reinterpret_cast< int*>(_v) = _t->maxImportFiles(); break;
        case 11: *reinterpret_cast< int*>(_v) = _t->searchTimeout(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject AppConfig::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AppConfig.data,
    qt_meta_data_AppConfig,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AppConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AppConfig.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AppConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 12;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
