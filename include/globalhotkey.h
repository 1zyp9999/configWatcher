#ifndef GLOBALHOTKEY_H
#define GLOBALHOTKEY_H

#include <QObject>
#include <QAbstractNativeEventFilter>
#include <QKeySequence>

// X11 和 XCB 头文件
#include <X11/Xlib.h>
#include <xcb/xcb.h>

/**
 * @brief 全局快捷键管理类
 * 支持在 Linux X11 环境下注册全局快捷键
 */
class GlobalHotkey : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    explicit GlobalHotkey(QObject *parent = nullptr);
    ~GlobalHotkey();

    bool registerHotkey(const QString& keySequence);
    void unregisterHotkey();
    QString getHotkey() const { return m_hotkeySequence; }
    bool setHotkey(const QString& keySequence);

signals:
    void activated();

private:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;
    bool parseKeySequence(const QString& keySequence, Qt::KeyboardModifiers& modifiers, Qt::Key& key);
    uint getX11Modifiers(Qt::KeyboardModifiers modifiers);

private:
    QString m_hotkeySequence;
    int m_hotkeyId;
    Display* m_display;
    Window m_window;
    bool m_registered;
    
    static GlobalHotkey* s_instance;
};

#endif // GLOBALHOTKEY_H
