#ifndef CONFIGENTRY_H
#define CONFIGENTRY_H

#include <QObject>
#include <QString>
#include <QStack>

class ConfigEntry;

class ConfigEntryPool {
public:
    static ConfigEntryPool& instance() {
        static ConfigEntryPool pool;
        return pool;
    }
    
    ConfigEntry* acquire(QObject* parent = nullptr);
    void release(ConfigEntry* entry);
    void clear();
    int size() const;

private:
    ConfigEntryPool() = default;
    ~ConfigEntryPool();
    
    QStack<ConfigEntry*> m_pool;
    int m_maxPoolSize = 100;
};

class ConfigEntry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(QString format READ format WRITE setFormat NOTIFY formatChanged)
    Q_PROPERTY(QString chineseKey READ chineseKey WRITE setChineseKey NOTIFY chineseKeyChanged)

public:
    explicit ConfigEntry(QObject *parent = nullptr) : QObject(parent) {}

    QString key() const { return m_key; }
    void setKey(const QString& key) { m_key = key; emit keyChanged(); }

    QString value() const { return m_value; }
    void setValue(const QString& value) { m_value = value; emit valueChanged(); }

    QString filePath() const { return m_filePath; }
    void setFilePath(const QString& filePath) { m_filePath = filePath; emit filePathChanged(); }

    QString format() const { return m_format; }
    void setFormat(const QString& format) { m_format = format; emit formatChanged(); }

    QString chineseKey() const { return m_chineseKey; }
    void setChineseKey(const QString& chineseKey) { m_chineseKey = chineseKey; emit chineseKeyChanged(); }
    
    void reset() {
        m_key.clear();
        m_value.clear();
        m_filePath.clear();
        m_format.clear();
        m_chineseKey.clear();
    }

signals:
    void keyChanged();
    void valueChanged();
    void filePathChanged();
    void formatChanged();
    void chineseKeyChanged();

private:
    QString m_key;
    QString m_value;
    QString m_filePath;
    QString m_format;
    QString m_chineseKey;
};

inline ConfigEntry* ConfigEntryPool::acquire(QObject* parent) {
    if (m_pool.isEmpty()) {
        return new ConfigEntry(parent);
    }
    ConfigEntry* entry = m_pool.pop();
    entry->setParent(parent);
    entry->reset();
    return entry;
}

inline void ConfigEntryPool::release(ConfigEntry* entry) {
    if (entry && m_pool.size() < m_maxPoolSize) {
        entry->setParent(nullptr);
        entry->reset();
        m_pool.push(entry);
    } else if (entry) {
        delete entry;
    }
}

inline void ConfigEntryPool::clear() {
    while (!m_pool.isEmpty()) {
        delete m_pool.pop();
    }
}

inline int ConfigEntryPool::size() const { 
    return m_pool.size(); 
}

inline ConfigEntryPool::~ConfigEntryPool() { 
    clear(); 
}

#endif // CONFIGENTRY_H
