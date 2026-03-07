#ifndef CONFIGVALIDATOR_H
#define CONFIGVALIDATOR_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>
#include <QHash>
#include <QRegularExpression>

struct ValidationRule {
    QString key;
    QString keyPattern;
    QString type;
    QVariant minValue;
    QVariant maxValue;
    QStringList allowedValues;
    QString regex;
    bool required;
    QString description;
};

class ConfigValidator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList validationResults READ validationResults NOTIFY validationResultsChanged)
    Q_PROPERTY(int errorCount READ errorCount NOTIFY validationResultsChanged)
    Q_PROPERTY(int warningCount READ warningCount NOTIFY validationResultsChanged)
    Q_PROPERTY(int infoCount READ infoCount NOTIFY validationResultsChanged)

public:
    enum Severity {
        Error,
        Warning,
        Info
    };
    Q_ENUM(Severity)

    explicit ConfigValidator(QObject* parent = nullptr);
    ~ConfigValidator();

    static ConfigValidator* instance();

    QVariantList validationResults() const { return m_results; }
    int errorCount() const;
    int warningCount() const;
    int infoCount() const;

    Q_INVOKABLE QVariantList validateFile(const QString& filePath);
    Q_INVOKABLE QVariantList validateConfig(const QVariantList& config, const QString& filePath = QString());
    Q_INVOKABLE QVariantList validateKey(const QString& key, const QString& value, const QString& section = QString());
    
    Q_INVOKABLE bool loadSchema(const QString& schemaPath);
    Q_INVOKABLE bool loadSchemaFromJson(const QString& jsonContent);
    Q_INVOKABLE QVariantMap getSchema();
    Q_INVOKABLE bool saveSchema(const QString& outputPath);
    
    Q_INVOKABLE void addRule(const QString& key, const QString& type, const QVariantMap& constraints);
    Q_INVOKABLE void removeRule(const QString& key);
    Q_INVOKABLE void clearRules();
    Q_INVOKABLE QVariantList getRules();
    
    Q_INVOKABLE QVariantList checkConflicts(const QVariantList& config);
    Q_INVOKABLE QVariantList checkDependencies(const QVariantList& config);
    Q_INVOKABLE QVariantList checkRanges(const QVariantList& config);
    Q_INVOKABLE QVariantList checkFormats(const QVariantList& config);
    
    Q_INVOKABLE QString generateValidationReport(const QString& format = "text");
    Q_INVOKABLE bool exportValidationReport(const QString& outputPath, const QString& format = "text");
    
    Q_INVOKABLE QVariantList suggestFixes(const QVariantList& issues);
    Q_INVOKABLE bool autoFix(QVariantList& config, const QVariantList& issues);

signals:
    void validationResultsChanged();
    void validationCompleted(int errors, int warnings, int infos);
    void schemaLoaded(const QString& schemaPath);
    void errorOccurred(const QString& error);

private:
    bool validateType(const QString& type, const QString& value);
    bool validateRange(const QString& value, const QVariant& min, const QVariant& max);
    bool validateRegex(const QString& value, const QString& pattern);
    bool validateEnum(const QString& value, const QStringList& allowed);
    
    void addResult(const QString& key, Severity severity, const QString& message, const QString& suggestion = QString());
    QVariantList parseConfigFile(const QString& filePath);
    QString detectFormat(const QString& filePath);
    QString getSchemaPath();
    void loadDefaultSchema();
    void loadBuiltinRules();

private:
    QVariantList m_results;
    QHash<QString, ValidationRule> m_rules;
    QVariantMap m_schema;
    QString m_lastValidatedFile;
    
    static ConfigValidator* s_instance;
};

#endif // CONFIGVALIDATOR_H
