#ifndef LOGINVIEWMODEL_H
#define LOGINVIEWMODEL_H

#include <QObject>
#include <QString>

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
};

#endif // LOGINVIEWMODEL_H
