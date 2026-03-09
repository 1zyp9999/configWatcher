/****************************************************************************
** Meta object code from reading C++ file 'configvalidator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../include/configvalidator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configvalidator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConfigValidator_t {
    QByteArrayData data[50];
    char stringdata0[567];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigValidator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigValidator_t qt_meta_stringdata_ConfigValidator = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ConfigValidator"
QT_MOC_LITERAL(1, 16, 24), // "validationResultsChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 19), // "validationCompleted"
QT_MOC_LITERAL(4, 62, 6), // "errors"
QT_MOC_LITERAL(5, 69, 8), // "warnings"
QT_MOC_LITERAL(6, 78, 5), // "infos"
QT_MOC_LITERAL(7, 84, 12), // "schemaLoaded"
QT_MOC_LITERAL(8, 97, 10), // "schemaPath"
QT_MOC_LITERAL(9, 108, 13), // "errorOccurred"
QT_MOC_LITERAL(10, 122, 5), // "error"
QT_MOC_LITERAL(11, 128, 12), // "validateFile"
QT_MOC_LITERAL(12, 141, 8), // "filePath"
QT_MOC_LITERAL(13, 150, 14), // "validateConfig"
QT_MOC_LITERAL(14, 165, 6), // "config"
QT_MOC_LITERAL(15, 172, 11), // "validateKey"
QT_MOC_LITERAL(16, 184, 3), // "key"
QT_MOC_LITERAL(17, 188, 5), // "value"
QT_MOC_LITERAL(18, 194, 7), // "section"
QT_MOC_LITERAL(19, 202, 10), // "loadSchema"
QT_MOC_LITERAL(20, 213, 18), // "loadSchemaFromJson"
QT_MOC_LITERAL(21, 232, 11), // "jsonContent"
QT_MOC_LITERAL(22, 244, 9), // "getSchema"
QT_MOC_LITERAL(23, 254, 10), // "saveSchema"
QT_MOC_LITERAL(24, 265, 10), // "outputPath"
QT_MOC_LITERAL(25, 276, 7), // "addRule"
QT_MOC_LITERAL(26, 284, 4), // "type"
QT_MOC_LITERAL(27, 289, 11), // "constraints"
QT_MOC_LITERAL(28, 301, 10), // "removeRule"
QT_MOC_LITERAL(29, 312, 10), // "clearRules"
QT_MOC_LITERAL(30, 323, 8), // "getRules"
QT_MOC_LITERAL(31, 332, 14), // "checkConflicts"
QT_MOC_LITERAL(32, 347, 17), // "checkDependencies"
QT_MOC_LITERAL(33, 365, 11), // "checkRanges"
QT_MOC_LITERAL(34, 377, 12), // "checkFormats"
QT_MOC_LITERAL(35, 390, 24), // "generateValidationReport"
QT_MOC_LITERAL(36, 415, 6), // "format"
QT_MOC_LITERAL(37, 422, 22), // "exportValidationReport"
QT_MOC_LITERAL(38, 445, 12), // "suggestFixes"
QT_MOC_LITERAL(39, 458, 6), // "issues"
QT_MOC_LITERAL(40, 465, 7), // "autoFix"
QT_MOC_LITERAL(41, 473, 13), // "QVariantList&"
QT_MOC_LITERAL(42, 487, 17), // "validationResults"
QT_MOC_LITERAL(43, 505, 10), // "errorCount"
QT_MOC_LITERAL(44, 516, 12), // "warningCount"
QT_MOC_LITERAL(45, 529, 9), // "infoCount"
QT_MOC_LITERAL(46, 539, 8), // "Severity"
QT_MOC_LITERAL(47, 548, 5), // "Error"
QT_MOC_LITERAL(48, 554, 7), // "Warning"
QT_MOC_LITERAL(49, 562, 4) // "Info"

    },
    "ConfigValidator\0validationResultsChanged\0"
    "\0validationCompleted\0errors\0warnings\0"
    "infos\0schemaLoaded\0schemaPath\0"
    "errorOccurred\0error\0validateFile\0"
    "filePath\0validateConfig\0config\0"
    "validateKey\0key\0value\0section\0loadSchema\0"
    "loadSchemaFromJson\0jsonContent\0getSchema\0"
    "saveSchema\0outputPath\0addRule\0type\0"
    "constraints\0removeRule\0clearRules\0"
    "getRules\0checkConflicts\0checkDependencies\0"
    "checkRanges\0checkFormats\0"
    "generateValidationReport\0format\0"
    "exportValidationReport\0suggestFixes\0"
    "issues\0autoFix\0QVariantList&\0"
    "validationResults\0errorCount\0warningCount\0"
    "infoCount\0Severity\0Error\0Warning\0Info"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigValidator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       4,  240, // properties
       1,  256, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  149,    2, 0x06 /* Public */,
       3,    3,  150,    2, 0x06 /* Public */,
       7,    1,  157,    2, 0x06 /* Public */,
       9,    1,  160,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      11,    1,  163,    2, 0x02 /* Public */,
      13,    2,  166,    2, 0x02 /* Public */,
      13,    1,  171,    2, 0x22 /* Public | MethodCloned */,
      15,    3,  174,    2, 0x02 /* Public */,
      15,    2,  181,    2, 0x22 /* Public | MethodCloned */,
      19,    1,  186,    2, 0x02 /* Public */,
      20,    1,  189,    2, 0x02 /* Public */,
      22,    0,  192,    2, 0x02 /* Public */,
      23,    1,  193,    2, 0x02 /* Public */,
      25,    3,  196,    2, 0x02 /* Public */,
      28,    1,  203,    2, 0x02 /* Public */,
      29,    0,  206,    2, 0x02 /* Public */,
      30,    0,  207,    2, 0x02 /* Public */,
      31,    1,  208,    2, 0x02 /* Public */,
      32,    1,  211,    2, 0x02 /* Public */,
      33,    1,  214,    2, 0x02 /* Public */,
      34,    1,  217,    2, 0x02 /* Public */,
      35,    1,  220,    2, 0x02 /* Public */,
      35,    0,  223,    2, 0x22 /* Public | MethodCloned */,
      37,    2,  224,    2, 0x02 /* Public */,
      37,    1,  229,    2, 0x22 /* Public | MethodCloned */,
      38,    1,  232,    2, 0x02 /* Public */,
      40,    2,  235,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,

 // methods: parameters
    QMetaType::QVariantList, QMetaType::QString,   12,
    QMetaType::QVariantList, QMetaType::QVariantList, QMetaType::QString,   14,   12,
    QMetaType::QVariantList, QMetaType::QVariantList,   14,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::QString, QMetaType::QString,   16,   17,   18,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::QString,   16,   17,
    QMetaType::Bool, QMetaType::QString,    8,
    QMetaType::Bool, QMetaType::QString,   21,
    QMetaType::QVariantMap,
    QMetaType::Bool, QMetaType::QString,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QVariantMap,   16,   26,   27,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::QVariantList,
    QMetaType::QVariantList, QMetaType::QVariantList,   14,
    QMetaType::QVariantList, QMetaType::QVariantList,   14,
    QMetaType::QVariantList, QMetaType::QVariantList,   14,
    QMetaType::QVariantList, QMetaType::QVariantList,   14,
    QMetaType::QString, QMetaType::QString,   36,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   24,   36,
    QMetaType::Bool, QMetaType::QString,   24,
    QMetaType::QVariantList, QMetaType::QVariantList,   39,
    QMetaType::Bool, 0x80000000 | 41, QMetaType::QVariantList,   14,   39,

 // properties: name, type, flags
      42, QMetaType::QVariantList, 0x00495001,
      43, QMetaType::Int, 0x00495001,
      44, QMetaType::Int, 0x00495001,
      45, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,

 // enums: name, alias, flags, count, data
      46,   46, 0x0,    3,  261,

 // enum data: key, value
      47, uint(ConfigValidator::Error),
      48, uint(ConfigValidator::Warning),
      49, uint(ConfigValidator::Info),

       0        // eod
};

