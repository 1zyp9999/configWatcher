#ifndef CONFIGENTRY_H
#define CONFIGENTRY_H

#include <QObject>
#include <QString>

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

    // Getter/Setter
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

#endif // CONFIGENTRY_H
