/****************************************************************************
** Meta object code from reading C++ file 'searchviewmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../include/searchviewmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'searchviewmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SearchViewModel_t {
    QByteArrayData data[54];
    char stringdata0[781];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SearchViewModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SearchViewModel_t qt_meta_stringdata_SearchViewModel = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SearchViewModel"
QT_MOC_LITERAL(1, 16, 17), // "searchTextChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 20), // "searchResultsChanged"
QT_MOC_LITERAL(4, 56, 16), // "isLoadingChanged"
QT_MOC_LITERAL(5, 73, 19), // "loadProgressChanged"
QT_MOC_LITERAL(6, 93, 20), // "suggestClustersReady"
QT_MOC_LITERAL(7, 114, 8), // "clusters"
QT_MOC_LITERAL(8, 123, 15), // "keyCountChanged"
QT_MOC_LITERAL(9, 139, 16), // "aiEnabledChanged"
QT_MOC_LITERAL(10, 156, 7), // "enabled"
QT_MOC_LITERAL(11, 164, 15), // "aiIntentChanged"
QT_MOC_LITERAL(12, 180, 19), // "aiConfidenceChanged"
QT_MOC_LITERAL(13, 200, 20), // "aiSuggestionsChanged"
QT_MOC_LITERAL(14, 221, 20), // "aiExplanationChanged"
QT_MOC_LITERAL(15, 242, 19), // "updateSearchResults"
QT_MOC_LITERAL(16, 262, 22), // "deliverSuggestClusters"
QT_MOC_LITERAL(17, 285, 17), // "openFileRequested"
QT_MOC_LITERAL(18, 303, 8), // "filePath"
QT_MOC_LITERAL(19, 312, 15), // "selectDirectory"
QT_MOC_LITERAL(20, 328, 15), // "loadConfigFiles"
QT_MOC_LITERAL(21, 344, 9), // "filePaths"
QT_MOC_LITERAL(22, 354, 14), // "openConfigFile"
QT_MOC_LITERAL(23, 369, 14), // "pickConfigFile"
QT_MOC_LITERAL(24, 384, 14), // "readConfigFile"
QT_MOC_LITERAL(25, 399, 15), // "writeConfigFile"
QT_MOC_LITERAL(26, 415, 7), // "entries"
QT_MOC_LITERAL(27, 423, 18), // "initializeDatabase"
QT_MOC_LITERAL(28, 442, 6), // "dbPath"
QT_MOC_LITERAL(29, 449, 13), // "buildKeyIndex"
QT_MOC_LITERAL(30, 463, 11), // "suggestKeys"
QT_MOC_LITERAL(31, 475, 6), // "prefix"
QT_MOC_LITERAL(32, 482, 10), // "maxResults"
QT_MOC_LITERAL(33, 493, 15), // "suggestClusters"
QT_MOC_LITERAL(34, 509, 11), // "maxClusters"
QT_MOC_LITERAL(35, 521, 13), // "maxPerCluster"
QT_MOC_LITERAL(36, 535, 22), // "requestSuggestClusters"
QT_MOC_LITERAL(37, 558, 18), // "analyzeSearchQuery"
QT_MOC_LITERAL(38, 577, 5), // "query"
QT_MOC_LITERAL(39, 583, 17), // "applyAiSuggestion"
QT_MOC_LITERAL(40, 601, 10), // "suggestion"
QT_MOC_LITERAL(41, 612, 18), // "expandSearchWithAi"
QT_MOC_LITERAL(42, 631, 16), // "getAiExplanation"
QT_MOC_LITERAL(43, 648, 10), // "searchText"
QT_MOC_LITERAL(44, 659, 13), // "searchResults"
QT_MOC_LITERAL(45, 673, 15), // "QList<QObject*>"
QT_MOC_LITERAL(46, 689, 9), // "isLoading"
QT_MOC_LITERAL(47, 699, 12), // "loadProgress"
QT_MOC_LITERAL(48, 712, 8), // "keyCount"
QT_MOC_LITERAL(49, 721, 9), // "aiEnabled"
QT_MOC_LITERAL(50, 731, 8), // "aiIntent"
QT_MOC_LITERAL(51, 740, 12), // "aiConfidence"
QT_MOC_LITERAL(52, 753, 13), // "aiSuggestions"
QT_MOC_LITERAL(53, 767, 13) // "aiExplanation"

    },
    "SearchViewModel\0searchTextChanged\0\0"
    "searchResultsChanged\0isLoadingChanged\0"
    "loadProgressChanged\0suggestClustersReady\0"
    "clusters\0keyCountChanged\0aiEnabledChanged\0"
    "enabled\0aiIntentChanged\0aiConfidenceChanged\0"
    "aiSuggestionsChanged\0aiExplanationChanged\0"
    "updateSearchResults\0deliverSuggestClusters\0"
    "openFileRequested\0filePath\0selectDirectory\0"
    "loadConfigFiles\0filePaths\0openConfigFile\0"
    "pickConfigFile\0readConfigFile\0"
    "writeConfigFile\0entries\0initializeDatabase\0"
    "dbPath\0buildKeyIndex\0suggestKeys\0"
    "prefix\0maxResults\0suggestClusters\0"
    "maxClusters\0maxPerCluster\0"
    "requestSuggestClusters\0analyzeSearchQuery\0"
    "query\0applyAiSuggestion\0suggestion\0"
    "expandSearchWithAi\0getAiExplanation\0"
    "searchText\0searchResults\0QList<QObject*>\0"
    "isLoading\0loadProgress\0keyCount\0"
    "aiEnabled\0aiIntent\0aiConfidence\0"
    "aiSuggestions\0aiExplanation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchViewModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
      10,  276, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  184,    2, 0x06 /* Public */,
       3,    0,  185,    2, 0x06 /* Public */,
       4,    0,  186,    2, 0x06 /* Public */,
       5,    0,  187,    2, 0x06 /* Public */,
       6,    1,  188,    2, 0x06 /* Public */,
       8,    0,  191,    2, 0x06 /* Public */,
       9,    1,  192,    2, 0x06 /* Public */,
      11,    0,  195,    2, 0x06 /* Public */,
      12,    0,  196,    2, 0x06 /* Public */,
      13,    0,  197,    2, 0x06 /* Public */,
      14,    0,  198,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,  199,    2, 0x0a /* Public */,
      16,    1,  200,    2, 0x0a /* Public */,
      17,    1,  203,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      19,    0,  206,    2, 0x02 /* Public */,
      20,    1,  207,    2, 0x02 /* Public */,
      22,    1,  210,    2, 0x02 /* Public */,
      23,    0,  213,    2, 0x02 /* Public */,
      24,    1,  214,    2, 0x02 /* Public */,
      25,    2,  217,    2, 0x02 /* Public */,
      27,    1,  222,    2, 0x02 /* Public */,
      29,    0,  225,    2, 0x02 /* Public */,
      30,    2,  226,    2, 0x02 /* Public */,
      30,    1,  231,    2, 0x22 /* Public | MethodCloned */,
      33,    3,  234,    2, 0x02 /* Public */,
      33,    2,  241,    2, 0x22 /* Public | MethodCloned */,
      33,    1,  246,    2, 0x22 /* Public | MethodCloned */,
      36,    3,  249,    2, 0x02 /* Public */,
      36,    2,  256,    2, 0x22 /* Public | MethodCloned */,
      36,    1,  261,    2, 0x22 /* Public | MethodCloned */,
      37,    1,  264,    2, 0x02 /* Public */,
      39,    1,  267,    2, 0x02 /* Public */,
      41,    1,  270,    2, 0x02 /* Public */,
      42,    1,  273,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariantList,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariantList,    7,
    QMetaType::Void, QMetaType::QString,   18,

 // methods: parameters
    QMetaType::QString,
    QMetaType::Void, QMetaType::QStringList,   21,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::QString,
    QMetaType::QVariantList, QMetaType::QString,   18,
    QMetaType::Bool, QMetaType::QString, QMetaType::QVariantList,   18,   26,
    QMetaType::Bool, QMetaType::QString,   28,
    QMetaType::Void,
    QMetaType::QStringList, QMetaType::QString, QMetaType::Int,   31,   32,
    QMetaType::QStringList, QMetaType::QString,   31,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::Int, QMetaType::Int,   31,   34,   35,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::Int,   31,   34,
    QMetaType::QVariantList, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,   31,   34,   35,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   31,   34,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString,   38,
    QMetaType::Void, QMetaType::QString,   40,
    QMetaType::Void, QMetaType::QString,   38,
    QMetaType::QString, QMetaType::QString,   38,

 // properties: name, type, flags
      43, QMetaType::QString, 0x00495103,
      44, 0x80000000 | 45, 0x00495009,
      46, QMetaType::Bool, 0x00495001,
      47, QMetaType::Int, 0x00495001,
      48, QMetaType::Int, 0x00495001,
      49, QMetaType::Bool, 0x00495103,
      50, QMetaType::QString, 0x00495001,
      51, QMetaType::Double, 0x00495001,
      52, QMetaType::QVariantList, 0x00495001,
      53, QMetaType::QString, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       5,
       6,
       7,
       8,
       9,
      10,

       0        // eod
};

void SearchViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SearchViewModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->searchTextChanged(); break;
        case 1: _t->searchResultsChanged(); break;
        case 2: _t->isLoadingChanged(); break;
        case 3: _t->loadProgressChanged(); break;
        case 4: _t->suggestClustersReady((*reinterpret_cast< QVariantList(*)>(_a[1]))); break;
        case 5: _t->keyCountChanged(); break;
        case 6: _t->aiEnabledChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->aiIntentChanged(); break;
        case 8: _t->aiConfidenceChanged(); break;
        case 9: _t->aiSuggestionsChanged(); break;
        case 10: _t->aiExplanationChanged(); break;
        case 11: _t->updateSearchResults(); break;
        case 12: _t->deliverSuggestClusters((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 13: _t->openFileRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: { QString _r = _t->selectDirectory();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->loadConfigFiles((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 16: _t->openConfigFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: { QString _r = _t->pickConfigFile();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 18: { QVariantList _r = _t->readConfigFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 19: { bool _r = _t->writeConfigFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariantList(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 20: { bool _r = _t->initializeDatabase((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 21: _t->buildKeyIndex(); break;
        case 22: { QStringList _r = _t->suggestKeys((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 23: { QStringList _r = _t->suggestKeys((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 24: { QVariantList _r = _t->suggestClusters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 25: { QVariantList _r = _t->suggestClusters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 26: { QVariantList _r = _t->suggestClusters((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 27: _t->requestSuggestClusters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 28: _t->requestSuggestClusters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 29: _t->requestSuggestClusters((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 30: _t->analyzeSearchQuery((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 31: _t->applyAiSuggestion((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 32: _t->expandSearchWithAi((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 33: { QString _r = _t->getAiExplanation((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SearchViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::searchTextChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SearchViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::searchResultsChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SearchViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::isLoadingChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SearchViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::loadProgressChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SearchViewModel::*)(QVariantList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::suggestClustersReady)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SearchViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::keyCountChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SearchViewModel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::aiEnabledChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SearchViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::aiIntentChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SearchViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::aiConfidenceChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SearchViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::aiSuggestionsChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SearchViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::aiExplanationChanged)) {
                *result = 10;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QObject*> >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SearchViewModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->searchText(); break;
        case 1: *reinterpret_cast< QList<QObject*>*>(_v) = _t->searchResults(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isLoading(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->loadProgress(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->keyCount(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->aiEnabled(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->aiIntent(); break;
        case 7: *reinterpret_cast< double*>(_v) = _t->aiConfidence(); break;
        case 8: *reinterpret_cast< QVariantList*>(_v) = _t->aiSuggestions(); break;
        case 9: *reinterpret_cast< QString*>(_v) = _t->aiExplanation(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<SearchViewModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSearchText(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setAiEnabled(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject SearchViewModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SearchViewModel.data,
    qt_meta_data_SearchViewModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SearchViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SearchViewModel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SearchViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 10;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void SearchViewModel::searchTextChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SearchViewModel::searchResultsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SearchViewModel::isLoadingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SearchViewModel::loadProgressChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SearchViewModel::suggestClustersReady(QVariantList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SearchViewModel::keyCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void SearchViewModel::aiEnabledChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SearchViewModel::aiIntentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void SearchViewModel::aiConfidenceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void SearchViewModel::aiSuggestionsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void SearchViewModel::aiExplanationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