void ConfigValidator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConfigValidator *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->validationResultsChanged(); break;
        case 1: _t->validationCompleted((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->schemaLoaded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: { QVariantList _r = _t->validateFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 5: { QVariantList _r = _t->validateConfig((*reinterpret_cast< const QVariantList(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 6: { QVariantList _r = _t->validateConfig((*reinterpret_cast< const QVariantList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 7: { QVariantList _r = _t->validateKey((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 8: { QVariantList _r = _t->validateKey((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->loadSchema((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->loadSchemaFromJson((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { QVariantMap _r = _t->getSchema();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->saveSchema((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->addRule((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QVariantMap(*)>(_a[3]))); break;
        case 14: _t->removeRule((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->clearRules(); break;
        case 16: { QVariantList _r = _t->getRules();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 17: { QVariantList _r = _t->checkConflicts((*reinterpret_cast< const QVariantList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 18: { QVariantList _r = _t->checkDependencies((*reinterpret_cast< const QVariantList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 19: { QVariantList _r = _t->checkRanges((*reinterpret_cast< const QVariantList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 20: { QVariantList _r = _t->checkFormats((*reinterpret_cast< const QVariantList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 21: { QString _r = _t->generateValidationReport((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 22: { QString _r = _t->generateValidationReport();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 23: { bool _r = _t->exportValidationReport((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 24: { bool _r = _t->exportValidationReport((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 25: { QVariantList _r = _t->suggestFixes((*reinterpret_cast< const QVariantList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 26: { bool _r = _t->autoFix((*reinterpret_cast< QVariantList(*)>(_a[1])),(*reinterpret_cast< const QVariantList(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConfigValidator::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigValidator::validationResultsChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConfigValidator::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigValidator::validationCompleted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ConfigValidator::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigValidator::schemaLoaded)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ConfigValidator::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConfigValidator::errorOccurred)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ConfigValidator *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantList*>(_v) = _t->validationResults(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->errorCount(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->warningCount(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->infoCount(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ConfigValidator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ConfigValidator.data,
    qt_meta_data_ConfigValidator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConfigValidator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigValidator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigValidator.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ConfigValidator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 27)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 27;
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
void ConfigValidator::validationResultsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ConfigValidator::validationCompleted(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ConfigValidator::schemaLoaded(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ConfigValidator::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
