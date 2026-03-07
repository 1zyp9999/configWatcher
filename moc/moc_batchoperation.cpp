/****************************************************************************
** Meta object code from reading C++ file 'batchoperation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/batchoperation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'batchoperation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BatchOperation_t {
    QByteArrayData data[58];
    char stringdata0[725];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BatchOperation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BatchOperation_t qt_meta_stringdata_BatchOperation = {
    {
QT_MOC_LITERAL(0, 0, 14), // "BatchOperation"
QT_MOC_LITERAL(1, 15, 17), // "operationsChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 15), // "progressChanged"
QT_MOC_LITERAL(4, 50, 9), // "completed"
QT_MOC_LITERAL(5, 60, 5), // "total"
QT_MOC_LITERAL(6, 66, 14), // "runningChanged"
QT_MOC_LITERAL(7, 81, 7), // "running"
QT_MOC_LITERAL(8, 89, 23), // "currentOperationChanged"
QT_MOC_LITERAL(9, 113, 9), // "operation"
QT_MOC_LITERAL(10, 123, 18), // "operationCompleted"
QT_MOC_LITERAL(11, 142, 7), // "success"
QT_MOC_LITERAL(12, 150, 7), // "message"
QT_MOC_LITERAL(13, 158, 13), // "batchFinished"
QT_MOC_LITERAL(14, 172, 12), // "successCount"
QT_MOC_LITERAL(15, 185, 9), // "failCount"
QT_MOC_LITERAL(16, 195, 17), // "batchUpdateValues"
QT_MOC_LITERAL(17, 213, 7), // "entries"
QT_MOC_LITERAL(18, 221, 16), // "batchUpdateValue"
QT_MOC_LITERAL(19, 238, 3), // "key"
QT_MOC_LITERAL(20, 242, 8), // "newValue"
QT_MOC_LITERAL(21, 251, 9), // "filePaths"
QT_MOC_LITERAL(22, 261, 11), // "batchDelete"
QT_MOC_LITERAL(23, 273, 4), // "keys"
QT_MOC_LITERAL(24, 278, 8), // "filePath"
QT_MOC_LITERAL(25, 287, 15), // "batchAddSection"
QT_MOC_LITERAL(26, 303, 11), // "sectionName"
QT_MOC_LITERAL(27, 315, 11), // "batchImport"
QT_MOC_LITERAL(28, 327, 9), // "sourceDir"
QT_MOC_LITERAL(29, 337, 9), // "targetDir"
QT_MOC_LITERAL(30, 347, 7), // "filters"
QT_MOC_LITERAL(31, 355, 11), // "batchExport"
QT_MOC_LITERAL(32, 367, 6), // "format"
QT_MOC_LITERAL(33, 374, 11), // "exportToCsv"
QT_MOC_LITERAL(34, 386, 10), // "outputPath"
QT_MOC_LITERAL(35, 397, 12), // "exportToJson"
QT_MOC_LITERAL(36, 410, 13), // "importFromCsv"
QT_MOC_LITERAL(37, 424, 7), // "csvPath"
QT_MOC_LITERAL(38, 432, 14), // "targetFilePath"
QT_MOC_LITERAL(39, 447, 14), // "importFromJson"
QT_MOC_LITERAL(40, 462, 8), // "jsonPath"
QT_MOC_LITERAL(41, 471, 12), // "batchReplace"
QT_MOC_LITERAL(42, 484, 10), // "searchText"
QT_MOC_LITERAL(43, 495, 11), // "replaceText"
QT_MOC_LITERAL(44, 507, 18), // "batchApplyTemplate"
QT_MOC_LITERAL(45, 526, 16), // "templateFilePath"
QT_MOC_LITERAL(46, 543, 15), // "targetFilePaths"
QT_MOC_LITERAL(47, 559, 16), // "batchSetReadOnly"
QT_MOC_LITERAL(48, 576, 8), // "readOnly"
QT_MOC_LITERAL(49, 585, 15), // "getOperationLog"
QT_MOC_LITERAL(50, 601, 17), // "clearOperationLog"
QT_MOC_LITERAL(51, 619, 17), // "undoLastOperation"
QT_MOC_LITERAL(52, 637, 7), // "canUndo"
QT_MOC_LITERAL(53, 645, 15), // "totalOperations"
QT_MOC_LITERAL(54, 661, 19), // "completedOperations"
QT_MOC_LITERAL(55, 681, 16), // "failedOperations"
QT_MOC_LITERAL(56, 698, 9), // "isRunning"
QT_MOC_LITERAL(57, 708, 16) // "currentOperation"

    },
    "BatchOperation\0operationsChanged\0\0"
    "progressChanged\0completed\0total\0"
    "runningChanged\0running\0currentOperationChanged\0"
    "operation\0operationCompleted\0success\0"
    "message\0batchFinished\0successCount\0"
    "failCount\0batchUpdateValues\0entries\0"
    "batchUpdateValue\0key\0newValue\0filePaths\0"
    "batchDelete\0keys\0filePath\0batchAddSection\0"
    "sectionName\0batchImport\0sourceDir\0"
    "targetDir\0filters\0batchExport\0format\0"
    "exportToCsv\0outputPath\0exportToJson\0"
    "importFromCsv\0csvPath\0targetFilePath\0"
    "importFromJson\0jsonPath\0batchReplace\0"
    "searchText\0replaceText\0batchApplyTemplate\0"
    "templateFilePath\0targetFilePaths\0"
    "batchSetReadOnly\0readOnly\0getOperationLog\0"
    "clearOperationLog\0undoLastOperation\0"
    "canUndo\0totalOperations\0completedOperations\0"
    "failedOperations\0isRunning\0currentOperation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BatchOperation[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       5,  244, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  134,    2, 0x06 /* Public */,
       3,    2,  135,    2, 0x06 /* Public */,
       6,    1,  140,    2, 0x06 /* Public */,
       8,    1,  143,    2, 0x06 /* Public */,
      10,    3,  146,    2, 0x06 /* Public */,
      13,    2,  153,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      16,    1,  158,    2, 0x02 /* Public */,
      18,    3,  161,    2, 0x02 /* Public */,
      22,    2,  168,    2, 0x02 /* Public */,
      25,    3,  173,    2, 0x02 /* Public */,
      27,    3,  180,    2, 0x02 /* Public */,
      31,    3,  187,    2, 0x02 /* Public */,
      31,    2,  194,    2, 0x22 /* Public | MethodCloned */,
      33,    2,  199,    2, 0x02 /* Public */,
      35,    2,  204,    2, 0x02 /* Public */,
      36,    2,  209,    2, 0x02 /* Public */,
      39,    2,  214,    2, 0x02 /* Public */,
      41,    4,  219,    2, 0x02 /* Public */,
      44,    2,  228,    2, 0x02 /* Public */,
      47,    3,  233,    2, 0x02 /* Public */,
      49,    0,  240,    2, 0x02 /* Public */,
      50,    0,  241,    2, 0x02 /* Public */,
      51,    0,  242,    2, 0x02 /* Public */,
      52,    0,  243,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::QString,    9,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,

 // methods: parameters
    QMetaType::Bool, QMetaType::QVariantList,   17,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QStringList,   19,   20,   21,
    QMetaType::Bool, QMetaType::QStringList, QMetaType::QString,   23,   24,
    QMetaType::Bool, QMetaType::QString, QMetaType::QVariantList, QMetaType::QString,   26,   17,   24,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QStringList,   28,   29,   30,
    QMetaType::Bool, QMetaType::QStringList, QMetaType::QString, QMetaType::QString,   21,   29,   32,
    QMetaType::Bool, QMetaType::QStringList, QMetaType::QString,   21,   29,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   24,   34,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   24,   34,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   37,   38,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   40,   38,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QStringList, QMetaType::QString,   42,   43,   23,   24,
    QMetaType::Bool, QMetaType::QString, QMetaType::QStringList,   45,   46,
    QMetaType::Bool, QMetaType::QStringList, QMetaType::QString, QMetaType::Bool,   23,   24,   48,
    QMetaType::QVariantList,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,

 // properties: name, type, flags
      53, QMetaType::Int, 0x00495001,
      54, QMetaType::Int, 0x00495001,
      55, QMetaType::Int, 0x00495001,
      56, QMetaType::Bool, 0x00495001,
      57, QMetaType::QString, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       1,
       2,
       3,

       0        // eod
};

