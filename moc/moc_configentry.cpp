/****************************************************************************
** Meta object code from reading C++ file 'configentry.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/configentry.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configentry.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConfigEntry_t {
    QByteArrayData data[12];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigEntry_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigEntry_t qt_meta_stringdata_ConfigEntry = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ConfigEntry"
QT_MOC_LITERAL(1, 12, 10), // "keyChanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 12), // "valueChanged"
QT_MOC_LITERAL(4, 37, 15), // "filePathChanged"
QT_MOC_LITERAL(5, 53, 13), // "formatChanged"
QT_MOC_LITERAL(6, 67, 17), // "chineseKeyChanged"
QT_MOC_LITERAL(7, 85, 3), // "key"
QT_MOC_LITERAL(8, 89, 5), // "value"
QT_MOC_LITERAL(9, 95, 8), // "filePath"
QT_MOC_LITERAL(10, 104, 6), // "format"
QT_MOC_LITERAL(11, 111, 10) // "chineseKey"

    },
    "ConfigEntry\0keyChanged\0\0valueChanged\0"
    "filePathChanged\0formatChanged\0"
    "chineseKeyChanged\0key\0value\0filePath\0"
    "format\0chineseKey"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigEntry[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       5,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,
       6,    0,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::QString, 0x00495103,
       8, QMetaType::QString, 0x00495103,
       9, QMetaType::QString, 0x00495103,
      10, QMetaType::QString, 0x00495103,
      11, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,

       0        // eod
};

void ConfigEntry::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConfigEntry *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->keyChanged(); break;
        case 1: _t->valueChanged(); break;
        case 2: _t->filePathChanged(); break;
        case 3: _t->formatChanged(); break;
        case 4: _t->chineseKeyChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConfigEntry::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigEntry::keyChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConfigEntry::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigEntry::valueChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ConfigEntry::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigEntry::filePathChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ConfigEntry::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigEntry::formatChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ConfigEntry::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigEntry::chineseKeyChanged)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ConfigEntry *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->key(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->value(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->filePath(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->format(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->chineseKey(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ConfigEntry *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setKey(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setValue(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setFilePath(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setFormat(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setChineseKey(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject ConfigEntry::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ConfigEntry.data,
    qt_meta_data_ConfigEntry,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConfigEntry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigEntry::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigEntry.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ConfigEntry::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
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
void ConfigEntry::keyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ConfigEntry::valueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ConfigEntry::filePathChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ConfigEntry::formatChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ConfigEntry::chineseKeyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
