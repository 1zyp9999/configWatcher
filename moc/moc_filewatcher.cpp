/****************************************************************************
** Meta object code from reading C++ file 'filewatcher.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/filewatcher.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filewatcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FileWatcher_t {
    QByteArrayData data[29];
    char stringdata0[363];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileWatcher_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileWatcher_t qt_meta_stringdata_FileWatcher = {
    {
QT_MOC_LITERAL(0, 0, 11), // "FileWatcher"
QT_MOC_LITERAL(1, 12, 11), // "fileChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "filePath"
QT_MOC_LITERAL(4, 34, 10), // "changeType"
QT_MOC_LITERAL(5, 45, 16), // "directoryChanged"
QT_MOC_LITERAL(6, 62, 7), // "dirPath"
QT_MOC_LITERAL(7, 70, 15), // "watchingChanged"
QT_MOC_LITERAL(8, 86, 8), // "watching"
QT_MOC_LITERAL(9, 95, 19), // "watchedFilesChanged"
QT_MOC_LITERAL(10, 115, 13), // "errorOccurred"
QT_MOC_LITERAL(11, 129, 5), // "error"
QT_MOC_LITERAL(12, 135, 13), // "onFileChanged"
QT_MOC_LITERAL(13, 149, 4), // "path"
QT_MOC_LITERAL(14, 154, 18), // "onDirectoryChanged"
QT_MOC_LITERAL(15, 173, 15), // "onDebounceTimer"
QT_MOC_LITERAL(16, 189, 8), // "addWatch"
QT_MOC_LITERAL(17, 198, 17), // "addWatchDirectory"
QT_MOC_LITERAL(18, 216, 7), // "filters"
QT_MOC_LITERAL(19, 224, 11), // "removeWatch"
QT_MOC_LITERAL(20, 236, 12), // "clearWatches"
QT_MOC_LITERAL(21, 249, 13), // "pauseWatching"
QT_MOC_LITERAL(22, 263, 14), // "resumeWatching"
QT_MOC_LITERAL(23, 278, 15), // "getChangedFiles"
QT_MOC_LITERAL(24, 294, 17), // "clearChangedFiles"
QT_MOC_LITERAL(25, 312, 14), // "getFileHistory"
QT_MOC_LITERAL(26, 327, 5), // "limit"
QT_MOC_LITERAL(27, 333, 16), // "watchedFileCount"
QT_MOC_LITERAL(28, 350, 12) // "watchedFiles"

    },
    "FileWatcher\0fileChanged\0\0filePath\0"
    "changeType\0directoryChanged\0dirPath\0"
    "watchingChanged\0watching\0watchedFilesChanged\0"
    "errorOccurred\0error\0onFileChanged\0"
    "path\0onDirectoryChanged\0onDebounceTimer\0"
    "addWatch\0addWatchDirectory\0filters\0"
    "removeWatch\0clearWatches\0pauseWatching\0"
    "resumeWatching\0getChangedFiles\0"
    "clearChangedFiles\0getFileHistory\0limit\0"
    "watchedFileCount\0watchedFiles"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileWatcher[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       3,  158, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  109,    2, 0x06 /* Public */,
       5,    1,  114,    2, 0x06 /* Public */,
       7,    1,  117,    2, 0x06 /* Public */,
       9,    0,  120,    2, 0x06 /* Public */,
      10,    1,  121,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,  124,    2, 0x08 /* Private */,
      14,    1,  127,    2, 0x08 /* Private */,
      15,    0,  130,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      16,    1,  131,    2, 0x02 /* Public */,
      17,    2,  134,    2, 0x02 /* Public */,
      17,    1,  139,    2, 0x22 /* Public | MethodCloned */,
      19,    1,  142,    2, 0x02 /* Public */,
      20,    0,  145,    2, 0x02 /* Public */,
      21,    0,  146,    2, 0x02 /* Public */,
      22,    0,  147,    2, 0x02 /* Public */,
      23,    0,  148,    2, 0x02 /* Public */,
      24,    0,  149,    2, 0x02 /* Public */,
      25,    2,  150,    2, 0x02 /* Public */,
      25,    1,  155,    2, 0x22 /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool, QMetaType::QString,    3,
    QMetaType::Bool, QMetaType::QString, QMetaType::QStringList,    6,   18,
    QMetaType::Bool, QMetaType::QString,    6,
    QMetaType::Bool, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QVariantList,
    QMetaType::Void,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::Int,    3,   26,
    QMetaType::QVariantList, QMetaType::QString,    3,

 // properties: name, type, flags
       8, QMetaType::Bool, 0x00495001,
      27, QMetaType::Int, 0x00495001,
      28, QMetaType::QStringList, 0x00495001,

 // properties: notify_signal_id
       2,
       3,
       3,

       0        // eod
};

void FileWatcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FileWatcher *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fileChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->directoryChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->watchingChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->watchedFilesChanged(); break;
        case 4: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onFileChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->onDirectoryChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->onDebounceTimer(); break;
        case 8: { bool _r = _t->addWatch((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->addWatchDirectory((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->addWatchDirectory((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->removeWatch((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->clearWatches(); break;
        case 13: _t->pauseWatching(); break;
        case 14: _t->resumeWatching(); break;
        case 15: { QVariantList _r = _t->getChangedFiles();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->clearChangedFiles(); break;
        case 17: { QVariantList _r = _t->getFileHistory((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 18: { QVariantList _r = _t->getFileHistory((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FileWatcher::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileWatcher::fileChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FileWatcher::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileWatcher::directoryChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FileWatcher::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileWatcher::watchingChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FileWatcher::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileWatcher::watchedFilesChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FileWatcher::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileWatcher::errorOccurred)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FileWatcher *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isWatching(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->watchedFileCount(); break;
        case 2: *reinterpret_cast< QStringList*>(_v) = _t->watchedFiles(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject FileWatcher::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_FileWatcher.data,
    qt_meta_data_FileWatcher,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FileWatcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileWatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FileWatcher.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FileWatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FileWatcher::fileChanged(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FileWatcher::directoryChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FileWatcher::watchingChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FileWatcher::watchedFilesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void FileWatcher::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
