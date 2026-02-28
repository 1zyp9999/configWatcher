#ifndef LOGINVIEWMODEL_H
#define LOGINVIEWMODEL_H

#include <QObject>
#include <QString>
#include <QSettings>
#include <QByteArray>
#include <QCryptographicHash>

class LoginViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(bool rememberPassword READ rememberPassword WRITE setRememberPassword NOTIFY rememberPasswordChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged)

public:
    explicit LoginViewModel(QObject *parent = nullptr);

    QString username() const { return m_username; }
    QString password() const { return m_password; }
    bool rememberPassword() const { return m_rememberPassword; }
    QString errorMessage() const { return m_errorMessage; }

    void setUsername(const QString& username);
    void setPassword(const QString& password);
    void setRememberPassword(bool remember);

    Q_INVOKABLE bool checkLogin();
    
    // 从配置文件加载凭证
    Q_INVOKABLE void loadCredentials();
    // 保存凭证（加密密码）
    Q_INVOKABLE void saveCredentials();

signals:
    void usernameChanged();
    void passwordChanged();
    void rememberPasswordChanged();
    void errorMessageChanged();
    void loginSuccess();

private:
    QString m_username;
    QString m_password;
    bool m_rememberPassword = false;
    QString m_errorMessage;
    
    // 简单的密码加密（Base64 + XOR，生产环境应使用更安全的方案）
    QString encryptPassword(const QString& password);
    QString decryptPassword(const QString& encrypted);
    
    // 配置文件路径
    QString getConfigPath() const;
};

#endif // LOGINVIEWMODEL_H