void BatchOperation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BatchOperation *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->operationsChanged(); break;
        case 1: _t->progressChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->runningChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->currentOperationChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->operationCompleted((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 5: _t->batchFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: { bool _r = _t->batchUpdateValues((*reinterpret_cast< const QVariantList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->batchUpdateValue((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->batchDelete((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->batchAddSection((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariantList(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->batchImport((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->batchExport((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->batchExport((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->exportToCsv((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: { bool _r = _t->exportToJson((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 15: { bool _r = _t->importFromCsv((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 16: { bool _r = _t->importFromJson((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 17: { bool _r = _t->batchReplace((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 18: { bool _r = _t->batchApplyTemplate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 19: { bool _r = _t->batchSetReadOnly((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 20: { QVariantList _r = _t->getOperationLog();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 21: _t->clearOperationLog(); break;
        case 22: { bool _r = _t->undoLastOperation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 23: { bool _r = _t->canUndo();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BatchOperation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BatchOperation::operationsChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BatchOperation::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BatchOperation::progressChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BatchOperation::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BatchOperation::runningChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BatchOperation::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BatchOperation::currentOperationChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (BatchOperation::*)(const QString & , bool , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BatchOperation::operationCompleted)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (BatchOperation::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BatchOperation::batchFinished)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<BatchOperation *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->totalOperations(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->completedOperations(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->failedOperations(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->isRunning(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->currentOperation(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject BatchOperation::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_BatchOperation.data,
    qt_meta_data_BatchOperation,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BatchOperation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BatchOperation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BatchOperation.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BatchOperation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 24;
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
void BatchOperation::operationsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BatchOperation::progressChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BatchOperation::runningChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BatchOperation::currentOperationChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void BatchOperation::operationCompleted(const QString & _t1, bool _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void BatchOperation::batchFinished(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
