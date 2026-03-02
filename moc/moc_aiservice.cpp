/****************************************************************************
** Meta object code from reading C++ file 'aiservice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/aiservice.h"
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
    QByteArrayData data[47];
    char stringdata0[659];
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
QT_MOC_LITERAL(4, 34, 21), // "userDictionaryChanged"
QT_MOC_LITERAL(5, 56, 20), // "searchHistoryChanged"
QT_MOC_LITERAL(6, 77, 13), // "analyzeIntent"
QT_MOC_LITERAL(7, 91, 5), // "query"
QT_MOC_LITERAL(8, 97, 19), // "getIntentConfidence"
QT_MOC_LITERAL(9, 117, 15), // "extractEntities"
QT_MOC_LITERAL(10, 133, 14), // "expandKeywords"
QT_MOC_LITERAL(11, 148, 10), // "maxResults"
QT_MOC_LITERAL(12, 159, 11), // "getSynonyms"
QT_MOC_LITERAL(13, 171, 4), // "word"
QT_MOC_LITERAL(14, 176, 15), // "getRelatedWords"
QT_MOC_LITERAL(15, 192, 19), // "generateSuggestions"
QT_MOC_LITERAL(16, 212, 7), // "context"
QT_MOC_LITERAL(17, 220, 14), // "maxSuggestions"
QT_MOC_LITERAL(18, 235, 12), // "explainQuery"
QT_MOC_LITERAL(19, 248, 15), // "needsFuzzyMatch"
QT_MOC_LITERAL(20, 264, 20), // "loadDomainDictionary"
QT_MOC_LITERAL(21, 285, 5), // "terms"
QT_MOC_LITERAL(22, 291, 15), // "clearDictionary"
QT_MOC_LITERAL(23, 307, 17), // "getDictionarySize"
QT_MOC_LITERAL(24, 325, 11), // "addUserTerm"
QT_MOC_LITERAL(25, 337, 3), // "key"
QT_MOC_LITERAL(26, 341, 7), // "chinese"
QT_MOC_LITERAL(27, 349, 8), // "synonyms"
QT_MOC_LITERAL(28, 358, 14), // "removeUserTerm"
QT_MOC_LITERAL(29, 373, 12), // "getUserTerms"
QT_MOC_LITERAL(30, 386, 18), // "saveUserDictionary"
QT_MOC_LITERAL(31, 405, 18), // "loadUserDictionary"
QT_MOC_LITERAL(32, 424, 21), // "getUserDictionaryPath"
QT_MOC_LITERAL(33, 446, 19), // "recordSearchHistory"
QT_MOC_LITERAL(34, 466, 11), // "resultCount"
QT_MOC_LITERAL(35, 478, 8), // "selected"
QT_MOC_LITERAL(36, 487, 16), // "getSearchHistory"
QT_MOC_LITERAL(37, 504, 5), // "limit"
QT_MOC_LITERAL(38, 510, 18), // "clearSearchHistory"
QT_MOC_LITERAL(39, 529, 14), // "getHotSearches"
QT_MOC_LITERAL(40, 544, 17), // "saveSearchHistory"
QT_MOC_LITERAL(41, 562, 17), // "loadSearchHistory"
QT_MOC_LITERAL(42, 580, 20), // "getSearchHistoryPath"
QT_MOC_LITERAL(43, 601, 10), // "setEnabled"
QT_MOC_LITERAL(44, 612, 9), // "isEnabled"
QT_MOC_LITERAL(45, 622, 18), // "setLearningEnabled"
QT_MOC_LITERAL(46, 641, 17) // "isLearningEnabled"

    },
    "AiService\0enabledChanged\0\0enabled\0"
    "userDictionaryChanged\0searchHistoryChanged\0"
    "analyzeIntent\0query\0getIntentConfidence\0"
    "extractEntities\0expandKeywords\0"
    "maxResults\0getSynonyms\0word\0getRelatedWords\0"
    "generateSuggestions\0context\0maxSuggestions\0"
    "explainQuery\0needsFuzzyMatch\0"
    "loadDomainDictionary\0terms\0clearDictionary\0"
    "getDictionarySize\0addUserTerm\0key\0"
    "chinese\0synonyms\0removeUserTerm\0"
    "getUserTerms\0saveUserDictionary\0"
    "loadUserDictionary\0getUserDictionaryPath\0"
    "recordSearchHistory\0resultCount\0"
    "selected\0getSearchHistory\0limit\0"
    "clearSearchHistory\0getHotSearches\0"
    "saveSearchHistory\0loadSearchHistory\0"
    "getSearchHistoryPath\0setEnabled\0"
    "isEnabled\0setLearningEnabled\0"
    "isLearningEnabled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AiService[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  214,    2, 0x06 /* Public */,
       4,    0,  217,    2, 0x06 /* Public */,
       5,    0,  218,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       6,    1,  219,    2, 0x02 /* Public */,
       8,    1,  222,    2, 0x02 /* Public */,
       9,    1,  225,    2, 0x02 /* Public */,
      10,    2,  228,    2, 0x02 /* Public */,
      10,    1,  233,    2, 0x22 /* Public | MethodCloned */,
      12,    1,  236,    2, 0x02 /* Public */,
      14,    1,  239,    2, 0x02 /* Public */,
      15,    3,  242,    2, 0x02 /* Public */,
      15,    2,  249,    2, 0x22 /* Public | MethodCloned */,
      15,    1,  254,    2, 0x22 /* Public | MethodCloned */,
      18,    1,  257,    2, 0x02 /* Public */,
      19,    1,  260,    2, 0x02 /* Public */,
      20,    1,  263,    2, 0x02 /* Public */,
      22,    0,  266,    2, 0x02 /* Public */,
      23,    0,  267,    2, 0x02 /* Public */,
      24,    3,  268,    2, 0x02 /* Public */,
      24,    2,  275,    2, 0x22 /* Public | MethodCloned */,
      28,    1,  280,    2, 0x02 /* Public */,
      29,    0,  283,    2, 0x02 /* Public */,
      30,    0,  284,    2, 0x02 /* Public */,
      31,    0,  285,    2, 0x02 /* Public */,
      32,    0,  286,    2, 0x02 /* Public */,
      33,    3,  287,    2, 0x02 /* Public */,
      33,    2,  294,    2, 0x22 /* Public | MethodCloned */,
      33,    1,  299,    2, 0x22 /* Public | MethodCloned */,
      36,    1,  302,    2, 0x02 /* Public */,
      36,    0,  305,    2, 0x22 /* Public | MethodCloned */,
      38,    0,  306,    2, 0x02 /* Public */,
      39,    1,  307,    2, 0x02 /* Public */,
      39,    0,  310,    2, 0x22 /* Public | MethodCloned */,
      40,    0,  311,    2, 0x02 /* Public */,
      41,    0,  312,    2, 0x02 /* Public */,
      42,    0,  313,    2, 0x02 /* Public */,
      43,    1,  314,    2, 0x02 /* Public */,
      44,    0,  317,    2, 0x02 /* Public */,
      45,    1,  318,    2, 0x02 /* Public */,
      46,    0,  321,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::QString, QMetaType::QString,    7,
    QMetaType::Double, QMetaType::QString,    7,
    QMetaType::QVariantList, QMetaType::QString,    7,
    QMetaType::QStringList, QMetaType::QString, QMetaType::Int,    7,   11,
    QMetaType::QStringList, QMetaType::QString,    7,
    QMetaType::QStringList, QMetaType::QString,   13,
    QMetaType::QStringList, QMetaType::QString,   13,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::QString, QMetaType::Int,    7,   16,   17,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::QString,    7,   16,
    QMetaType::QVariantList, QMetaType::QString,    7,
    QMetaType::QString, QMetaType::QString,    7,
    QMetaType::Bool, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QVariantMap,   21,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QStringList,   25,   26,   27,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   25,   26,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::QVariantList,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Bool,    7,   34,   35,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    7,   34,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::QVariantList, QMetaType::Int,   37,
    QMetaType::QVariantList,
    QMetaType::Void,
    QMetaType::QVariantList, QMetaType::Int,   37,
    QMetaType::QVariantList,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Bool,
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
        case 1: _t->userDictionaryChanged(); break;
        case 2: _t->searchHistoryChanged(); break;
        case 3: { QString _r = _t->analyzeIntent((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: { double _r = _t->getIntentConfidence((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 5: { QVariantList _r = _t->extractEntities((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 6: { QStringList _r = _t->expandKeywords((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 7: { QStringList _r = _t->expandKeywords((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 8: { QStringList _r = _t->getSynonyms((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 9: { QStringList _r = _t->getRelatedWords((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 10: { QVariantList _r = _t->generateSuggestions((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 11: { QVariantList _r = _t->generateSuggestions((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 12: { QVariantList _r = _t->generateSuggestions((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 13: { QString _r = _t->explainQuery((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 14: { bool _r = _t->needsFuzzyMatch((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->loadDomainDictionary((*reinterpret_cast< const QVariantMap(*)>(_a[1]))); break;
        case 16: _t->clearDictionary(); break;
        case 17: { int _r = _t->getDictionarySize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 18: _t->addUserTerm((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3]))); break;
        case 19: _t->addUserTerm((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 20: _t->removeUserTerm((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 21: { QVariantList _r = _t->getUserTerms();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 22: { bool _r = _t->saveUserDictionary();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 23: { bool _r = _t->loadUserDictionary();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 24: { QString _r = _t->getUserDictionaryPath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 25: _t->recordSearchHistory((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 26: _t->recordSearchHistory((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 27: _t->recordSearchHistory((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 28: { QVariantList _r = _t->getSearchHistory((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 29: { QVariantList _r = _t->getSearchHistory();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 30: _t->clearSearchHistory(); break;
        case 31: { QVariantList _r = _t->getHotSearches((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 32: { QVariantList _r = _t->getHotSearches();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 33: { bool _r = _t->saveSearchHistory();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 34: { bool _r = _t->loadSearchHistory();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 35: { QString _r = _t->getSearchHistoryPath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 36: _t->setEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: { bool _r = _t->isEnabled();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 38: _t->setLearningEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: { bool _r = _t->isLearningEnabled();
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
        {
            using _t = void (AiService::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiService::userDictionaryChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AiService::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiService::searchHistoryChanged)) {
                *result = 2;
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
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 40;
    }
    return _id;
}

// SIGNAL 0
void AiService::enabledChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AiService::userDictionaryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AiService::searchHistoryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
