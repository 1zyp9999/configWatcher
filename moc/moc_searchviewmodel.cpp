/****************************************************************************
** Meta object code from reading C++ file 'searchviewmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/viewmodel/searchviewmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
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
    QByteArrayData data[47];
    char stringdata0[643];
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
QT_MOC_LITERAL(8, 123, 17), // "searchModeChanged"
QT_MOC_LITERAL(9, 141, 18), // "currentPageChanged"
QT_MOC_LITERAL(10, 160, 17), // "totalPagesChanged"
QT_MOC_LITERAL(11, 178, 19), // "updateSearchResults"
QT_MOC_LITERAL(12, 198, 22), // "deliverSuggestClusters"
QT_MOC_LITERAL(13, 221, 17), // "openFileRequested"
QT_MOC_LITERAL(14, 239, 8), // "filePath"
QT_MOC_LITERAL(15, 248, 13), // "onParserError"
QT_MOC_LITERAL(16, 262, 7), // "message"
QT_MOC_LITERAL(17, 270, 14), // "pickConfigFile"
QT_MOC_LITERAL(18, 285, 14), // "readConfigFile"
QT_MOC_LITERAL(19, 300, 15), // "writeConfigFile"
QT_MOC_LITERAL(20, 316, 7), // "entries"
QT_MOC_LITERAL(21, 324, 15), // "selectDirectory"
QT_MOC_LITERAL(22, 340, 15), // "loadConfigFiles"
QT_MOC_LITERAL(23, 356, 9), // "filePaths"
QT_MOC_LITERAL(24, 366, 14), // "openConfigFile"
QT_MOC_LITERAL(25, 381, 18), // "initializeDatabase"
QT_MOC_LITERAL(26, 400, 6), // "dbPath"
QT_MOC_LITERAL(27, 407, 13), // "buildKeyIndex"
QT_MOC_LITERAL(28, 421, 11), // "suggestKeys"
QT_MOC_LITERAL(29, 433, 6), // "prefix"
QT_MOC_LITERAL(30, 440, 10), // "maxResults"
QT_MOC_LITERAL(31, 451, 15), // "suggestClusters"
QT_MOC_LITERAL(32, 467, 11), // "maxClusters"
QT_MOC_LITERAL(33, 479, 13), // "maxPerCluster"
QT_MOC_LITERAL(34, 493, 22), // "requestSuggestClusters"
QT_MOC_LITERAL(35, 516, 8), // "nextPage"
QT_MOC_LITERAL(36, 525, 12), // "previousPage"
QT_MOC_LITERAL(37, 538, 8), // "goToPage"
QT_MOC_LITERAL(38, 547, 4), // "page"
QT_MOC_LITERAL(39, 552, 10), // "searchText"
QT_MOC_LITERAL(40, 563, 13), // "searchResults"
QT_MOC_LITERAL(41, 577, 9), // "isLoading"
QT_MOC_LITERAL(42, 587, 12), // "loadProgress"
QT_MOC_LITERAL(43, 600, 10), // "searchMode"
QT_MOC_LITERAL(44, 611, 11), // "currentPage"
QT_MOC_LITERAL(45, 623, 10), // "totalPages"
QT_MOC_LITERAL(46, 634, 8) // "pageSize"

    },
    "SearchViewModel\0searchTextChanged\0\0"
    "searchResultsChanged\0isLoadingChanged\0"
    "loadProgressChanged\0suggestClustersReady\0"
    "clusters\0searchModeChanged\0"
    "currentPageChanged\0totalPagesChanged\0"
    "updateSearchResults\0deliverSuggestClusters\0"
    "openFileRequested\0filePath\0onParserError\0"
    "message\0pickConfigFile\0readConfigFile\0"
    "writeConfigFile\0entries\0selectDirectory\0"
    "loadConfigFiles\0filePaths\0openConfigFile\0"
    "initializeDatabase\0dbPath\0buildKeyIndex\0"
    "suggestKeys\0prefix\0maxResults\0"
    "suggestClusters\0maxClusters\0maxPerCluster\0"
    "requestSuggestClusters\0nextPage\0"
    "previousPage\0goToPage\0page\0searchText\0"
    "searchResults\0isLoading\0loadProgress\0"
    "searchMode\0currentPage\0totalPages\0"
    "pageSize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchViewModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       8,  252, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  169,    2, 0x06 /* Public */,
       3,    0,  170,    2, 0x06 /* Public */,
       4,    0,  171,    2, 0x06 /* Public */,
       5,    0,  172,    2, 0x06 /* Public */,
       6,    1,  173,    2, 0x06 /* Public */,
       8,    0,  176,    2, 0x06 /* Public */,
       9,    0,  177,    2, 0x06 /* Public */,
      10,    0,  178,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,  179,    2, 0x0a /* Public */,
      12,    1,  180,    2, 0x0a /* Public */,
      13,    1,  183,    2, 0x0a /* Public */,
      15,    1,  186,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      17,    0,  189,    2, 0x02 /* Public */,
      18,    1,  190,    2, 0x02 /* Public */,
      19,    2,  193,    2, 0x02 /* Public */,
      21,    0,  198,    2, 0x02 /* Public */,
      22,    1,  199,    2, 0x02 /* Public */,
      24,    1,  202,    2, 0x02 /* Public */,
      25,    1,  205,    2, 0x02 /* Public */,
      27,    0,  208,    2, 0x02 /* Public */,
      28,    2,  209,    2, 0x02 /* Public */,
      28,    1,  214,    2, 0x22 /* Public | MethodCloned */,
      31,    3,  217,    2, 0x02 /* Public */,
      31,    2,  224,    2, 0x22 /* Public | MethodCloned */,
      31,    1,  229,    2, 0x22 /* Public | MethodCloned */,
      34,    3,  232,    2, 0x02 /* Public */,
      34,    2,  239,    2, 0x22 /* Public | MethodCloned */,
      34,    1,  244,    2, 0x22 /* Public | MethodCloned */,
      35,    0,  247,    2, 0x02 /* Public */,
      36,    0,  248,    2, 0x02 /* Public */,
      37,    1,  249,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariantList,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariantList,    7,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString,   16,

 // methods: parameters
    QMetaType::QString,
    QMetaType::QVariantList, QMetaType::QString,   14,
    QMetaType::Bool, QMetaType::QString, QMetaType::QVariantList,   14,   20,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QStringList,   23,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Bool, QMetaType::QString,   26,
    QMetaType::Void,
    QMetaType::QStringList, QMetaType::QString, QMetaType::Int,   29,   30,
    QMetaType::QStringList, QMetaType::QString,   29,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::Int, QMetaType::Int,   29,   32,   33,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::Int,   29,   32,
    QMetaType::QVariantList, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,   29,   32,   33,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   29,   32,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,

 // properties: name, type, flags
      39, QMetaType::QString, 0x00495103,
      40, QMetaType::QVariantList, 0x00495001,
      41, QMetaType::Bool, 0x00495001,
      42, QMetaType::Int, 0x00495001,
      43, QMetaType::Int, 0x00495103,
      44, QMetaType::Int, 0x00495103,
      45, QMetaType::Int, 0x00495001,
      46, QMetaType::Int, 0x00095401,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       5,
       6,
       7,
       0,

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
        case 5: _t->searchModeChanged(); break;
        case 6: _t->currentPageChanged(); break;
        case 7: _t->totalPagesChanged(); break;
        case 8: _t->updateSearchResults(); break;
        case 9: _t->deliverSuggestClusters((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 10: _t->openFileRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->onParserError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: { QString _r = _t->pickConfigFile();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 13: { QVariantList _r = _t->readConfigFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 14: { bool _r = _t->writeConfigFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariantList(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 15: { QString _r = _t->selectDirectory();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->loadConfigFiles((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 17: _t->openConfigFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: { bool _r = _t->initializeDatabase((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 19: _t->buildKeyIndex(); break;
        case 20: { QStringList _r = _t->suggestKeys((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 21: { QStringList _r = _t->suggestKeys((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 22: { QVariantList _r = _t->suggestClusters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 23: { QVariantList _r = _t->suggestClusters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 24: { QVariantList _r = _t->suggestClusters((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 25: _t->requestSuggestClusters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 26: _t->requestSuggestClusters((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 27: _t->requestSuggestClusters((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 28: _t->nextPage(); break;
        case 29: _t->previousPage(); break;
        case 30: _t->goToPage((*reinterpret_cast< int(*)>(_a[1]))); break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::searchModeChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SearchViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::currentPageChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SearchViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchViewModel::totalPagesChanged)) {
                *result = 7;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SearchViewModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->searchText(); break;
        case 1: *reinterpret_cast< QVariantList*>(_v) = _t->searchResults(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isLoading(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->loadProgress(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->searchMode(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->currentPage(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->totalPages(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->pageSize(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<SearchViewModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSearchText(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setSearchMode(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setCurrentPage(*reinterpret_cast< int*>(_v)); break;
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
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 31;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 8;
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
void SearchViewModel::searchModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void SearchViewModel::currentPageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void SearchViewModel::totalPagesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
