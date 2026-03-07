#!/bin/bash
# ConfigWatcher 快捷键唤起脚本
# 使用方法 1：直接运行 - 切换窗口显示/隐藏
# 使用方法 2：带参数运行 - ./toggle_window.sh setup 自动设置系统快捷键

PROGRAM="ConfigWatcher"
BIN_PATH="$HOME/ConfigWatcher/bin/ConfigWatcher"
SCRIPT_PATH="$(readlink -f "$0")"

# 检测桌面环境
detect_desktop() {
    if [ -n "$GNOME_DESKTOP_SESSION_ID" ] || echo "$XDG_CURRENT_DESKTOP" | grep -qi "gnome"; then
        echo "gnome"
    elif echo "$XDG_CURRENT_DESKTOP" | grep -qi "kde"; then
        echo "kde"
    elif echo "$XDG_CURRENT_DESKTOP" | grep -qi "xfce"; then
        echo "xfce"
    elif echo "$DESKTOP_SESSION" | grep -qi "mate"; then
        echo "mate"
    else
        echo "unknown"
    fi
}

# 设置 GNOME 快捷键
setup_gnome_hotkey() {
    echo "检测到 GNOME 桌面环境"
    gsettings set org.gnome.settings-daemon.plugins.media-keys custom-keybindings "['/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/']"
    gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/ name "ConfigWatcher"
    gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/ command "$SCRIPT_PATH"
    gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/ binding "<Primary><Alt>Q"
    echo "✅ GNOME 快捷键已设置：Ctrl+Alt+Q → ConfigWatcher"
}

# 自动设置快捷键
auto_setup() {
    DESKTOP=$(detect_desktop)
    case "$DESKTOP" in
        gnome) setup_gnome_hotkey ;;
        *) echo "⚠️ 桌面环境：$DESKTOP，请手动设置快捷键" ;;
    esac
}

# 切换窗口显示/隐藏
toggle_window() {
    # 检查程序是否在运行
    PID=$(pgrep -f "$PROGRAM")
    
    if [ -z "$PID" ]; then
        # 程序未运行，启动它
        echo "🚀 启动 ConfigWatcher..."
        nohup "$BIN_PATH" > /dev/null 2>&1 &
        sleep 2
    else
        # 程序在运行，查找窗口（使用窗口类名匹配）
        WINDOW_ID=$(xdotool search --name "ConfigWatcher" 2>/dev/null | head -1)
        
        # 如果没找到，尝试用窗口标题的一部分
        if [ -z "$WINDOW_ID" ]; then
            WINDOW_ID=$(xdotool search --name "AOI" 2>/dev/null | head -1)
        fi
        
        if [ -z "$WINDOW_ID" ]; then
            # 窗口不存在（可能在托盘），尝试通过托盘唤醒
            echo "📌 窗口在托盘区，尝试唤醒..."
            # 简单方案：重启程序
            kill $PID 2>/dev/null
            sleep 1
            nohup "$BIN_PATH" > /dev/null 2>&1 &
        else
            # 检查窗口是否可见
            if xdotool search --onlyvisible --name "ConfigWatcher" > /dev/null 2>&1; then
                # 窗口可见，隐藏它
                echo "🙈 隐藏 ConfigWatcher 窗口"
                xdotool windowminimize "$WINDOW_ID"
            else
                # 窗口隐藏，显示它
                echo "👁️ 显示 ConfigWatcher 窗口"
                xdotool windowmap "$WINDOW_ID"
                xdotool windowactivate "$WINDOW_ID"
                xdotool windowraise "$WINDOW_ID"
            fi
        fi
    fi
}

# 主程序
case "${1:-}" in
    setup)
        echo "======================================"
        echo "  ConfigWatcher 快捷键自动设置工具"
        echo "======================================"
        auto_setup
        echo ""
        echo "测试快捷键：按 Ctrl+Alt+Q"
        ;;
    toggle)
        toggle_window
        ;;
    *)
        toggle_window
        ;;
esac
