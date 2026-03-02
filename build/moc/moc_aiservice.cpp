/****************************************************************************
** Meta object code from reading C++ file 'aiservice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../include/aiservice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'aiservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AiService_t {
    QByteArrayData data[24];
    char stringdata0[303];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AiService_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AiService_t qt_meta_stringdata_AiService = {
    {
QT_MOC_LITERAL(0, 0, 9), // "AiService"
QT_MOC_LITERAL(1, 10, 14), // "enabledChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "enabled"
QT_MOC_LITERAL(4, 34, 13), // "analyzeIntent"
QT_MOC_LITERAL(5, 48, 5), // "query"
QT_MOC_LITERAL(6, 54, 19), // "getIntentConfidence"
QT_MOC_LITERAL(7, 74, 15), // "extractEntities"
QT_MOC_LITERAL(8, 90, 14), // "expandKeywords"
QT_MOC_LITERAL(9, 105, 10), // "maxResults"
QT_MOC_LITERAL(10, 116, 11), // "getSynonyms"
QT_MOC_LITERAL(11, 128, 4), // "word"
QT_MOC_LITERAL(12, 133, 15), // "getRelatedWords"
QT_MOC_LITERAL(13, 149, 19), // "generateSuggestions"
QT_MOC_LITERAL(14, 169, 7), // "context"
QT_MOC_LITERAL(15, 177, 14), // "maxSuggestions"
QT_MOC_LITERAL(16, 192, 12), // "explainQuery"
QT_MOC_LITERAL(17, 205, 15), // "needsFuzzyMatch"
QT_MOC_LITERAL(18, 221, 20), // "loadDomainDictionary"
QT_MOC_LITERAL(19, 242, 5), // "terms"
QT_MOC_LITERAL(20, 248, 15), // "clearDictionary"
QT_MOC_LITERAL(21, 264, 17), // "getDictionarySize"
QT_MOC_LITERAL(22, 282, 10), // "setEnabled"
QT_MOC_LITERAL(23, 293, 9) // "isEnabled"

    },
    "AiService\0enabledChanged\0\0enabled\0"
    "analyzeIntent\0query\0getIntentConfidence\0"
    "extractEntities\0expandKeywords\0"
    "maxResults\0getSynonyms\0word\0getRelatedWords\0"
    "generateSuggestions\0context\0maxSuggestions\0"
    "explainQuery\0needsFuzzyMatch\0"
    "loadDomainDictionary\0terms\0clearDictionary\0"
    "getDictionarySize\0setEnabled\0isEnabled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AiService[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       4,    1,  107,    2, 0x02 /* Public */,
       6,    1,  110,    2, 0x02 /* Public */,
       7,    1,  113,    2, 0x02 /* Public */,
       8,    2,  116,    2, 0x02 /* Public */,
       8,    1,  121,    2, 0x22 /* Public | MethodCloned */,
      10,    1,  124,    2, 0x02 /* Public */,
      12,    1,  127,    2, 0x02 /* Public */,
      13,    3,  130,    2, 0x02 /* Public */,
      13,    2,  137,    2, 0x22 /* Public | MethodCloned */,
      13,    1,  142,    2, 0x22 /* Public | MethodCloned */,
      16,    1,  145,    2, 0x02 /* Public */,
      17,    1,  148,    2, 0x02 /* Public */,
      18,    1,  151,    2, 0x02 /* Public */,
      20,    0,  154,    2, 0x02 /* Public */,
      21,    0,  155,    2, 0x02 /* Public */,
      22,    1,  156,    2, 0x02 /* Public */,
      23,    0,  159,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // methods: parameters
    QMetaType::QString, QMetaType::QString,    5,
    QMetaType::Double, QMetaType::QString,    5,
    QMetaType::QVariantList, QMetaType::QString,    5,
    QMetaType::QStringList, QMetaType::QString, QMetaType::Int,    5,    9,
    QMetaType::QStringList, QMetaType::QString,    5,
    QMetaType::QStringList, QMetaType::QString,   11,
    QMetaType::QStringList, QMetaType::QString,   11,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::QString, QMetaType::Int,    5,   14,   15,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::QString,    5,   14,
    QMetaType::QVariantList, QMetaType::QString,    5,
    QMetaType::QString, QMetaType::QString,    5,
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QVariantMap,   19,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Bool,

       0        // eod
};

void AiService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AiService *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->enabledChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: { QString _r = _t->analyzeIntent((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 2: { double _r = _t->getIntentConfidence((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 3: { QVariantList _r = _t->extractEntities((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 4: { QStringList _r = _t->expandKeywords((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 5: { QStringList _r = _t->expandKeywords((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 6: { QStringList _r = _t->getSynonyms((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 7: { QStringList _r = _t->getRelatedWords((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 8: { QVariantList _r = _t->generateSuggestions((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 9: { QVariantList _r = _t->generateSuggestions((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 10: { QVariantList _r = _t->generateSuggestions((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 11: { QString _r = _t->explainQuery((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->needsFuzzyMatch((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->loadDomainDictionary((*reinterpret_cast< const QVariantMap(*)>(_a[1]))); break;
        case 14: _t->clearDictionary(); break;
        case 15: { int _r = _t->getDictionarySize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->setEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: { bool _r = _t->isEnabled();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AiService::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiService::enabledChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AiService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AiService.data,
    qt_meta_data_AiService,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AiService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AiService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AiService.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AiService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void AiService::enabledChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
