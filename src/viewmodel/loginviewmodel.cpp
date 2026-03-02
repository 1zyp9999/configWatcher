#include "loginviewmodel.h"
#include <QDebug>
#include <QTimer>
#include <QStandardPaths>
#include <QDir>

LoginViewModel::LoginViewModel(QObject *parent) : QObject(parent)
{
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

bool LoginViewModel::checkLogin()
{
    m_errorMessage = "";
    emit errorMessageChanged();

    // 登录校验（账号：admin，密码：aoi2024）
    if (m_username == "admin" && m_password == "aoi2024") {
        emit loginSuccess();

        // Database import is handled centrally in main.cpp on startup; do not create DB here to avoid duplicate connections.

        return true;
    } else {
        m_errorMessage = "用户名或密码错误";
        emit errorMessageChanged();
        return false;
    }
}
