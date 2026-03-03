# ConfigWatcher

配置搜索工具 - 快速搜索和管理系统配置文件

## 项目简介

ConfigWatcher 是一个基于 Qt 开发的跨平台配置文件搜索工具，支持快速检索 `.ini`、`.json`、`.xml` 等格式的配置文件，并提供简洁的 UI 界面和系统托盘集成。

## 主要功能

- 🔍 **配置搜索** - 快速搜索系统中的配置文件
- 📊 **多格式支持** - 支持 `.ini`、`.json`、`.xml` 格式
- 💾 **数据库管理** - 自动导入配置文件到本地数据库
- 🖥️ **双模式界面** - 完整模式与精简模式一键切换
- 🔔 **系统托盘** - 后台运行，随时调用
- ⌨️ **全局快捷键** - `Ctrl+Alt+M` 快速切换窗口模式
- 📝 **日志记录** - 自动记录运行日志

## 技术栈

- **框架**: Qt 5 (Quick/QML + Widgets)
- **语言**: C++11
- **UI**: Qt Quick Controls 2 (Material/Basic 风格)
- **数据库**: Qt SQL
- **并发**: Qt Concurrent

## 编译要求

- Qt 5.12 或更高版本
- C++11 兼容编译器
- Linux 系统需要 X11 和 XCB 库

### Linux 依赖

```bash
# Ubuntu/Debian
sudo apt-get install qt5-default qtquickcontrols2-5-dev libx11-dev libxcb1-dev

# Fedora/RHEL
sudo dnf install qt5-qtbase-devel qt5-qtquickcontrols2-devel libX11-devel libxcb-devel
```

## 编译与运行

### 使用 qmake

```bash
# 生成 Makefile
qmake ConfigWatcher.pro

# 编译
make

# 运行
./bin/ConfigWatcher
```

### 使用 Qt Creator

1. 打开 `ConfigWatcher.pro` 项目文件
2. 选择构建配置（Debug/Release）
3. 点击运行按钮

## 项目结构

```
ConfigWatcher/
├── main.cpp                 # 程序入口
├── ConfigWatcher.pro        # qmake 项目文件
├── bin/                     # 编译输出目录
├── src/                     # 源代码
│   ├── model/              # 数据模型
│   │   └── configparser.cpp
│   └── viewmodel/          # 视图模型
│       ├── loginviewmodel.cpp
│       ├── searchviewmodel.cpp
│       └── databasemanager.cpp
├── include/                 # 头文件
├── res/                     # 资源文件
│   └── qml/                # QML 界面文件
│       ├── main.qml
│       ├── MainPage.qml
│       ├── LoginPage.qml
│       └── MiniWindow.qml
├── moc/                     # MOC 输出目录
├── obj/                     # 目标文件目录
└── rcc/                     # 资源编译输出
```

## 使用说明

### 快捷键

| 快捷键 | 功能 |
|--------|------|
| `Ctrl+Alt+M` | 切换完整模式/精简模式 |

### 系统托盘

- 双击托盘图标：打开精简模式窗口
- 右键菜单：切换模式或退出程序

### 数据存储

- **数据库**: `~/.config/Leichen/configwatcher.db`
- **日志文件**: `~/.config/log/configwatcher.log`
- **配置文件目录**: `~/.config/Leichen/`

## 版本信息

- **当前版本**: v0.0.1
- **作者**: 张宇鹏
- **构建时间**: 见程序上下文属性 `APP_BUILD_TIME`

## 许可证

本项目为 AI 编程马拉松作品。

## 贡献

欢迎提交 Issue 和 Pull Request！

## 联系方式

如有问题或建议，请通过 Issue 联系作者。
