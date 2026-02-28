#include "loginviewmodel.h"
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QCryptographicHash>

LoginViewModel::LoginViewModel(QObject *parent) : QObject(parent)
{
    loadCredentials();
}

void LoginViewModel::setUsername(const QString& username)
{
    if (m_username == username) return;
    m_username = username;
    emit usernameChanged();
}

void LoginViewModel::setPassword(const QString& password)
{
    if (m_password == password) return;
    m_password = password;
    emit passwordChanged();
}

void LoginViewModel::setRememberPassword(bool remember)
{
    if (m_rememberPassword == remember) return;
    m_rememberPassword = remember;
    emit rememberPasswordChanged();
}

QString LoginViewModel::encryptPassword(const QString& password)
{
    QString salt = "ConfigWatcher2024";
    QString toHash = password + salt;
    QByteArray hashed = QCryptographicHash::hash(toHash.toUtf8(), QCryptographicHash::Sha256);
    return QString::fromLatin1(hashed.toBase64());
}

QString LoginViewModel::decryptPassword(const QString& encrypted)
{
    Q_UNUSED(encrypted);
    return QString();
}

QString LoginViewModel::getConfigPath() const
{
    QString configDir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/ConfigWatcher";
    QDir dir;
    if (!dir.exists(configDir)) {
        dir.mkpath(configDir);
    }
    return configDir + "/credentials.conf";
}

void LoginViewModel::loadCredentials()
{
    QString configPath = getConfigPath();
    QSettings settings(configPath, QSettings::IniFormat);

    m_username = settings.value("username", "admin").toString();
    m_rememberPassword = settings.value("rememberPassword", false).toBool();
    
    // 不加载密码（密码是加密的，无法解密）
    m_password = "";
}

void LoginViewModel::saveCredentials()
{
    if (!m_rememberPassword) {
        QFile::remove(getConfigPath());
        return;
    }

    QString configPath = getConfigPath();
    QSettings settings(configPath, QSettings::IniFormat);

    settings.setValue("username", m_username);
    settings.setValue("password", encryptPassword(m_password));
    settings.setValue("rememberPassword", m_rememberPassword);
    settings.sync();
    
    qDebug() << "Credentials saved to:" << configPath;
}

bool LoginViewModel::checkLogin()
{
    m_errorMessage = "";
    emit errorMessageChanged();

    qDebug() << "Login attempt - username:" << m_username << ", password:" << m_password;
    
    // 简单验证：用户名 admin，密码 aoi2024
    if (m_username == "admin" && m_password == "aoi2024") {
        qDebug() << "Login successful!";
        
        // 登录成功，如果需要则保存凭证
        if (m_rememberPassword) {
            saveCredentials();
        }

        emit loginSuccess();
        return true;
    } else {
        m_errorMessage = "用户名或密码错误";
        emit errorMessageChanged();
        qDebug() << "Login failed!";
        return false;
    }
}
