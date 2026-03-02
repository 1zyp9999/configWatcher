#include <QKeySequence>
#include <QDebug>
#include <QApplication>
#include <QTimer>

#include "globalhotkey.h"

GlobalHotkey* GlobalHotkey::s_instance = nullptr;

GlobalHotkey::GlobalHotkey(QObject *parent) 
    : QObject(parent)
    , m_hotkeyId(1001)
    , m_display(nullptr)
    , m_window(0)
    , m_registered(false)
{
    s_instance = this;
    
    // 使用定时器轮询方式检测快捷键（更可靠）
    m_display = XOpenDisplay(nullptr);
    if (m_display) {
        m_window = DefaultRootWindow(m_display);
        qDebug() << "GlobalHotkey initialized with X11";
    } else {
        qWarning() << "Failed to open X display";
    }
}

GlobalHotkey::~GlobalHotkey()
{
    unregisterHotkey();
    if (m_display) {
        XCloseDisplay(m_display);
    }
    s_instance = nullptr;
}

bool GlobalHotkey::registerHotkey(const QString& keySequence)
{
    if (!m_display) {
        qWarning() << "X display not available";
        return false;
    }
    
    unregisterHotkey();
    
    Qt::KeyboardModifiers modifiers;
    Qt::Key key;
    
    if (!parseKeySequence(keySequence, modifiers, key)) {
        qWarning() << "Invalid key sequence:" << keySequence;
        return false;
    }
    
    uint x11Mods = getX11Modifiers(modifiers);
    KeyCode keyCode = XKeysymToKeycode(m_display, static_cast<KeySym>(key));
    
    if (keyCode == 0) {
        qWarning() << "Invalid key code for key:" << key;
        return false;
    }
    
    // 注册 X11 全局快捷键
    XGrabKey(m_display, keyCode, x11Mods, m_window, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(m_display, keyCode, x11Mods | LockMask, m_window, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(m_display, keyCode, x11Mods | Mod2Mask, m_window, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(m_display, keyCode, x11Mods | LockMask | Mod2Mask, m_window, True, GrabModeAsync, GrabModeAsync);
    
    // 刷新 X11 缓冲区确保注册生效
    XFlush(m_display);
    XSync(m_display, False);
    
    m_hotkeySequence = keySequence;
    m_registered = true;
    
    qDebug() << "Hotkey registered:" << keySequence << "keyCode:" << keyCode;
    return true;
}

void GlobalHotkey::unregisterHotkey()
{
    if (!m_registered || !m_display) return;
    
    XUngrabKey(m_display, AnyKey, AnyModifier, m_window);
    XFlush(m_display);
    
    m_registered = false;
    m_hotkeySequence.clear();
    
    qDebug() << "Hotkey unregistered";
}

bool GlobalHotkey::setHotkey(const QString& keySequence)
{
    return registerHotkey(keySequence);
}

bool GlobalHotkey::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)
    
    if (!m_registered || !m_display) return false;
    
    xcb_generic_event_t* event = static_cast<xcb_generic_event_t*>(message);
    if (!event) return false;
    
    uint8_t response_type = event->response_type & ~0x80;
    
    // 使用 KEY_PRESS 而非 KEY_RELEASE（更可靠，修饰键状态更准确）
    if (response_type == XCB_KEY_PRESS) {
        xcb_key_press_event_t* pressEvent = reinterpret_cast<xcb_key_press_event_t*>(event);
        
        Qt::KeyboardModifiers modifiers;
        Qt::Key key;
        if (parseKeySequence(m_hotkeySequence, modifiers, key)) {
            KeyCode keyCode = XKeysymToKeycode(m_display, static_cast<KeySym>(key));
            
            if (pressEvent->detail == keyCode) {
                // 验证修饰键状态（忽略 CapsLock/NumLock）
                uint x11Mods = getX11Modifiers(modifiers);
                uint stateMask = pressEvent->state & ~(LockMask | Mod2Mask);  // 排除 CapsLock 和 NumLock
                
                if (stateMask == x11Mods) {
                    emit activated();
                    return true;
                }
            }
        }
    }
    
    return false;
}

bool GlobalHotkey::parseKeySequence(const QString& keySequence, Qt::KeyboardModifiers& modifiers, Qt::Key& key)
{
    QKeySequence seq(keySequence);
    if (seq.isEmpty()) return false;
    
    int keyInt = seq[0];
    modifiers = Qt::KeyboardModifiers(keyInt & Qt::KeyboardModifierMask);
    key = static_cast<Qt::Key>(keyInt & ~Qt::KeyboardModifierMask);
    
    return true;
}

uint GlobalHotkey::getX11Modifiers(Qt::KeyboardModifiers modifiers)
{
    uint x11Mods = 0;
    
    if (modifiers & Qt::ShiftModifier) x11Mods |= ShiftMask;
    if (modifiers & Qt::ControlModifier) x11Mods |= ControlMask;
    if (modifiers & Qt::AltModifier) x11Mods |= Mod1Mask;
    if (modifiers & Qt::MetaModifier) x11Mods |= Mod4Mask;
    
    return x11Mods;
}
