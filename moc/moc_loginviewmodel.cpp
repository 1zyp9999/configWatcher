/****************************************************************************
** Meta object code from reading C++ file 'loginviewmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/viewmodel/loginviewmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loginviewmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LoginViewModel_t {
    QByteArrayData data[14];
    char stringdata0[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LoginViewModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LoginViewModel_t qt_meta_stringdata_LoginViewModel = {
    {
QT_MOC_LITERAL(0, 0, 14), // "LoginViewModel"
QT_MOC_LITERAL(1, 15, 15), // "usernameChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 15), // "passwordChanged"
QT_MOC_LITERAL(4, 48, 23), // "rememberPasswordChanged"
QT_MOC_LITERAL(5, 72, 19), // "errorMessageChanged"
QT_MOC_LITERAL(6, 92, 12), // "loginSuccess"
QT_MOC_LITERAL(7, 105, 10), // "checkLogin"
QT_MOC_LITERAL(8, 116, 15), // "loadCredentials"
QT_MOC_LITERAL(9, 132, 15), // "saveCredentials"
QT_MOC_LITERAL(10, 148, 8), // "username"
QT_MOC_LITERAL(11, 157, 8), // "password"
QT_MOC_LITERAL(12, 166, 16), // "rememberPassword"
QT_MOC_LITERAL(13, 183, 12) // "errorMessage"

    },
    "LoginViewModel\0usernameChanged\0\0"
    "passwordChanged\0rememberPasswordChanged\0"
    "errorMessageChanged\0loginSuccess\0"
    "checkLogin\0loadCredentials\0saveCredentials\0"
    "username\0password\0rememberPassword\0"
    "errorMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoginViewModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       4,   62, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,
       6,    0,   58,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    0,   59,    2, 0x02 /* Public */,
       8,    0,   60,    2, 0x02 /* Public */,
       9,    0,   61,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      10, QMetaType::QString, 0x00495103,
      11, QMetaType::QString, 0x00495103,
      12, QMetaType::Bool, 0x00495103,
      13, QMetaType::QString, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void LoginViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LoginViewModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->usernameChanged(); break;
        case 1: _t->passwordChanged(); break;
        case 2: _t->rememberPasswordChanged(); break;
        case 3: _t->errorMessageChanged(); break;
        case 4: _t->loginSuccess(); break;
        case 5: { bool _r = _t->checkLogin();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->loadCredentials(); break;
        case 7: _t->saveCredentials(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LoginViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginViewModel::usernameChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LoginViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginViewModel::passwordChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LoginViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginViewModel::rememberPasswordChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LoginViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginViewModel::errorMessageChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (LoginViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginViewModel::loginSuccess)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<LoginViewModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->username(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->password(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->rememberPassword(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->errorMessage(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<LoginViewModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setUsername(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setPassword(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setRememberPassword(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject LoginViewModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_LoginViewModel.data,
    qt_meta_data_LoginViewModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LoginViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LoginViewModel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LoginViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void LoginViewModel::usernameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LoginViewModel::passwordChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LoginViewModel::rememberPasswordChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void LoginViewModel::errorMessageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void LoginViewModel::loginSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
