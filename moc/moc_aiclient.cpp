/****************************************************************************
** Meta object code from reading C++ file 'aiclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../include/aiclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'aiclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AiClient_t {
    QByteArrayData data[69];
    char stringdata0[790];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AiClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AiClient_t qt_meta_stringdata_AiClient = {
    {
QT_MOC_LITERAL(0, 0, 8), // "AiClient"
QT_MOC_LITERAL(1, 9, 14), // "enabledChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "enabled"
QT_MOC_LITERAL(4, 33, 15), // "providerChanged"
QT_MOC_LITERAL(5, 49, 8), // "provider"
QT_MOC_LITERAL(6, 58, 13), // "apiKeyChanged"
QT_MOC_LITERAL(7, 72, 3), // "key"
QT_MOC_LITERAL(8, 76, 12), // "modelChanged"
QT_MOC_LITERAL(9, 89, 5), // "model"
QT_MOC_LITERAL(10, 95, 14), // "baseUrlChanged"
QT_MOC_LITERAL(11, 110, 3), // "url"
QT_MOC_LITERAL(12, 114, 17), // "processingChanged"
QT_MOC_LITERAL(13, 132, 10), // "processing"
QT_MOC_LITERAL(14, 143, 13), // "errorOccurred"
QT_MOC_LITERAL(15, 157, 5), // "error"
QT_MOC_LITERAL(16, 163, 18), // "temperatureChanged"
QT_MOC_LITERAL(17, 182, 4), // "temp"
QT_MOC_LITERAL(18, 187, 16), // "maxTokensChanged"
QT_MOC_LITERAL(19, 204, 6), // "tokens"
QT_MOC_LITERAL(20, 211, 14), // "intentAnalyzed"
QT_MOC_LITERAL(21, 226, 6), // "intent"
QT_MOC_LITERAL(22, 233, 10), // "confidence"
QT_MOC_LITERAL(23, 244, 11), // "explanation"
QT_MOC_LITERAL(24, 256, 16), // "keywordsExpanded"
QT_MOC_LITERAL(25, 273, 8), // "keywords"
QT_MOC_LITERAL(26, 282, 20), // "searchTermsSuggested"
QT_MOC_LITERAL(27, 303, 5), // "terms"
QT_MOC_LITERAL(28, 309, 15), // "configExplained"
QT_MOC_LITERAL(29, 325, 15), // "configValidated"
QT_MOC_LITERAL(30, 341, 6), // "issues"
QT_MOC_LITERAL(31, 348, 12), // "chatResponse"
QT_MOC_LITERAL(32, 361, 8), // "response"
QT_MOC_LITERAL(33, 370, 15), // "promptCompleted"
QT_MOC_LITERAL(34, 386, 6), // "result"
QT_MOC_LITERAL(35, 393, 15), // "onReplyFinished"
QT_MOC_LITERAL(36, 409, 12), // "onReplyError"
QT_MOC_LITERAL(37, 422, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(38, 450, 9), // "onTimeout"
QT_MOC_LITERAL(39, 460, 13), // "analyzeIntent"
QT_MOC_LITERAL(40, 474, 5), // "query"
QT_MOC_LITERAL(41, 480, 14), // "expandKeywords"
QT_MOC_LITERAL(42, 495, 18), // "suggestSearchTerms"
QT_MOC_LITERAL(43, 514, 7), // "context"
QT_MOC_LITERAL(44, 522, 13), // "explainConfig"
QT_MOC_LITERAL(45, 536, 5), // "value"
QT_MOC_LITERAL(46, 542, 14), // "validateConfig"
QT_MOC_LITERAL(47, 557, 6), // "config"
QT_MOC_LITERAL(48, 564, 4), // "chat"
QT_MOC_LITERAL(49, 569, 7), // "message"
QT_MOC_LITERAL(50, 577, 7), // "history"
QT_MOC_LITERAL(51, 585, 14), // "completePrompt"
QT_MOC_LITERAL(52, 600, 6), // "prompt"
QT_MOC_LITERAL(53, 607, 22), // "getConversationHistory"
QT_MOC_LITERAL(54, 630, 24), // "clearConversationHistory"
QT_MOC_LITERAL(55, 655, 12), // "abortRequest"
QT_MOC_LITERAL(56, 668, 12), // "loadSettings"
QT_MOC_LITERAL(57, 681, 12), // "saveSettings"
QT_MOC_LITERAL(58, 694, 6), // "apiKey"
QT_MOC_LITERAL(59, 701, 7), // "baseUrl"
QT_MOC_LITERAL(60, 709, 12), // "isProcessing"
QT_MOC_LITERAL(61, 722, 9), // "lastError"
QT_MOC_LITERAL(62, 732, 11), // "temperature"
QT_MOC_LITERAL(63, 744, 9), // "maxTokens"
QT_MOC_LITERAL(64, 754, 8), // "Provider"
QT_MOC_LITERAL(65, 763, 6), // "OpenAI"
QT_MOC_LITERAL(66, 770, 5), // "Azure"
QT_MOC_LITERAL(67, 776, 6), // "Ollama"
QT_MOC_LITERAL(68, 783, 6) // "Custom"

    },
    "AiClient\0enabledChanged\0\0enabled\0"
    "providerChanged\0provider\0apiKeyChanged\0"
    "key\0modelChanged\0model\0baseUrlChanged\0"
    "url\0processingChanged\0processing\0"
    "errorOccurred\0error\0temperatureChanged\0"
    "temp\0maxTokensChanged\0tokens\0"
    "intentAnalyzed\0intent\0confidence\0"
    "explanation\0keywordsExpanded\0keywords\0"
    "searchTermsSuggested\0terms\0configExplained\0"
    "configValidated\0issues\0chatResponse\0"
    "response\0promptCompleted\0result\0"
    "onReplyFinished\0onReplyError\0"
    "QNetworkReply::NetworkError\0onTimeout\0"
    "analyzeIntent\0query\0expandKeywords\0"
    "suggestSearchTerms\0context\0explainConfig\0"
    "value\0validateConfig\0config\0chat\0"
    "message\0history\0completePrompt\0prompt\0"
    "getConversationHistory\0clearConversationHistory\0"
    "abortRequest\0loadSettings\0saveSettings\0"
    "apiKey\0baseUrl\0isProcessing\0lastError\0"
    "temperature\0maxTokens\0Provider\0OpenAI\0"
    "Azure\0Ollama\0Custom"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AiClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       9,  264, // properties
       1,  300, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  174,    2, 0x06 /* Public */,
       4,    1,  177,    2, 0x06 /* Public */,
       6,    1,  180,    2, 0x06 /* Public */,
       8,    1,  183,    2, 0x06 /* Public */,
      10,    1,  186,    2, 0x06 /* Public */,
      12,    1,  189,    2, 0x06 /* Public */,
      14,    1,  192,    2, 0x06 /* Public */,
      16,    1,  195,    2, 0x06 /* Public */,
      18,    1,  198,    2, 0x06 /* Public */,
      20,    3,  201,    2, 0x06 /* Public */,
      24,    1,  208,    2, 0x06 /* Public */,
      26,    1,  211,    2, 0x06 /* Public */,
      28,    1,  214,    2, 0x06 /* Public */,
      29,    1,  217,    2, 0x06 /* Public */,
      31,    1,  220,    2, 0x06 /* Public */,
      33,    1,  223,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      35,    0,  226,    2, 0x08 /* Private */,
      36,    1,  227,    2, 0x08 /* Private */,
      38,    0,  230,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      39,    1,  231,    2, 0x02 /* Public */,
      41,    1,  234,    2, 0x02 /* Public */,
      42,    1,  237,    2, 0x02 /* Public */,
      44,    2,  240,    2, 0x02 /* Public */,
      46,    1,  245,    2, 0x02 /* Public */,
      48,    2,  248,    2, 0x02 /* Public */,
      48,    1,  253,    2, 0x22 /* Public | MethodCloned */,
      51,    1,  256,    2, 0x02 /* Public */,
      53,    0,  259,    2, 0x02 /* Public */,
      54,    0,  260,    2, 0x02 /* Public */,
      55,    0,  261,    2, 0x02 /* Public */,
      56,    0,  262,    2, 0x02 /* Public */,
      57,    0,  263,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::Double,   17,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::QString, QMetaType::Double, QMetaType::QString,   21,   22,   23,
    QMetaType::Void, QMetaType::QVariantList,   25,
    QMetaType::Void, QMetaType::QVariantList,   27,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, QMetaType::QVariantList,   30,
    QMetaType::Void, QMetaType::QString,   32,
    QMetaType::Void, QMetaType::QString,   34,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 37,   15,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   40,
    QMetaType::Void, QMetaType::QString,   40,
    QMetaType::Void, QMetaType::QString,   43,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,   45,
    QMetaType::Void, QMetaType::QVariantMap,   47,
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantList,   49,   50,
    QMetaType::Void, QMetaType::QString,   49,
    QMetaType::Void, QMetaType::QString,   52,
    QMetaType::QVariantList,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,

 // properties: name, type, flags
       3, QMetaType::Bool, 0x00495103,
       5, QMetaType::QString, 0x00495103,
      58, QMetaType::QString, 0x00495103,
       9, QMetaType::QString, 0x00495103,
      59, QMetaType::QString, 0x00495103,
      60, QMetaType::Bool, 0x00495001,
      61, QMetaType::QString, 0x00495001,
      62, QMetaType::Double, 0x00495103,
      63, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,

 // enums: name, alias, flags, count, data
      64,   64, 0x0,    4,  305,

 // enum data: key, value
      65, uint(AiClient::OpenAI),
      66, uint(AiClient::Azure),
      67, uint(AiClient::Ollama),
      68, uint(AiClient::Custom),

       0        // eod
};

void AiClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AiClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->enabledChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->providerChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->apiKeyChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->modelChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->baseUrlChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->processingChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->temperatureChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->maxTokensChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->intentAnalyzed((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 10: _t->keywordsExpanded((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 11: _t->searchTermsSuggested((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 12: _t->configExplained((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->configValidated((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 14: _t->chatResponse((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->promptCompleted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->onReplyFinished(); break;
        case 17: _t->onReplyError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 18: _t->onTimeout(); break;
        case 19: _t->analyzeIntent((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: _t->expandKeywords((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 21: _t->suggestSearchTerms((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: _t->explainConfig((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 23: _t->validateConfig((*reinterpret_cast< const QVariantMap(*)>(_a[1]))); break;
        case 24: _t->chat((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariantList(*)>(_a[2]))); break;
        case 25: _t->chat((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: _t->completePrompt((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 27: { QVariantList _r = _t->getConversationHistory();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 28: _t->clearConversationHistory(); break;
        case 29: _t->abortRequest(); break;
        case 30: { bool _r = _t->loadSettings();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 31: { bool _r = _t->saveSettings();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AiClient::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::enabledChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::providerChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::apiKeyChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::modelChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::baseUrlChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::processingChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::errorOccurred)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::temperatureChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::maxTokensChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(const QString & , double , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::intentAnalyzed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(const QVariantList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::keywordsExpanded)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(const QVariantList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::searchTermsSuggested)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::configExplained)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(const QVariantList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::configValidated)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::chatResponse)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (AiClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AiClient::promptCompleted)) {
                *result = 15;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AiClient *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isEnabled(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->provider(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->apiKey(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->model(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->baseUrl(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->isProcessing(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->lastError(); break;
        case 7: *reinterpret_cast< double*>(_v) = _t->temperature(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->maxTokens(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<AiClient *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setProvider(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setApiKey(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setModel(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setBaseUrl(*reinterpret_cast< QString*>(_v)); break;
        case 7: _t->setTemperature(*reinterpret_cast< double*>(_v)); break;
        case 8: _t->setMaxTokens(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject AiClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AiClient.data,
    qt_meta_data_AiClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AiClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AiClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AiClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AiClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AiClient::enabledChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AiClient::providerChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AiClient::apiKeyChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AiClient::modelChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AiClient::baseUrlChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AiClient::processingChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AiClient::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AiClient::temperatureChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void AiClient::maxTokensChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void AiClient::intentAnalyzed(const QString & _t1, double _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void AiClient::keywordsExpanded(const QVariantList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void AiClient::searchTermsSuggested(const QVariantList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void AiClient::configExplained(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void AiClient::configValidated(const QVariantList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void AiClient::chatResponse(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void AiClient::promptCompleted(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
