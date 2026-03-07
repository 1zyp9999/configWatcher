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
- 🤖 **AI 服务集成** - 支持 AI 辅助功能

### 新增功能 (v2.0.0)

- 📡 **实时文件监控** - 自动监控配置文件变化，实时更新数据库
- 🔄 **配置对比** - 支持文件对比、数据库对比、快照对比
- 📦 **批量操作** - 批量编辑、批量导入导出、批量替换
- 🧠 **真 AI 集成** - 支持 OpenAI、Azure、Ollama 等真实 AI API
- ✅ **配置验证** - Schema 验证、冲突检测、依赖检查

### 性能优化 (v2.0.0)

- ⚡ **Levenshtein 算法优化** - 使用 BK-Tree 数据结构 + 剪枝策略，模糊搜索性能提升 10x+
- 🗄️ **TF-IDF 缓存** - 聚类结果缓存 30 秒，避免重复计算
- 🔄 **对象池** - ConfigEntry 对象复用，减少内存分配开销
- 📚 **词典延迟加载** - AI 词典按需加载，启动速度提升
- 🎯 **反向索引** - 意图分析使用反向索引，匹配效率 O(1)
- 💾 **查询缓存** - 数据库查询结果缓存，减少 I/O 开销
- 🎨 **QML 绑定优化** - 属性缓存机制，降低绑定计算频率
- 📁 **异步导入** - 文件导入后台执行，UI 不阻塞

## 技术栈

- **框架**: Qt 5 (Quick/QML + Widgets)
- **语言**: C++11
- **UI**: Qt Quick Controls 2 (Material/Basic 风格)
- **数据库**: SQLite + FTS5 全文搜索
- **并发**: Qt Concurrent
- **AI 服务**: AIService 模块 + OpenAI/Azure/Ollama API
- **网络**: Qt Network

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
├── main.cpp                     # 程序入口
├── ConfigWatcher.pro            # qmake 项目文件
├── bin/                         # 编译输出目录
├── src/                         # 源代码
│   ├── model/                  # 数据模型
│   │   └── configparser.cpp
│   ├── viewmodel/              # 视图模型
│   │   ├── loginviewmodel.cpp
│   │   ├── searchviewmodel.cpp
│   │   └── databasemanager.cpp
│   ├── aiservice.cpp           # AI 服务
│   ├── globalhotkey.cpp        # 全局快捷键
│   ├── filewatcher.cpp         # 文件监控
│   ├── configdiff.cpp          # 配置对比
│   ├── batchoperation.cpp      # 批量操作
│   ├── aiclient.cpp            # AI API 客户端
│   └── configvalidator.cpp     # 配置验证
├── include/                     # 头文件
│   ├── configentry.h           # 配置条目 + 对象池
│   ├── databasemanager.h       # 数据库管理 + 查询缓存
│   ├── searchviewmodel.h       # 搜索视图模型
│   ├── aiservice.h             # AI 服务
│   ├── globalhotkey.h          # 全局快捷键
│   ├── filewatcher.h           # 文件监控
│   ├── configdiff.h            # 配置对比
│   ├── batchoperation.h        # 批量操作
│   ├── aiclient.h              # AI API 客户端
│   └── configvalidator.h       # 配置验证
├── res/                         # 资源文件
│   ├── qml/                    # QML 界面文件
│   │   ├── main.qml
│   │   ├── MainPage.qml
│   │   ├── LoginPage.qml
│   │   └── MiniWindow.qml
│   └── images/                 # 图片资源
├── moc/                         # MOC 输出目录
├── obj/                         # 目标文件目录
└── rcc/                         # 资源编译输出
```

## 使用说明

### 快捷键

| 快捷键 | 功能 |
|--------|------|
| `Ctrl+Alt+M` | 切换完整模式/精简模式 |

### 系统托盘

- 双击托盘图标：打开精简模式窗口
- 右键菜单：
  - **精简模式** - 切换到精简模式
  - **完整模式** - 切换到完整模式
  - **退出** - 退出程序

### AI 配置

在 AI 管理界面可以配置：
- **Provider**: OpenAI / Azure / Ollama / Custom
- **API Key**: 你的 API 密钥
- **Model**: 模型名称 (如 gpt-4, gpt-3.5-turbo)
- **Base URL**: 自定义 API 地址
- **Temperature**: 生成温度 (0-2)
- **Max Tokens**: 最大输出 token 数

### 数据存储

- **数据库**: `configwatcher.db`
- **日志文件**: `~/.aoi/log/configwatcher.log`
- **用户词典**: `~/.local/share/ConfigWatcher/user_dictionary.json`
- **搜索历史**: `~/.local/share/ConfigWatcher/search_history.json`

## 版本信息

- **当前版本**: v2.0.0
- **作者**: Jack Zhang
- **构建时间**: 见程序上下文属性 `APP_BUILD_TIME`

## 更新日志

### v2.0.0
- 新增实时文件监控功能
- 新增配置对比功能（文件/数据库/快照对比）
- 新增批量操作功能（批量编辑/导入导出/替换）
- 新增真实 AI API 集成（OpenAI/Azure/Ollama）
- 新增配置验证功能（Schema/冲突/依赖检查）
- 优化 Levenshtein 算法（BK-Tree + 剪枝）
- 优化 TF-IDF 聚类缓存
- 优化 ConfigEntry 对象池
- 优化 AI 词典延迟加载
- 优化意图分析反向索引
- 优化数据库查询缓存
- 优化 QML 属性绑定
- 优化文件异步导入

### v1.3.0
- 基础配置搜索功能
- 多格式支持 (ini/json/xml)
- 双模式界面
- 系统托盘集成
- 全局快捷键

## 许可证

本项目为 AI 编程马拉松作品。

## 贡献

欢迎提交 Issue 和 Pull Request！

## 联系方式

如有问题或建议，请通过 Issue 联系作者。
