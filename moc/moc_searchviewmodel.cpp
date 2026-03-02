/****************************************************************************
** Meta object code from reading C++ file 'searchviewmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/searchviewmodel.h"
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
    QByteArrayData data[73];
    char stringdata0[1042];
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
QT_MOC_LITERAL(15, 242, 22), // "learningEnabledChanged"
QT_MOC_LITERAL(16, 265, 19), // "formatFilterChanged"
QT_MOC_LITERAL(17, 285, 19), // "updateSearchResults"
QT_MOC_LITERAL(18, 305, 22), // "deliverSuggestClusters"
QT_MOC_LITERAL(19, 328, 17), // "openFileRequested"
QT_MOC_LITERAL(20, 346, 8), // "filePath"
QT_MOC_LITERAL(21, 355, 15), // "selectDirectory"
QT_MOC_LITERAL(22, 371, 15), // "loadConfigFiles"
QT_MOC_LITERAL(23, 387, 9), // "filePaths"
QT_MOC_LITERAL(24, 397, 14), // "openConfigFile"
QT_MOC_LITERAL(25, 412, 14), // "pickConfigFile"
QT_MOC_LITERAL(26, 427, 14), // "readConfigFile"
QT_MOC_LITERAL(27, 442, 15), // "writeConfigFile"
QT_MOC_LITERAL(28, 458, 7), // "entries"
QT_MOC_LITERAL(29, 466, 18), // "initializeDatabase"
QT_MOC_LITERAL(30, 485, 6), // "dbPath"
QT_MOC_LITERAL(31, 492, 13), // "buildKeyIndex"
QT_MOC_LITERAL(32, 506, 11), // "suggestKeys"
QT_MOC_LITERAL(33, 518, 6), // "prefix"
QT_MOC_LITERAL(34, 525, 10), // "maxResults"
QT_MOC_LITERAL(35, 536, 15), // "suggestClusters"
QT_MOC_LITERAL(36, 552, 11), // "maxClusters"
QT_MOC_LITERAL(37, 564, 13), // "maxPerCluster"
QT_MOC_LITERAL(38, 578, 22), // "requestSuggestClusters"
QT_MOC_LITERAL(39, 601, 18), // "analyzeSearchQuery"
QT_MOC_LITERAL(40, 620, 5), // "query"
QT_MOC_LITERAL(41, 626, 17), // "applyAiSuggestion"
QT_MOC_LITERAL(42, 644, 10), // "suggestion"
QT_MOC_LITERAL(43, 655, 18), // "expandSearchWithAi"
QT_MOC_LITERAL(44, 674, 16), // "getAiExplanation"
QT_MOC_LITERAL(45, 691, 11), // "addUserTerm"
QT_MOC_LITERAL(46, 703, 3), // "key"
QT_MOC_LITERAL(47, 707, 7), // "chinese"
QT_MOC_LITERAL(48, 715, 8), // "synonyms"
QT_MOC_LITERAL(49, 724, 14), // "removeUserTerm"
QT_MOC_LITERAL(50, 739, 12), // "getUserTerms"
QT_MOC_LITERAL(51, 752, 12), // "recordSearch"
QT_MOC_LITERAL(52, 765, 11), // "resultCount"
QT_MOC_LITERAL(53, 777, 8), // "selected"
QT_MOC_LITERAL(54, 786, 16), // "getSearchHistory"
QT_MOC_LITERAL(55, 803, 5), // "limit"
QT_MOC_LITERAL(56, 809, 18), // "clearSearchHistory"
QT_MOC_LITERAL(57, 828, 14), // "getHotSearches"
QT_MOC_LITERAL(58, 843, 18), // "setLearningEnabled"
QT_MOC_LITERAL(59, 862, 17), // "isLearningEnabled"
QT_MOC_LITERAL(60, 880, 10), // "searchText"
QT_MOC_LITERAL(61, 891, 13), // "searchResults"
QT_MOC_LITERAL(62, 905, 15), // "QList<QObject*>"
QT_MOC_LITERAL(63, 921, 9), // "isLoading"
QT_MOC_LITERAL(64, 931, 12), // "loadProgress"
QT_MOC_LITERAL(65, 944, 8), // "keyCount"
QT_MOC_LITERAL(66, 953, 9), // "aiEnabled"
QT_MOC_LITERAL(67, 963, 8), // "aiIntent"
QT_MOC_LITERAL(68, 972, 12), // "aiConfidence"
QT_MOC_LITERAL(69, 985, 13), // "aiSuggestions"
QT_MOC_LITERAL(70, 999, 13), // "aiExplanation"
QT_MOC_LITERAL(71, 1013, 15), // "learningEnabled"
QT_MOC_LITERAL(72, 1029, 12) // "formatFilter"

    },
    "SearchViewModel\0searchTextChanged\0\0"
    "searchResultsChanged\0isLoadingChanged\0"
    "loadProgressChanged\0suggestClustersReady\0"
    "clusters\0keyCountChanged\0aiEnabledChanged\0"
    "enabled\0aiIntentChanged\0aiConfidenceChanged\0"
    "aiSuggestionsChanged\0aiExplanationChanged\0"
    "learningEnabledChanged\0formatFilterChanged\0"
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
    "addUserTerm\0key\0chinese\0synonyms\0"
    "removeUserTerm\0getUserTerms\0recordSearch\0"
    "resultCount\0selected\0getSearchHistory\0"
    "limit\0clearSearchHistory\0getHotSearches\0"
    "setLearningEnabled\0isLearningEnabled\0"
    "searchText\0searchResults\0QList<QObject*>\0"
    "isLoading\0loadProgress\0keyCount\0"
    "aiEnabled\0aiIntent\0aiConfidence\0"
    "aiSuggestions\0aiExplanation\0learningEnabled\0"
    "formatFilter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchViewModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      45,   14, // methods
      12,  364, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  239,    2, 0x06 /* Public */,
       3,    0,  240,    2, 0x06 /* Public */,
       4,    0,  241,    2, 0x06 /* Public */,
       5,    0,  242,    2, 0x06 /* Public */,
       6,    1,  243,    2, 0x06 /* Public */,
       8,    0,  246,    2, 0x06 /* Public */,
       9,    1,  247,    2, 0x06 /* Public */,
      11,    0,  250,    2, 0x06 /* Public */,
      12,    0,  251,    2, 0x06 /* Public */,
      13,    0,  252,    2, 0x06 /* Public */,
      14,    0,  253,    2, 0x06 /* Public */,
      15,    1,  254,    2, 0x06 /* Public */,
      16,    0,  257,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,  258,    2, 0x0a /* Public */,
      18,    1,  259,    2, 0x0a /* Public */,
      19,    1,  262,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      21,    0,  265,    2, 0x02 /* Public */,
      22,    1,  266,    2, 0x02 /* Public */,
      24,    1,  269,    2, 0x02 /* Public */,
      25,    0,  272,    2, 0x02 /* Public */,
      26,    1,  273,    2, 0x02 /* Public */,
      27,    2,  276,    2, 0x02 /* Public */,
      29,    1,  281,    2, 0x02 /* Public */,
      31,    0,  284,    2, 0x02 /* Public */,
      32,    2,  285,    2, 0x02 /* Public */,
      32,    1,  290,    2, 0x22 /* Public | MethodCloned */,
      35,    3,  293,    2, 0x02 /* Public */,
      35,    2,  300,    2, 0x22 /* Public | MethodCloned */,
      35,    1,  305,    2, 0x22 /* Public | MethodCloned */,
      38,    3,  308,    2, 0x02 /* Public */,
      38,    2,  315,    2, 0x22 /* Public | MethodCloned */,
      38,    1,  320,    2, 0x22 /* Public | MethodCloned */,
      39,    1,  323,    2, 0x02 /* Public */,
      41,    1,  326,    2, 0x02 /* Public */,
      43,    1,  329,    2, 0x02 /* Public */,
      44,    1,  332,    2, 0x02 /* Public */,
      45,    3,  335,    2, 0x02 /* Public */,
      49,    1,  342,    2, 0x02 /* Public */,
      50,    0,  345,    2, 0x02 /* Public */,
      51,    3,  346,    2, 0x02 /* Public */,
      54,    1,  353,    2, 0x02 /* Public */,
      56,    0,  356,    2, 0x02 /* Public */,
      57,    1,  357,    2, 0x02 /* Public */,
      58,    1,  360,    2, 0x02 /* Public */,
      59,    0,  363,    2, 0x02 /* Public */,

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
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariantList,    7,
    QMetaType::Void, QMetaType::QString,   20,

 // methods: parameters
    QMetaType::QString,
    QMetaType::Void, QMetaType::QStringList,   23,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::QString,
    QMetaType::QVariantList, QMetaType::QString,   20,
    QMetaType::Bool, QMetaType::QString, QMetaType::QVariantList,   20,   28,
    QMetaType::Bool, QMetaType::QString,   30,
    QMetaType::Void,
    QMetaType::QStringList, QMetaType::QString, QMetaType::Int,   33,   34,
    QMetaType::QStringList, QMetaType::QString,   33,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::Int, QMetaType::Int,   33,   36,   37,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::Int,   33,   36,
    QMetaType::QVariantList, QMetaType::QString,   33,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,   33,   36,   37,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   33,   36,
    QMetaType::Void, QMetaType::QString,   33,
    QMetaType::Void, QMetaType::QString,   40,
    QMetaType::Void, QMetaType::QString,   42,
    QMetaType::Void, QMetaType::QString,   40,
    QMetaType::QString, QMetaType::QString,   40,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QVariantList,   46,   47,   48,
    QMetaType::Void, QMetaType::QString,   46,
    QMetaType::QVariantList,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Bool,   40,   52,   53,
    QMetaType::QVariantList, QMetaType::Int,   55,
    QMetaType::Void,
    QMetaType::QVariantList, QMetaType::Int,   55,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Bool,

 // properties: name, type, flags
      60, QMetaType::QString, 0x00495103,
      61, 0x80000000 | 62, 0x00495009,
      63, QMetaType::Bool, 0x00495001,
      64, QMetaType::Int, 0x00495001,
      65, QMetaType::Int, 0x00495001,
      66, QMetaType::Bool, 0x00495103,
      67, QMetaType::QString, 0x00495001,
      68, QMetaType::Double, 0x00495001,
      69, QMetaType::QVariantList, 0x00495001,
      70, QMetaType::QString, 0x00495001,
      71, QMetaType::Bool, 0x00495103,
      72, QMetaType::QString, 0x00495103,

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
      11,
      12,

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
        case 11: _t->learningEnabledChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->formatFilterChanged(); break;
        case 13: _t->updateSearchResults(); break;
        case 14: _t->deliverSuggestClusters((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 15: _t->openFileRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: { QString _r = _t->selectDirectory();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 17: _t->loadConfigFiles((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 18: _t->openConfigFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: { QString _r = _t->pickConfigFile();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 20: { QVariantList _r = _t->readConfigFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 21: { bool _r = _t->writeConfigFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariantList(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 22: { bool _r = _t->initializeDatabase((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 23: _t->buildKeyIndex(); break;
        case 24: { QStringList _r = _t->suggestKeys((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 25: { QStringList _r = _t->suggestKeys((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 26: { QVariantList _r = _t->suggestClusters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 27: { QVariantList _r = _t->suggestClusters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 28: { QVariantList _r = _t->suggestClusters((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 29: _t->requestSuggestClusters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 30: _t->requestSuggestClusters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 31: _t->requestSuggestClusters((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 32: _t->analyzeSearchQuery((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 33: _t->applyAiSuggestion((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 34: _t->expandSearchWithAi((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 35: { QString _r = _t->getAiExplanation((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 36: _t->addUserTerm((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QVariantList(*)>(_a[3]))); break;
        case 37: _t->removeUserTerm((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 38: { QVariantList _r = _t->getUserTerms();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 39: _t->recordSearch((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 40: { QVariantList _r = _t->getSearchHistory((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 41: _t->clearSearchHistory(); break;
        case 42: { QVariantList _r = _t->getHotSearches((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 43: _t->setLearningEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 44: { bool _r = _t->isLearningEnabled();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
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
        {
            using _t = void (SearchViewModel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::learningEnabledChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (SearchViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::formatFilterChanged)) {
                *result = 12;
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
        case 10: *reinterpret_cast< bool*>(_v) = _t->isLearningEnabled(); break;
        case 11: *reinterpret_cast< QString*>(_v) = _t->formatFilter(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<SearchViewModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSearchText(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setAiEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 10: _t->setLearningEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 11: _t->setFormatFilter(*reinterpret_cast< QString*>(_v)); break;
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
        if (_id < 45)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 45;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 45)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 45;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
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

// SIGNAL 11
void SearchViewModel::learningEnabledChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void SearchViewModel::formatFilterChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
