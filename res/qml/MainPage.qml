import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import ConfigWatcher 1.0

Item {
    id: mainPage

    property string selectedTitle: ""
    property string selectedContent: ""
    property string selectedFormat: ""
    property string appName: "ConfigWatcher"
    property string appVersion: "v0.0.1"
    property string buildTime: "未知"
    property string appAuthor: ""
    property bool aboutVisible: false
    property bool translationsVisible: false
    property bool suggestionsVisible: false
    property bool settingsVisible: false
    property string settingsFilePath: ""
    signal openFileRequested(string filePath)
    ListModel { id: settingsModel }
    ListModel { id: fileModel }
    ListModel { id: userDictModel }
    ListModel { id: historyModel }
    ListModel { id: hotSearchModel }
    ListModel { id: changeLogModel }
    property bool changeLogVisible: false

    // ===== 深色配色方案（与登录界面统一） =====
    property color primaryColor: "#2563EB"        // 主色：蓝
    property color primaryLight: "#3B82F6"        // 浅主色
    property color primaryDark: "#1D4ED8"         // 深主色
    property color accentColor: "#10B981"         // 强调色：翡翠绿
    property color warningColor: "#F59E0B"        // 警告色：琥珀
    property color dangerColor: "#EF4444"         // 危险色
    property color bgColor: "#020617"             // 页面背景（最深）
    property color cardColor: "#0f172a"           // 卡片背景（深蓝灰）
    property color surfaceColor: "#1e293b"        // 表面色（输入框/工具栏）
    property color borderColor: "#334155"         // 边框
    property color borderLightColor: "#1e293b"    // 浅边框
    property color textPrimary: "#f1f5f9"         // 主文本（亮白）
    property color textSecondary: "#94a3b8"       // 次文本（灰）
    property color textMuted: "#64748b"           // 弱文本

    // 保持旧属性兼容
    property color boxColor: cardColor
    property color boxColorSolid: cardColor
    property color textColor: textPrimary

    property int defaultWidth: 800
    property int defaultHeight: 600
    width: (parent && parent.width !== undefined && parent.width !== null) ? parseInt(parent.width) : defaultWidth
    height: (parent && parent.height !== undefined && parent.height !== null) ? parseInt(parent.height) : defaultHeight

    Component.onCompleted: {
        if (parent) {
            width = parent.width ? parseInt(parent.width) : defaultWidth
            height = parent.height ? parseInt(parent.height) : defaultHeight
        }
        if (typeof APP_VERSION !== 'undefined') mainPage.appVersion = APP_VERSION
        if (typeof APP_BUILD_TIME !== 'undefined') mainPage.buildTime = APP_BUILD_TIME
        if (typeof APP_NAME !== 'undefined') mainPage.appName = APP_NAME
        if (typeof APP_AUTHOR !== 'undefined') mainPage.appAuthor = APP_AUTHOR
    }

    // ===== 深色背景（与登录界面一致） =====
    Rectangle {
        anchors.fill: parent
        color: bgColor
        z: -2
    }
    Image {
        anchors.fill: parent
        source: "qrc:/images/login_background.png"
        fillMode: Image.AspectFill
        opacity: 0.08
        z: -1
        onStatusChanged: {
            if (status === Image.Error) visible = false;
        }
    }

    SearchViewModel {
        id: searchVM
        Component.onCompleted: {
            if (typeof searchVM.searchText === 'undefined') searchVM.searchText = ""
        }
    }

    function selectDirectory() {
        var dir = searchVM.selectDirectory();
        if (dir && dir.trim() !== "") {
            searchVM.loadConfigFiles([dir]);
        } else {
            console.warn("选择的目录为空或无效");
        }
    }

    // ===== 主内容区域 =====
    Rectangle {
        id: contentCard
        anchors.fill: parent
        anchors.margins: 16
        color: cardColor
        radius: 16
        border.color: borderColor
        border.width: 1

        // 顶部蓝色装饰条（与登录卡片一致）
        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 3
            radius: 16
            color: primaryColor
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 0
            spacing: 0

            // ===== 顶部导航栏 =====
            Rectangle {
                id: topMenu
                Layout.fillWidth: true
                height: 52
                color: "transparent"
                radius: 0

                // 底部分割线
                Rectangle {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    height: 1
                    color: borderColor
                }

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 20
                    anchors.rightMargin: 20
                    spacing: 4

                    // Logo区域
                    Text {
                        text: "CW"
                        font.pointSize: 16
                        font.bold: true
                        color: primaryColor
                    }
                    Rectangle { width: 1; height: 24; color: borderColor; Layout.leftMargin: 8; Layout.rightMargin: 8 }

                    Repeater {
                        model: [qsTr("开始"), qsTr("系统"), qsTr("修改"), qsTr("帮助"), qsTr("关于")]
                        delegate: Rectangle {
                            id: menuItemRect
                            color: "transparent"
                            radius: 8
                            Layout.preferredWidth: menuText.paintedWidth + 24
                            Layout.preferredHeight: 36

                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                property string label: modelData
                                onClicked: {
                                    if (label === qsTr("关于")) mainPage.aboutVisible = true
                                    else if (label === qsTr("修改")) mainPage.settingsVisible = true
                                    else console.log("点击菜单：", label)
                                }
                                onEntered: menuItemRect.color = surfaceColor
                                onExited: menuItemRect.color = "transparent"
                            }

                            Text {
                                id: menuText
                                text: modelData
                                anchors.centerIn: parent
                                color: textSecondary
                                font.pointSize: 13
                            }
                        }
                    }

                    // AI 管理菜单
                    Rectangle {
                        id: aiMenuBtnRect
                        color: "transparent"
                        radius: 8
                        Layout.preferredWidth: aiMenuText.paintedWidth + 24
                        Layout.preferredHeight: 36
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: mainPage.aiManagementVisible = true
                            onEntered: aiMenuBtnRect.color = surfaceColor
                            onExited: aiMenuBtnRect.color = "transparent"
                        }
                        Text {
                            id: aiMenuText
                            text: qsTr("AI 管理")
                            anchors.centerIn: parent
                            color: searchVM.aiEnabled ? "#60a5fa" : textSecondary
                            font.pointSize: 13
                        }
                    }

                    Rectangle {
                        id: fileMenuBtnRect
                        color: "transparent"
                        radius: 8
                        Layout.preferredWidth: fileMenuText.paintedWidth + 24
                        Layout.preferredHeight: 36
                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                if (DB && typeof DB.listFiles === 'function') {
                                    var files = DB.listFiles()
                                    fileModel.clear()
                                    for (var i=0;i<files.length;i++) {
                                        var p = files[i].path || ""
                                        var name = p.split('/').pop() || p
                                        name = name.replace(/\.[^/.]+$/, "")
                                        fileModel.append({path: p, format: files[i].format, display: name})
                                    }
                                    if (fileModel.count>0) {
                                        settingsFilePath = fileModel.get(0).path
                                    }
                                    mainPage.settingsVisible = true
                                } else {
                                    console.log('DB.listFiles not available; please rebuild the app')
                                }
                            }
                            onEntered: fileMenuBtnRect.color = surfaceColor
                            onExited: fileMenuBtnRect.color = "transparent"
                        }
                        Text { id: fileMenuText; text: qsTr("文件"); anchors.centerIn: parent; color: textSecondary; font.pointSize: 13 }
                    }

                    Item { Layout.fillWidth: true }

                    // 精简模式按钮
                    Rectangle {
                        id: miniModeBtnRect
                        color: "transparent"
                        radius: 8
                        Layout.preferredWidth: 36
                        Layout.preferredHeight: 36
                        ToolTip { visible: miniModeMouse.containsMouse; text: "切换精简模式 (Ctrl+Alt+M)"; timeout: 2000 }
                        MouseArea {
                            id: miniModeMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                // 通过根窗口发出信号
                                var win = mainPage.Window.window
                                if (win && typeof win.requestMiniMode === 'function') {
                                    win.requestMiniMode()
                                }
                            }
                            onEntered: miniModeBtnRect.color = surfaceColor
                            onExited: miniModeBtnRect.color = "transparent"
                        }
                        Text {
                            text: "🔽"
                            anchors.centerIn: parent
                            font.pointSize: 14
                        }
                    }

                    // 右侧版本标签
                    Text {
                        text: mainPage.appVersion
                        color: textMuted
                        font.pointSize: 10
                    }
                }
            }

            // ===== 工具栏 =====
            Rectangle {
                id: toolbarCard
                color: "#0b1222"
                radius: 0
                Layout.fillWidth: true
                implicitHeight: toolbarLayout.implicitHeight + 24
                z: 1

                // 底部分割线
                Rectangle {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    height: 1
                    color: borderColor
                }

                ColumnLayout {
                    id: toolbarLayout
                    anchors.fill: parent
                    anchors.leftMargin: 20
                    anchors.rightMargin: 20
                    anchors.topMargin: 12
                    anchors.bottomMargin: 12
                    spacing: 10

                    // ---- 第一行：快捷入口 + 下拉选择 ----
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 8

                        // 光源预设
                        Rectangle {
                            id: lightIconBtn
                            width: 34; height: 34; radius: 8
                            color: "#1e293b"
                            border.color: "#fbbf24"; border.width: 1
                            ToolTip { visible: lightMouse.containsMouse; text: "光源配置"; timeout: 1500 }
                            MouseArea {
                                id: lightMouse
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                hoverEnabled: true
                                onClicked: { openConfigByName("light") }
                                onEntered: parent.color = "#334155"
                                onExited: parent.color = "#1e293b"
                            }
                            Text { text: "💡"; anchors.centerIn: parent; font.pointSize: 16 }
                        }

                        // 相机预设
                        Rectangle {
                            id: cameraIconBtn
                            width: 34; height: 34; radius: 8
                            color: "#1e293b"
                            border.color: "#3b82f6"; border.width: 1
                            ToolTip { visible: cameraMouse.containsMouse; text: "相机配置"; timeout: 1500 }
                            MouseArea {
                                id: cameraMouse
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                hoverEnabled: true
                                onClicked: { openConfigByName("camera") }
                                onEntered: parent.color = "#334155"
                                onExited: parent.color = "#1e293b"
                            }
                            Text { text: "📷"; anchors.centerIn: parent; font.pointSize: 14 }
                        }

                        // 投影仪预设
                        Rectangle {
                            id: projectorIconBtn
                            width: 34; height: 34; radius: 8
                            color: "#1e293b"
                            border.color: "#a855f7"; border.width: 1
                            ToolTip { visible: projectorMouse.containsMouse; text: "投影仪配置"; timeout: 1500 }
                            MouseArea {
                                id: projectorMouse
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                hoverEnabled: true
                                onClicked: { openConfigByName("projector") }
                                onEntered: parent.color = "#334155"
                                onExited: parent.color = "#1e293b"
                            }
                            Text { text: "📽️"; anchors.centerIn: parent; font.pointSize: 14 }
                        }

                        // 标定预设
                        Rectangle {
                            id: calibrationIconBtn
                            width: 34; height: 34; radius: 8
                            color: "#1e293b"
                            border.color: "#10b981"; border.width: 1
                            ToolTip { visible: calibrationMouse.containsMouse; text: "标定配置"; timeout: 1500 }
                            MouseArea {
                                id: calibrationMouse
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                hoverEnabled: true
                                onClicked: { openConfigByName("calibration") }
                                onEntered: parent.color = "#334155"
                                onExited: parent.color = "#1e293b"
                            }
                            Text { text: "🎯"; anchors.centerIn: parent; font.pointSize: 14 }
                        }

                        // 硬件预设
                        Rectangle {
                            id: hardwareIconBtn
                            width: 34; height: 34; radius: 8
                            color: "#1e293b"
                            border.color: "#f97316"; border.width: 1
                            ToolTip { visible: hardwareMouse.containsMouse; text: "硬件配置"; timeout: 1500 }
                            MouseArea {
                                id: hardwareMouse
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                hoverEnabled: true
                                onClicked: { openConfigByName("hardware") }
                                onEntered: parent.color = "#334155"
                                onExited: parent.color = "#1e293b"
                            }
                            Text { text: "🔧"; anchors.centerIn: parent; font.pointSize: 14 }
                        }

                        // 用户预设
                        Rectangle {
                            id: userIconBtn
                            width: 34; height: 34; radius: 8
                            color: "#1e293b"
                            border.color: "#ec4899"; border.width: 1
                            ToolTip { visible: userMouse.containsMouse; text: "用户配置"; timeout: 1500 }
                            MouseArea {
                                id: userMouse
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                hoverEnabled: true
                                onClicked: { openConfigByName("usersetting") }
                                onEntered: parent.color = "#334155"
                                onExited: parent.color = "#1e293b"
                            }
                            Text { text: "👤"; anchors.centerIn: parent; font.pointSize: 14 }
                        }

                        Rectangle { width: 1; height: 24; color: borderColor }

                        // 配置类型标签
                        Text { text: qsTr("类型"); color: textSecondary; font.pointSize: 11 }
                        ComboBox {
                            id: configTypeCombo
                            model: ["相机", "投影", "用户配置", "调整配置", "hardware配置", "标定配置"]
                            Layout.preferredWidth: 130
                            font.pointSize: 12
                            background: Rectangle { color: surfaceColor; radius: 8; border.color: borderColor; border.width: 1 }
                            contentItem: Text { text: configTypeCombo.currentText; color: textPrimary; verticalAlignment: Text.AlignVCenter; anchors.left: parent.left; anchors.leftMargin: 10 }
                            function loadConfigByType() {
                                var type = configTypeCombo.currentText;
                                var baseDir = searchVM.selectDirectory();
                                if (!baseDir || baseDir.trim() === "") return;
                                var fileMap = {
                                    "相机": "camera", "投影": "projector",
                                    "用户配置": "usersetting", "调整配置": "adjustsetting",
                                    "hardware配置": "hardware", "标定配置": "calibration"
                                };
                                var fileName = fileMap[type];
                                if (fileName) {
                                    var ext = suffixCombo.currentText || "ini";
                                    searchVM.loadConfigFiles([baseDir + "/" + fileName + "." + ext]);
                                }
                            }
                            onCurrentIndexChanged: loadConfigByType()
                        }

                        Rectangle { width: 1; height: 24; color: borderColor }

                        Text { text: qsTr("模式"); color: textSecondary; font.pointSize: 11 }
                        ComboBox {
                            id: searchModeCombo
                            model: [qsTr("模糊搜索"), qsTr("精准搜索")]
                            Layout.preferredWidth: 110
                            font.pointSize: 12
                            currentIndex: 0
                            background: Rectangle { color: surfaceColor; radius: 8; border.color: borderColor; border.width: 1 }
                            contentItem: Text { text: searchModeCombo.currentText; color: textPrimary; verticalAlignment: Text.AlignVCenter; anchors.left: parent.left; anchors.leftMargin: 10 }
                            onCurrentIndexChanged: {
                                searchVM.searchMode = currentIndex
                                searchVM.updateSearchResults()
                            }
                        }

                        Rectangle { width: 1; height: 24; color: borderColor }

                        Text { text: qsTr("格式"); color: textSecondary; font.pointSize: 11 }
                        ComboBox {
                            id: formatFilterCombo
                            model: ["全部", "ini", "json", "xml"]
                            Layout.preferredWidth: 90
                            font.pointSize: 12
                            currentIndex: 0
                            background: Rectangle { color: surfaceColor; radius: 8; border.color: borderColor; border.width: 1 }
                            contentItem: Text { text: formatFilterCombo.currentText; color: textPrimary; verticalAlignment: Text.AlignVCenter; anchors.left: parent.left; anchors.leftMargin: 10 }
                            onCurrentIndexChanged: {
                                var val = formatFilterCombo.currentText
                                searchVM.formatFilter = (val === "全部") ? "" : val
                            }
                        }

                        Item { Layout.fillWidth: true }
                    }

                    // ---- 第二行：搜索框 + 按钮 ----
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 8

                        // 搜索输入框
                        TextField {
                            id: searchField
                            placeholderText: qsTr("搜索字段名/值（支持中文）...")
                            text: searchVM.searchText || ""
                            onAccepted: {
                                searchVM.searchText = text
                                if (searchVM.aiEnabled) searchVM.analyzeSearchQuery(text)
                                searchVM.updateSearchResults()
                            }
                            onTextChanged: {
                                if (searchVM.aiEnabled && text.length >= 2) {
                                    analyzeTimer.restart()
                                }
                            }
                            Layout.fillWidth: true
                            height: 38
                            font.pointSize: 13
                            color: textPrimary
                            placeholderTextColor: textMuted
                            background: Rectangle {
                                color: surfaceColor
                                radius: 10
                                border.width: 1
                                border.color: searchField.activeFocus ? primaryColor : borderColor
                            }
                        }

                        // 定时器：用于延迟触发 AI 分析，避免频繁调用
                        Timer {
                            id: analyzeTimer
                            interval: 300
                            onTriggered: {
                                if (searchVM.aiEnabled && searchField.text.length >= 2) {
                                    searchVM.analyzeSearchQuery(searchField.text)
                                }
                            }
                        }

                        // 搜索按钮
                        Button {
                            id: searchButton
                            text: qsTr("搜索")
                            font.pointSize: 12
                            height: 38
                            Layout.preferredWidth: 72
                            onClicked: {
                                console.log("[DEBUG] 搜索按钮被点击，searchText=", searchField.text)
                                console.log("[DEBUG] DB exists:", (typeof DB !== 'undefined'))
                                searchVM.searchText = searchField.text
                                if (searchVM.aiEnabled) searchVM.analyzeSearchQuery(searchField.text)
                                searchVM.updateSearchResults()
                                console.log("[DEBUG] 搜索结果数量:", searchVM.searchResults ? searchVM.searchResults.length : 0)
                                // 记录搜索历史
                                if (searchVM.learningEnabled && searchField.text.trim() !== "") {
                                    searchVM.recordSearch(searchField.text, searchVM.searchResults ? searchVM.searchResults.length : 0, false)
                                }
                            }
                            background: Rectangle {
                                radius: 10
                                color: primaryColor
                            }
                            contentItem: Text { text: parent.text; color: "#FFFFFF"; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter; font.pointSize: 12; font.bold: true }
                        }

                        // AI 开关按钮
                        Rectangle {
                            id: aiToggleBtn
                            width: 38; height: 38; radius: 10
                            color: searchVM.aiEnabled ? "#1e3a5f" : surfaceColor
                            border.color: searchVM.aiEnabled ? "#60a5fa" : borderColor
                            border.width: 1
                            ToolTip {
                                visible: aiToggleMouse.containsMouse
                                text: searchVM.aiEnabled ? "关闭 AI 增强" : "开启 AI 增强"
                                timeout: 2000
                            }
                            MouseArea {
                                id: aiToggleMouse
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                hoverEnabled: true
                                onClicked: searchVM.aiEnabled = !searchVM.aiEnabled
                                onEntered: { if (searchVM.aiEnabled) parent.color = "#254575"; else parent.color = "#334155" }
                                onExited: { if (searchVM.aiEnabled) parent.color = "#1e3a5f"; else parent.color = surfaceColor }
                            }
                            Text {
                                text: searchVM.aiEnabled ? "🤖" : "🤖"
                                anchors.centerIn: parent
                                font.pointSize: 16
                                opacity: searchVM.aiEnabled ? 1.0 : 0.5
                            }
                        }

                        // 联想按钮
                        Button {
                            id: suggestBtn
                            text: qsTr("联想")
                            font.pointSize: 12
                            height: 38
                            Layout.preferredWidth: 72
                            onClicked: {
                                console.log("[DEBUG] 联想按钮被点击，searchText=", searchField.text)
                                console.log("[DEBUG] DB exists:", (typeof DB !== 'undefined'))
                                searchVM.buildKeyIndex()
                                console.log("[DEBUG] keyIndex 已构建，开始请求 suggestClusters")
                                searchVM.requestSuggestClusters(searchField.text, 8, 6)
                                mainPage.suggestionsVisible = true
                                suggestModel.clear()
                            }
                            background: Rectangle { radius: 10; color: surfaceColor; border.color: primaryColor; border.width: 1 }
                            contentItem: Text { text: parent.text; color: primaryLight; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter; font.pointSize: 12 }
                        }

                        // 清空按钮
                        Button {
                            text: qsTr("清空")
                            font.pointSize: 12
                            height: 38
                            Layout.preferredWidth: 72
                            onClicked: { searchField.text = ""; searchVM.searchText = "" }
                            background: Rectangle { radius: 10; color: surfaceColor; border.color: borderColor; border.width: 1 }
                            contentItem: Text { text: parent.text; color: textSecondary; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter; font.pointSize: 12 }
                        }
                    }
                }
            }

            // ===== AI 智能分析面板 =====
            Rectangle {
                id: aiAnalysisCard
                color: "#0f172a"
                radius: 12
                Layout.fillWidth: true
                implicitHeight: aiLayout.implicitHeight + 20
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                Layout.topMargin: 8
                visible: searchVM.aiEnabled && (searchVM.aiIntent !== "" || searchVM.aiSuggestions.length > 0)
                border.color: searchVM.aiConfidence > 0.8 ? "#10B981" : (searchVM.aiConfidence > 0.5 ? "#3B82F6" : borderColor)
                border.width: 1

                ColumnLayout {
                    id: aiLayout
                    anchors.fill: parent
                    anchors.leftMargin: 16
                    anchors.rightMargin: 16
                    anchors.topMargin: 12
                    anchors.bottomMargin: 12
                    spacing: 10

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 8

                        Rectangle {
                            width: 28; height: 28; radius: 6
                            color: "#1e3a5f"
                            border.color: "#60a5fa"
                            border.width: 1
                            Text { text: "✨"; anchors.centerIn: parent; font.pointSize: 14 }
                        }

                        Rectangle {
                            color: searchVM.aiIntent === "search_key" ? "#1e3a5f" :
                                   searchVM.aiIntent === "search_value" ? "#14332a" :
                                   searchVM.aiIntent === "search_chinese" ? "#2d1f3d" :
                                   searchVM.aiIntent === "navigate" ? "#1f3a2d" : "#1e293b"
                            radius: 6; height: 28
                            Layout.preferredWidth: intentText.paintedWidth + 16
                            visible: intentText.text !== ""

                            Text {
                                id: intentText
                                text: {
                                    if (!searchVM.aiEnabled) return ""
                                    switch (searchVM.aiIntent) {
                                        case "search_key": return "🔑 搜索配置项"
                                        case "search_value": return "📊 搜索参数值"
                                        case "search_chinese": return "📝 搜索中文描述"
                                        case "navigate": return "🧭 导航意图"
                                        default: return "🔍 分析中..."
                                    }
                                }
                                anchors.centerIn: parent
                                color: textPrimary
                                font.pointSize: 11
                            }
                        }

                        Rectangle {
                            color: "transparent"
                            Layout.fillWidth: true
                            height: 28

                            RowLayout {
                                anchors.right: parent.right
                                spacing: 6

                                Text { text: "置信度："; color: textMuted; font.pointSize: 10 }

                                Rectangle {
                                    width: 100; height: 8; radius: 4
                                    color: "#1e293b"
                                    border.color: borderColor
                                    border.width: 1

                                    Rectangle {
                                        width: parent.width * (searchVM.aiConfidence || 0)
                                        height: parent.height
                                        radius: 4
                                        color: searchVM.aiConfidence > 0.8 ? "#10B981" :
                                               searchVM.aiConfidence > 0.5 ? "#3B82F6" : "#F59E0B"
                                    }
                                }

                                Text {
                                    text: Math.round((searchVM.aiConfidence || 0) * 100) + "%"
                                    color: textSecondary
                                    font.pointSize: 10
                                    Layout.preferredWidth: 40
                                }
                            }
                        }
                    }

                    Text {
                        text: searchVM.aiExplanation || ""
                        color: textSecondary
                        font.pointSize: 11
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                        visible: text !== ""
                    }

                    Rectangle {
                        color: "transparent"
                        Layout.fillWidth: true
                        implicitHeight: suggestionsRow.implicitHeight
                        visible: suggestionsRow.children.length > 0

                        RowLayout {
                            id: suggestionsRow
                            anchors.left: parent.left
                            anchors.right: parent.right
                            spacing: 6

                            Repeater {
                                model: searchVM.aiSuggestions

                                delegate: Rectangle {
                                    id: suggestItem
                                    color: "transparent"
                                    radius: 6
                                    height: 28
                                    Layout.preferredWidth: suggestText.paintedWidth + 16
                                    border.color: "#3B82F6"
                                    border.width: 1

                                    MouseArea {
                                        anchors.fill: parent
                                        cursorShape: Qt.PointingHandCursor
                                        onClicked: {
                                            searchField.text = modelData.text
                                            searchVM.searchText = modelData.text
                                            searchVM.updateSearchResults()
                                        }
                                        onEntered: suggestItem.color = "#1e3a5f"
                                        onExited: suggestItem.color = "transparent"
                                    }

                                    Text {
                                        id: suggestText
                                        text: modelData.text
                                        color: modelData.type === "exact" ? primaryLight :
                                               modelData.type === "synonym" ? "#6ee7b7" : "#a78bfa"
                                        anchors.centerIn: parent
                                        font.pointSize: 11
                                    }

                                    Rectangle {
                                        anchors.left: parent.right
                                        anchors.leftMargin: 2
                                        anchors.verticalCenter: parent.verticalCenter
                                        width: 6; height: 6; radius: 3
                                        color: modelData.type === "exact" ? primaryColor :
                                               modelData.type === "synonym" ? "#10B981" : "#8b5cf6"
                                        visible: index === 0
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // ===== 进度条 =====
            ProgressBar {
                Layout.fillWidth: true
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                value: (searchVM.loadProgress || 0) / 100
                visible: searchVM.isLoading || false
                height: 4
                background: Rectangle { color: borderLightColor; radius: 2 }
                contentItem: Rectangle {
                    color: primaryColor
                    radius: 2
                }
            }

            // ===== 内容区域：结果列表 =====
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                Layout.bottomMargin: 0
                color: "transparent"

                RowLayout {
                    anchors.fill: parent
                    spacing: 0
                    ListView {
                        id: resultListView
                        width: parent.width
                        height: parent.height
                        model: searchVM.searchResults || []
                        spacing: 4
                        clip: true

                        // 滚动条
                        ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded }

                        delegate: Rectangle {
                            id: resultCard
                            width: resultListView.width - 8
                            height: expandedCol.implicitHeight + 20
                            radius: 12
                            color: resultCardMA.containsMouse ? "#171C28" : "#111621"
                            border.color: resultCardMA.containsMouse ? Qt.rgba(37/255, 99/255, 235/255, 0.3) : Qt.rgba(1,1,1,0.04)
                            border.width: 1
                            x: 4

                            property bool resultCardExpanded: false

                            Behavior on height { NumberAnimation { duration: 180; easing.type: Easing.OutCubic } }
                            Behavior on color { ColorAnimation { duration: 120 } }
                            Behavior on border.color { ColorAnimation { duration: 120 } }

                            MouseArea {
                                id: resultCardMA
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: resultCard.resultCardExpanded = !resultCard.resultCardExpanded
                            }

                            ColumnLayout {
                                id: expandedCol
                                anchors.left: parent.left; anchors.right: parent.right
                                anchors.top: parent.top
                                anchors.margins: 12
                                spacing: 8

                                // ===== 主行 =====
                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 10

                                    // 格式标签
                                    Rectangle {
                                        width: 38; height: 20; radius: 10
                                        color: {
                                            var fmt = (modelData.format || modelData.fileFormat || "").toLowerCase()
                                            if (fmt === "ini") return Qt.rgba(34/255,197/255,94/255, 0.15)
                                            if (fmt === "json") return Qt.rgba(245/255,158/255,11/255, 0.15)
                                            if (fmt === "xml") return Qt.rgba(139/255,92/255,246/255, 0.15)
                                            return Qt.rgba(1,1,1,0.06)
                                        }
                                        Text {
                                            anchors.centerIn: parent
                                            text: (modelData.format || modelData.fileFormat || "?").toUpperCase()
                                            font.pointSize: 8; font.bold: true
                                            color: {
                                                var fmt = (modelData.format || modelData.fileFormat || "").toLowerCase()
                                                if (fmt === "ini") return "#4ADE80"
                                                if (fmt === "json") return "#FBBF24"
                                                if (fmt === "xml") return "#A78BFA"
                                                return "#64748B"
                                            }
                                        }
                                    }

                                    // 参数名
                                    Text {
                                        text: modelData.key || modelData.name || "未知字段"
                                        color: "#E2E8F0"
                                        font.pointSize: 12
                                        font.bold: true
                                        font.family: "monospace"
                                        elide: Text.ElideRight
                                        Layout.preferredWidth: resultListView.width * 0.28
                                    }

                                    // 中文名（如果有）
                                    Text {
                                        visible: (modelData.chineseKey || modelData.chinese || "") !== "" && (modelData.chineseKey || modelData.chinese || "") !== (modelData.key || "")
                                        text: modelData.chineseKey || modelData.chinese || ""
                                        color: "#60A5FA"
                                        font.pointSize: 11
                                        elide: Text.ElideRight
                                        Layout.maximumWidth: 180
                                    }

                                    Item { Layout.fillWidth: true }

                                    // 值预览
                                    Rectangle {
                                        Layout.maximumWidth: 260
                                        height: 24; radius: 6
                                        width: valPreviewText.implicitWidth + 16
                                        color: Qt.rgba(1,1,1,0.04)
                                        Text {
                                            id: valPreviewText
                                            anchors.centerIn: parent
                                            text: {
                                                var v = modelData.value || modelData.raw_value || ""
                                                return v.length > 40 ? v.substring(0, 40) + "…" : v
                                            }
                                            color: "#94A3B8"; font.pointSize: 10; font.family: "monospace"
                                            elide: Text.ElideRight
                                            maximumLineCount: 1
                                        }
                                    }

                                    // 展开指示器
                                    Text {
                                        text: resultCard.resultCardExpanded ? "▲" : "▼"
                                        color: "#475569"; font.pointSize: 9
                                    }
                                }

                                // ===== 展开区域 =====
                                Rectangle {
                                    visible: resultCard.resultCardExpanded
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: visible ? expandedContent.implicitHeight + 24 : 0
                                    radius: 10
                                    color: "#0D1117"
                                    border.color: Qt.rgba(1,1,1,0.04)
                                    clip: true

                                    Behavior on Layout.preferredHeight { NumberAnimation { duration: 150; easing.type: Easing.OutCubic } }

                                    ColumnLayout {
                                        id: expandedContent
                                        anchors.fill: parent; anchors.margins: 12
                                        spacing: 8

                                        // 值行
                                        RowLayout {
                                            spacing: 8
                                            Text { text: "值"; color: "#475569"; font.pointSize: 10; font.bold: true; Layout.preferredWidth: 60 }
                                            Rectangle {
                                                Layout.fillWidth: true; height: 32; radius: 8
                                                color: Qt.rgba(1,1,1,0.03)
                                                border.color: Qt.rgba(1,1,1,0.06)
                                                Text {
                                                    anchors.fill: parent; anchors.leftMargin: 10; anchors.rightMargin: 10
                                                    verticalAlignment: Text.AlignVCenter
                                                    text: modelData.value || modelData.raw_value || "(空)"
                                                    color: "#F1F5F9"; font.pointSize: 11; font.family: "monospace"
                                                    elide: Text.ElideRight
                                                }
                                            }
                                        }

                                        // 中文名行
                                        RowLayout {
                                            visible: (modelData.chineseKey || modelData.chinese || "") !== ""
                                            spacing: 8
                                            Text { text: "中文"; color: "#475569"; font.pointSize: 10; font.bold: true; Layout.preferredWidth: 60 }
                                            Text {
                                                text: modelData.chineseKey || modelData.chinese || ""
                                                color: "#60A5FA"; font.pointSize: 11
                                                Layout.fillWidth: true; elide: Text.ElideRight
                                            }
                                        }

                                        // 文件路径行
                                        RowLayout {
                                            spacing: 8
                                            Text { text: "文件"; color: "#475569"; font.pointSize: 10; font.bold: true; Layout.preferredWidth: 60 }
                                            Text {
                                                text: {
                                                    var fp = modelData.filePath || ""
                                                    return fp.split('/').pop() || fp
                                                }
                                                color: "#94A3B8"; font.pointSize: 10
                                                elide: Text.ElideMiddle; Layout.fillWidth: true
                                            }
                                        }

                                        // 操作按钮行
                                        RowLayout {
                                            Layout.topMargin: 4
                                            spacing: 8

                                            // 复制值
                                            Rectangle {
                                                width: copyValText.implicitWidth + 20; height: 30; radius: 8
                                                color: copyValMA.containsMouse ? "#1E293B" : "transparent"
                                                border.color: Qt.rgba(1,1,1,0.08); border.width: 1
                                                Text { id: copyValText; anchors.centerIn: parent; text: "📋 复制值"; color: copyValMA.containsMouse ? "#E2E8F0" : "#64748B"; font.pointSize: 10 }
                                                MouseArea {
                                                    id: copyValMA; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor
                                                    onClicked: {
                                                        mainPage.selectedTitle = "值: " + (modelData.key || "")
                                                        mainPage.selectedContent = modelData.value || modelData.raw_value || ""
                                                        mainPage.selectedFormat = modelData.format || modelData.fileFormat || ""
                                                    }
                                                }
                                            }

                                            // 打开文件
                                            Rectangle {
                                                width: openFileText.implicitWidth + 20; height: 30; radius: 8
                                                color: openFileMA.containsMouse ? "#1E293B" : "transparent"
                                                border.color: Qt.rgba(1,1,1,0.08); border.width: 1
                                                Text { id: openFileText; anchors.centerIn: parent; text: "📂 打开文件"; color: openFileMA.containsMouse ? "#E2E8F0" : "#64748B"; font.pointSize: 10 }
                                                MouseArea {
                                                    id: openFileMA; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor
                                                    onClicked: mainPage.openFileRequested(modelData.filePath || "")
                                                }
                                            }

                                            // 编辑文件
                                            Rectangle {
                                                width: editFileText.implicitWidth + 20; height: 30; radius: 8
                                                color: editFileMA.containsMouse ? "#1E293B" : "transparent"
                                                border.color: Qt.rgba(1,1,1,0.08); border.width: 1
                                                Text { id: editFileText; anchors.centerIn: parent; text: "⚙ 编辑"; color: editFileMA.containsMouse ? "#E2E8F0" : "#64748B"; font.pointSize: 10 }
                                                MouseArea {
                                                    id: editFileMA; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor
                                                    onClicked: {
                                                        var fp = modelData.filePath || ""
                                                        if (fp) {
                                                            var fname = fp.split('/').pop().replace(/\.[^/.]+$/, "")
                                                            openConfigByName(fname)
                                                        }
                                                    }
                                                }
                                            }

                                            Item { Layout.fillWidth: true }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // 空状态提示
                Column {
                    anchors.centerIn: parent
                    spacing: 12
                    visible: resultListView.count === 0 && !(searchVM.isLoading || false)

                    Text { text: "🔍"; font.pointSize: 40; anchors.horizontalCenter: parent.horizontalCenter; opacity: 0.3 }
                    Text {
                        text: qsTr("暂无匹配结果")
                        font.pointSize: 15; color: "#475569"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        text: qsTr("试试输入关键词搜索配置项")
                        font.pointSize: 11; color: "#334155"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                // 加载中提示
                Column {
                    anchors.centerIn: parent
                    spacing: 12
                    visible: searchVM.isLoading || false

                    BusyIndicator { anchors.horizontalCenter: parent.horizontalCenter; running: true; width: 40; height: 40 }
                    Text {
                        text: qsTr("正在加载配置文件...")
                        font.pointSize: 14; color: "#64748B"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }

            // ===== 底部状态栏 =====
            Rectangle {
                Layout.fillWidth: true
                height: 36
                color: "#0b1222"
                radius: 0

                // 顶部分割线
                Rectangle {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    height: 1
                    color: borderColor
                }

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 20
                    anchors.rightMargin: 20

                    // 左侧小蓝点指示
                    Rectangle { width: 6; height: 6; radius: 3; color: primaryColor }
                    Text {
                        text: qsTr("就绪")
                        color: textSecondary
                        font.pointSize: 10
                    }
                    Item { Layout.fillWidth: true }
                    Text {
                        text: qsTr("共 %1 个配置项 | 匹配 %2 个").arg(searchVM.searchResults ? searchVM.searchResults.length : 0).arg(searchVM.searchResults ? searchVM.searchResults.length : 0)
                        anchors.verticalCenter: parent.verticalCenter
                        font.pointSize: 10
                        color: textSecondary
                        horizontalAlignment: Text.AlignRight
                    }
                }
            }
        }
    }

    // ===== 关于弹窗 =====
    Rectangle {
        id: aboutOverlay
        anchors.fill: parent
        color: "#000000AA"
        visible: mainPage.aboutVisible
        z: 999
        MouseArea { anchors.fill: parent; onClicked: mainPage.aboutVisible = false }
        Rectangle {
            id: aboutBox
            width: 440
            height: aboutContent.implicitHeight + 40
            anchors.centerIn: parent
            radius: 16
            color: cardColor
            border.color: borderColor
            border.width: 1
            ColumnLayout {
                id: aboutContent
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.margins: 24
                spacing: 10

                // Logo
                Rectangle {
                    Layout.alignment: Qt.AlignHCenter
                    width: 56; height: 56; radius: 28
                    color: primaryColor
                    Text { text: "CW"; anchors.centerIn: parent; color: "#FFFFFF"; font.pointSize: 18; font.bold: true }
                }

                Text {
                    text: mainPage.appName
                    font.pointSize: 16
                    color: textPrimary
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    Layout.fillWidth: true
                    wrapMode: Text.WordWrap
                    horizontalAlignment: Text.AlignHCenter
                }
                Text {
                    text: qsTr("版本：") + mainPage.appVersion
                    color: textSecondary
                    font.pointSize: 12
                    Layout.fillWidth: true
                    wrapMode: Text.WordWrap
                    horizontalAlignment: Text.AlignHCenter
                }
                Text {
                    text: qsTr("最近编译时间：") + mainPage.buildTime
                    color: textSecondary
                    font.pointSize: 12
                    Layout.fillWidth: true
                    wrapMode: Text.WordWrap
                    horizontalAlignment: Text.AlignHCenter
                }
                Text {
                    text: qsTr("作者：") + mainPage.appAuthor
                    color: textSecondary
                    font.pointSize: 11
                    Layout.fillWidth: true
                    wrapMode: Text.WordWrap
                    horizontalAlignment: Text.AlignHCenter
                }
                Item { Layout.fillHeight: true }
                RowLayout { Layout.alignment: Qt.AlignHCenter
                    Button {
                        text: qsTr("关闭")
                        onClicked: mainPage.aboutVisible = false
                        Layout.preferredWidth: 100
                        Layout.preferredHeight: 36
                        background: Rectangle { radius: 10; color: primaryColor }
                        contentItem: Text { text: parent.text; color: "#FFFFFF"; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter; font.bold: true }
                    }
                }
            }
        }
    }

    // ===== 翻译管理弹窗 =====
    Rectangle {
        id: translationsOverlay
        anchors.fill: parent
        color: "#000000AA"
        visible: mainPage.translationsVisible
        z: 1000
        MouseArea { anchors.fill: parent; onClicked: mainPage.translationsVisible = false }

        Rectangle {
            id: transBox
            width: Math.min(parent.width - 80, 760)
            height: Math.min(parent.height - 120, 520)
            anchors.centerIn: parent
            radius: 16
            color: cardColor
            border.color: borderColor
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 10

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12
                    Text { text: qsTr("翻译管理"); color: textPrimary; font.pointSize: 16; font.bold: true; Layout.alignment: Qt.AlignLeft }
                    Item { Layout.fillWidth: true }
                    Button { text: qsTr("刷新"); onClicked: reloadTranslations(); background: Rectangle { color: surfaceColor; radius: 10; border.color: borderColor; border.width: 1 } contentItem: Text { text: parent.text; color: textPrimary; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter } }
                    Button { text: qsTr("应用翻译"); onClicked: { DB.applyTranslationsToParameters(); reloadTranslations(); } background: Rectangle { color: primaryColor; radius: 10 } contentItem: Text { text: parent.text; color: "#FFFFFF"; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter; font.bold: true } }
                    Button { text: qsTr("关闭"); onClicked: mainPage.translationsVisible = false; background: Rectangle { color: surfaceColor; radius: 10; border.color: borderColor; border.width: 1 } contentItem: Text { text: parent.text; color: textPrimary; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter } }
                }

                ListModel { id: translationListModel }

                Flickable {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height - 120
                    contentWidth: parent.width
                    clip: true

                    Column {
                        id: listColumn
                        width: parent.width
                        spacing: 6
                        Repeater {
                            model: translationListModel
                            delegate: Rectangle {
                                width: parent.width - 24
                                height: 46
                                radius: 10
                                color: surfaceColor
                                border.color: borderColor
                                RowLayout {
                                    anchors.fill: parent
                                    anchors.margins: 10
                                    spacing: 8
                                    Text { text: model.key; color: textSecondary; font.pointSize: 12; Layout.preferredWidth: 220; elide: Text.ElideRight }
                                    TextField {
                                        id: tf
                                        text: model.chinese
                                        placeholderText: qsTr("输入中文翻译...")
                                        Layout.fillWidth: true
                                        height: 32
                                        color: textPrimary
                                        background: Rectangle { color: cardColor; radius: 8; border.color: borderColor; border.width: 1 }
                                        onAccepted: {
                                            DB.setTranslation(model.key, text)
                                            translationListModel.setProperty(index, "chinese", text)
                                        }
                                    }
                                    Button {
                                        text: qsTr("保存")
                                        onClicked: { DB.setTranslation(model.key, tf.text); translationListModel.setProperty(index, "chinese", tf.text) }
                                        Layout.preferredWidth: 64
                                        height: 32
                                        background: Rectangle { color: primaryColor; radius: 8 }
                                        contentItem: Text { text: parent.text; color: "#FFFFFF"; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter }
                                    }
                                }
                            }
                        }
                    }
                }

                Component.onCompleted: reloadTranslations()
                function reloadTranslations() {
                    translationListModel.clear()
                    var arr = []
                    try { arr = DB.listTranslations() } catch(e) { arr = [] }
                    for (var i=0;i<arr.length;i++) { translationListModel.append({ key: arr[i].key, chinese: arr[i].chinese }) }
                }
            }
        }
    }

    ListModel { id: suggestModel }
    Popup {
        id: suggestionsPopup
        z: 10000
        parent: mainPage
        modal: false
        focus: true
        width: Math.min(contentCard.width * 0.6, 560)
        height: 320
        visible: mainPage.suggestionsVisible
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        anchors.centerIn: parent

        Component.onCompleted: {
            console.log("[QML] suggestionsPopup ready, z=", suggestionsPopup.z)
            console.log("[QML] popup size:", width, "x", height)
        }

        Rectangle {
            id: suggestionsShadow
            anchors.fill: parent
            anchors.margins: 6
            color: "#00000055"
            radius: 18
            z: 0
        }

        Rectangle {
            id: suggestionsBg
            anchors.fill: parent
            color: cardColor
            radius: 16
            border.color: borderColor
            border.width: 1
            z: 1
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 10

                Text {
                    text: qsTr("联想结果")
                    color: textPrimary
                    font.pointSize: 16
                    font.bold: true
                    Layout.fillWidth: true
                }

                ListView {
                    id: suggestListView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: suggestModel
                    clip: true
                    boundsBehavior: Flickable.StopAtBounds
                    spacing: 10
                    ScrollBar.vertical: ScrollBar {
                        policy: ScrollBar.AlwaysOn
                        width: 6
                        anchors.right: parent.right
                        visible: suggestListView.contentHeight > suggestListView.height
                    }

                    delegate: Rectangle {
                        width: suggestListView.width
                        color: surfaceColor
                        radius: 12
                        border.color: borderColor
                        border.width: 1
                        property var clusterData: model
                        property string clusterName: clusterData.cluster || clusterData.k || ""
                        property var clusterItems: (function() {
                            try {
                                if (clusterData.items && Array.isArray(clusterData.items)) return clusterData.items
                                if (clusterData.itemsJson) return JSON.parse(clusterData.itemsJson)
                            } catch(e) {
                                console.warn("解析cluster items失败:", e)
                            }
                            return clusterData.k ? [clusterData.k] : []
                        })()

                        implicitHeight: clusterContent.implicitHeight + 20

                        ColumnLayout {
                            id: clusterContent
                            anchors.fill: parent
                            anchors.margins: 12
                            spacing: 8

                            Text {
                                text: clusterName || qsTr("未命名聚类")
                                color: textPrimary
                                font.pointSize: 13
                                font.bold: true
                                Layout.fillWidth: true
                                wrapMode: Text.NoWrap
                                elide: Text.ElideRight
                            }

                            Column {
                                id: itemsColumn
                                width: parent.width
                                spacing: 6

                                Repeater {
                                    model: clusterItems
                                    delegate: Rectangle {
                                        width: parent.width
                                        height: 40
                                        color: cardColor
                                        radius: 8
                                        border.color: borderColor
                                        border.width: 1

                                        RowLayout {
                                            anchors.fill: parent
                                            anchors.margins: 8
                                            spacing: 8
                                            Layout.preferredHeight: parent.height

                                            Text {
                                                text: modelData || ""
                                                color: textPrimary
                                                font.pointSize: 12
                                                Layout.preferredWidth: Math.max(0, parent.width - 160)
                                                elide: Text.ElideRight
                                                verticalAlignment: Text.AlignVCenter
                                            }

                                            Button {
                                                text: qsTr("填充")
                                                Layout.preferredWidth: 60
                                                Layout.alignment: Qt.AlignVCenter
                                                height: 28
                                                onClicked: {
                                                    searchField.text = modelData || "";
                                                    mainPage.selectedTitle = qsTr("键: ") + (modelData || "");
                                                    mainPage.selectedContent = "";
                                                    mainPage.suggestionsVisible = false;
                                                    suggestModel.clear();
                                                }
                                                background: Rectangle {
                                                    radius: 8; color: "#1e3a5f"; border.color: "#2563EB"; border.width: 1
                                                }
                                                contentItem: Text { text: parent.text; color: "#60a5fa"; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter; font.pointSize: 11 }
                                            }

                                            Button {
                                                text: qsTr("搜索")
                                                Layout.preferredWidth: 60
                                                Layout.alignment: Qt.AlignVCenter
                                                height: 28
                                                onClicked: {
                                                    searchField.text = modelData || "";
                                                    searchVM.searchText = modelData || "";
                                                    searchVM.updateSearchResults();
                                                    mainPage.suggestionsVisible = false;
                                                    suggestModel.clear();
                                                }
                                                background: Rectangle { radius: 8; color: primaryColor }
                                                contentItem: Text { text: parent.text; color: "#FFFFFF"; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter; font.pointSize: 11; font.bold: true }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                RowLayout {
                    Layout.alignment: Qt.AlignRight
                    Layout.fillWidth: true
                    anchors.margins: 8

                    Button {
                        text: qsTr("关闭")
                        onClicked: {
                            mainPage.suggestionsVisible = false;
                            suggestModel.clear();
                            suggestionsPopup.close();
                        }
                        Layout.preferredWidth: 80
                        height: 34
                        background: Rectangle {
                            radius: 10;
                            color: surfaceColor;
                            border.color: borderColor;
                            border.width: 1
                        }
                        contentItem: Text {
                            text: parent.text;
                            color: textPrimary;
                            anchors.fill: parent;
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }
            }
        }
    }

    Connections {
        target: searchVM
        function onSuggestClustersReady(clusters) {
            console.log("[QML] onSuggestClustersReady received, clusters len:", clusters ? clusters.length : 0)
            try { 
                console.log("[QML] clusters preview:", JSON.stringify(clusters && clusters.length ? clusters.slice(0,3) : clusters)) 
            } catch(e) {}
            
            suggestModel.clear()
            if (!clusters || !Array.isArray(clusters)) { 
                mainPage.suggestionsVisible = false; 
                return 
            }

            for (var ci=0; ci<clusters.length; ++ci) {
                var c = clusters[ci] || {}
                var items = c.items || []
                var cleanItems = []
                if (Array.isArray(items)) {
                    for (var ji=0; ji<items.length; ++ji) {
                        cleanItems.push(items[ji] === null || typeof items[ji] === 'undefined' ? "" : String(items[ji]));
                    }
                }
                suggestModel.append({ 
                    cluster: c.cluster || "", 
                    items: cleanItems,
                    itemsJson: JSON.stringify(cleanItems),
                    k: c.k || ""
                })
            }

            try {
                console.log("[QML] suggestModel.count=", suggestModel.count)
                for (var ii=0; ii<suggestModel.count; ++ii) {
                    var item = suggestModel.get(ii);
                    console.log("[QML] suggestModel[", ii, "]=", JSON.stringify({
                        cluster: item.cluster,
                        itemsLength: item.items ? item.items.length : 0,
                        itemsJson: item.itemsJson
                    }))
                }
            } catch(e) { 
                console.warn("调试输出model失败:", e) 
            }

            mainPage.suggestionsVisible = suggestModel.count > 0
            if (mainPage.suggestionsVisible) {
                if (!suggestionsPopup.opened) {
                    suggestionsPopup.open();
                    console.log("[QML] 弹窗已打开，visible=", suggestionsPopup.visible)
                }
            } else {
                if (suggestionsPopup.opened) {
                    suggestionsPopup.close();
                }
            }
        }
    }

    Connections {
        target: mainPage
        function onOpenFileRequested(filePath) {
            console.log("[QML] openFileRequested ->", filePath)
            if (typeof searchVM.openFileRequested === 'function') {
                searchVM.openFileRequested(filePath)
            } else if (typeof searchVM.openConfigFile === 'function') {
                searchVM.openConfigFile(filePath)
            } else {
                console.warn("searchVM 未暴露打开文件函数")
            }
        }
    }

    Shortcut { sequence: "Ctrl+R"; onActivated: suggestBtn.clicked() }

    property var lastClusters: []

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 12
        spacing: 6
        Text { id: debugKeyCount; visible: false }
        Text { id: debugClusters; visible: false }
    }

    // ===== 设置弹窗（重新设计） =====
    Rectangle {
        id: settingsOverlay
        anchors.fill: parent
        color: "#000000BB"
        visible: mainPage.settingsVisible
        z: 1001
        MouseArea { anchors.fill: parent; onClicked: mainPage.settingsVisible = false }

        // 弹窗主体
        Rectangle {
            id: settingsBox
            width: Math.min(parent.width - 80, 960)
            height: Math.min(parent.height - 60, 720)
            anchors.centerIn: parent
            radius: 20
            color: "#1A1D23"
            border.color: Qt.rgba(1,1,1,0.08)
            border.width: 1
            // 阻止点击穿透
            MouseArea { anchors.fill: parent; onClicked: {} }

            // 左侧装饰条
            Rectangle {
                width: 4; height: parent.height - 40; radius: 2
                anchors.left: parent.left; anchors.leftMargin: 0
                anchors.verticalCenter: parent.verticalCenter
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#2563EB" }
                    GradientStop { position: 0.5; color: "#7C3AED" }
                    GradientStop { position: 1.0; color: "#2563EB" }
                }
            }

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 0

                // ===== 顶部标题栏 =====
                RowLayout {
                    Layout.fillWidth: true
                    Layout.bottomMargin: 16
                    spacing: 12

                    // 图标
                    Rectangle {
                        width: 40; height: 40; radius: 12
                        gradient: Gradient {
                            orientation: Gradient.Horizontal
                            GradientStop { position: 0; color: "#2563EB" }
                            GradientStop { position: 1; color: "#7C3AED" }
                        }
                        Text { text: "⚙"; anchors.centerIn: parent; font.pointSize: 18; color: "white" }
                    }

                    ColumnLayout {
                        spacing: 2
                        Text {
                            text: qsTr("配置文件编辑器")
                            color: "#F1F5F9"
                            font.pointSize: 17
                            font.bold: true
                        }
                        Text {
                            text: mainPage.settingsFilePath
                                  ? mainPage.settingsFilePath.split('/').pop()
                                  : qsTr("未选择文件")
                            color: "#64748B"
                            font.pointSize: 10
                            elide: Text.ElideMiddle
                            Layout.maximumWidth: 400
                        }
                    }

                    Item { Layout.fillWidth: true }

                    // 条目计数徽章
                    Rectangle {
                        visible: settingsModel.count > 0
                        width: countLabel.implicitWidth + 16; height: 26; radius: 13
                        color: Qt.rgba(37/255, 99/255, 235/255, 0.15)
                        Text {
                            id: countLabel
                            anchors.centerIn: parent
                            text: settingsModel.count + " 项"
                            color: "#60A5FA"; font.pointSize: 10; font.bold: true
                        }
                    }

                    // 关闭按钮
                    Rectangle {
                        width: 36; height: 36; radius: 18
                        color: closeMA.containsMouse ? "#374151" : "transparent"
                        Text { text: "✕"; anchors.centerIn: parent; color: "#94A3B8"; font.pointSize: 14 }
                        MouseArea {
                            id: closeMA; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor
                            onClicked: mainPage.settingsVisible = false
                        }
                    }
                }

                // ===== 文件选择栏 =====
                Rectangle {
                    Layout.fillWidth: true
                    height: 48
                    radius: 12
                    color: "#0F1117"
                    border.color: Qt.rgba(1,1,1,0.06)
                    Layout.bottomMargin: 12

                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 12; anchors.rightMargin: 12
                        spacing: 10

                        Text { text: "📁"; font.pointSize: 14 }

                        ComboBox {
                            id: fileComboBox
                            model: fileModel
                            Layout.fillWidth: true
                            Layout.preferredHeight: 36
                            textRole: "display"
                            currentIndex: -1
                            font.pointSize: 12

                            background: Rectangle {
                                color: "#1E2028"
                                radius: 8
                                border.color: Qt.rgba(1,1,1,0.08)
                                border.width: 1
                            }
                            contentItem: Text {
                                text: fileComboBox.currentText || qsTr("请选择配置文件...")
                                color: fileComboBox.currentText ? "#E2E8F0" : "#475569"
                                verticalAlignment: Text.AlignVCenter
                                elide: Text.ElideMiddle
                                leftPadding: 10
                                font.pointSize: 12
                            }

                            popup: Popup {
                                y: fileComboBox.height + 4
                                width: fileComboBox.width
                                implicitHeight: Math.min(contentItem.implicitHeight + 8, 280)
                                padding: 4
                                background: Rectangle {
                                    color: "#1E2028"
                                    radius: 10
                                    border.color: Qt.rgba(1,1,1,0.1)
                                    border.width: 1
                                    layer.enabled: true
                                }
                                contentItem: ListView {
                                    id: fileListView
                                    clip: true
                                    implicitHeight: contentHeight
                                    model: fileModel
                                    spacing: 2
                                    delegate: Rectangle {
                                        width: fileListView.width
                                        height: 38
                                        radius: 8
                                        color: fileDelegateMA.containsMouse ? "#2A2D35" : "transparent"
                                        RowLayout {
                                            anchors.fill: parent; anchors.leftMargin: 10; anchors.rightMargin: 10; spacing: 8
                                            // 文件类型色块
                                            Rectangle {
                                                width: 6; height: 6; radius: 3
                                                color: {
                                                    var fmt = model.format || ""
                                                    if (fmt === "ini") return "#22C55E"
                                                    if (fmt === "json") return "#F59E0B"
                                                    if (fmt === "xml") return "#8B5CF6"
                                                    return "#64748B"
                                                }
                                            }
                                            Text {
                                                text: model.display || ""
                                                color: "#E2E8F0"; font.pointSize: 11
                                                elide: Text.ElideRight; Layout.fillWidth: true
                                            }
                                            Text {
                                                text: "." + (model.format || "")
                                                color: "#475569"; font.pointSize: 9
                                            }
                                        }
                                        MouseArea {
                                            id: fileDelegateMA; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor
                                            onClicked: { fileComboBox.currentIndex = index; fileComboBox.popup.close(); }
                                        }
                                    }
                                }
                            }

                            onCurrentIndexChanged: {
                                if (currentIndex < 0) return
                                var it = fileModel.get(currentIndex)
                                if (it && it.path) {
                                    settingsFilePath = it.path
                                    loadSettingsFromFile(settingsFilePath)
                                    if (mainPage.changeLogVisible) loadChangeLogs()
                                }
                            }
                        }

                        // 刷新按钮
                        Rectangle {
                            width: 36; height: 36; radius: 10
                            color: refreshMA.containsMouse ? "#1E293B" : "transparent"
                            Text { text: "🔄"; anchors.centerIn: parent; font.pointSize: 13 }
                            ToolTip { visible: refreshMA.containsMouse; text: "刷新文件列表"; delay: 400 }
                            MouseArea {
                                id: refreshMA; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    if (DB && typeof DB.listFiles === 'function') {
                                        var files = DB.listFiles()
                                        fileModel.clear()
                                        for (var i=0; i<files.length; i++) {
                                            var p = files[i].path || ""
                                            var name = p.split('/').pop() || p
                                            name = name.replace(/\.[^/.]+$/, "")
                                            fileModel.append({ path: p, format: files[i].format, display: name })
                                        }
                                        if (fileModel.count > 0 && fileComboBox.currentIndex < 0) {
                                            fileComboBox.currentIndex = 0
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // ===== 选项卡栏：编辑 / 修改记录 =====
                RowLayout {
                    Layout.fillWidth: true
                    Layout.bottomMargin: 8
                    spacing: 0

                    Repeater {
                        model: [qsTr("✏️ 编辑"), qsTr("📋 修改记录")]
                        Rectangle {
                            Layout.preferredWidth: 130; height: 36; radius: 8
                            color: {
                                var isActive = (index === 0 && !mainPage.changeLogVisible) || (index === 1 && mainPage.changeLogVisible)
                                return isActive ? "#2563EB" : "transparent"
                            }
                            Text {
                                anchors.centerIn: parent
                                text: modelData
                                color: {
                                    var isActive = (index === 0 && !mainPage.changeLogVisible) || (index === 1 && mainPage.changeLogVisible)
                                    return isActive ? "white" : "#64748B"
                                }
                                font.pointSize: 11; font.bold: true
                            }
                            MouseArea {
                                anchors.fill: parent; cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    if (index === 0) mainPage.changeLogVisible = false
                                    else { mainPage.changeLogVisible = true; loadChangeLogs() }
                                }
                            }
                        }
                    }

                    Item { Layout.fillWidth: true }

                    // 文件路径完整显示
                    Text {
                        text: mainPage.settingsFilePath || ""
                        color: "#475569"; font.pointSize: 9
                        elide: Text.ElideMiddle
                        Layout.maximumWidth: 350
                    }
                }

                Rectangle { Layout.fillWidth: true; height: 1; color: Qt.rgba(1,1,1,0.06); Layout.bottomMargin: 4 }

                // ===== 编辑面板 =====
                Item {
                    visible: !mainPage.changeLogVisible
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ColumnLayout {
                        anchors.fill: parent
                        spacing: 0

                        // 表头
                        Rectangle {
                            Layout.fillWidth: true; height: 36; radius: 8
                            color: Qt.rgba(1,1,1,0.03)
                            RowLayout {
                                anchors.fill: parent; anchors.leftMargin: 16; anchors.rightMargin: 16; spacing: 12
                                Text { text: qsTr("参数名称"); color: "#64748B"; font.pointSize: 10; font.bold: true; Layout.preferredWidth: 280 }
                                Text { text: qsTr("当前值"); color: "#64748B"; font.pointSize: 10; font.bold: true; Layout.fillWidth: true }
                            }
                        }

                        // 空状态
                        Item {
                            visible: settingsModel.count === 0
                            Layout.fillWidth: true; Layout.fillHeight: true
                            ColumnLayout {
                                anchors.centerIn: parent; spacing: 8
                                Text { text: "📂"; font.pointSize: 36; Layout.alignment: Qt.AlignHCenter; opacity: 0.4 }
                                Text { text: qsTr("请选择一个配置文件"); color: "#475569"; font.pointSize: 13; Layout.alignment: Qt.AlignHCenter }
                                Text { text: qsTr("点击上方下拉框选择文件，或使用刷新按钮加载文件列表"); color: "#334155"; font.pointSize: 10; Layout.alignment: Qt.AlignHCenter }
                            }
                        }

                        // 参数列表
                        ScrollView {
                            visible: settingsModel.count > 0
                            Layout.fillWidth: true; Layout.fillHeight: true
                            clip: true
                            ScrollBar.vertical.policy: ScrollBar.AsNeeded

                            ListView {
                                id: settingsListView
                                model: settingsModel
                                spacing: 2

                                delegate: Rectangle {
                                    width: settingsListView.width - 8
                                    height: 44
                                    radius: 8
                                    color: settingsItemMA.containsMouse ? Qt.rgba(1,1,1,0.04) : "transparent"

                                    MouseArea { id: settingsItemMA; anchors.fill: parent; hoverEnabled: true; propagateComposedEvents: true; onPressed: mouse.accepted = false }

                                    RowLayout {
                                        anchors.fill: parent; anchors.leftMargin: 16; anchors.rightMargin: 16; spacing: 12

                                        // 参数名
                                        Text {
                                            text: model.key || ""
                                            color: "#CBD5E1"
                                            font.pointSize: 11
                                            font.family: "monospace"
                                            Layout.preferredWidth: 270
                                            elide: Text.ElideRight
                                            ToolTip {
                                                visible: keyMA.containsMouse && (model.key || "").length > 35
                                                text: model.key || ""
                                                delay: 500
                                            }
                                            MouseArea { id: keyMA; anchors.fill: parent; hoverEnabled: true; propagateComposedEvents: true; onPressed: mouse.accepted = false }
                                        }

                                        // 值输入框
                                        TextField {
                                            id: editField
                                            text: model.value || ""
                                            readOnly: model.readOnly || false
                                            Layout.fillWidth: true
                                            height: 32
                                            font.pointSize: 11
                                            color: model.readOnly ? "#64748B" : "#F1F5F9"
                                            selectionColor: model.readOnly ? "transparent" : "#2563EB"
                                            selectedTextColor: model.readOnly ? "#64748B" : "white"
                                            background: Rectangle {
                                                color: editField.activeFocus && !model.readOnly ? "#1E293B" : "#111318"
                                                radius: 8
                                                border.color: {
                                                    if (model.readOnly) return Qt.rgba(1,1,1,0.06)
                                                    return editField.activeFocus ? "#2563EB" : Qt.rgba(1,1,1,0.06)
                                                }
                                                border.width: editField.activeFocus && !model.readOnly ? 2 : 1
                                            }
                                            leftPadding: 10
                                            onTextChanged: { settingsModel.setProperty(index, "value", text) }
                                        }

                                        // 锁定按钮
                                        Rectangle {
                                            width: 32; height: 32; radius: 8
                                            color: lockMA.containsMouse ? "#1E293B" : "transparent"
                                            ToolTip {
                                                visible: lockMA.containsMouse
                                                text: model.readOnly ? "解锁此字段" : "锁定此字段"
                                                timeout: 1000
                                            }
                                            Text {
                                                anchors.centerIn: parent
                                                text: model.readOnly ? "🔒" : "🔓"
                                                font.pointSize: 12
                                            }
                                            MouseArea {
                                                id: lockMA
                                                anchors.fill: parent
                                                hoverEnabled: true
                                                cursorShape: Qt.PointingHandCursor
                                                onClicked: {
                                                    // 显示密码输入对话框
                                                    lockDialog.currentKey = model.key
                                                    lockDialog.currentReadOnly = model.readOnly
                                                    lockDialog.currentIndex = index
                                                    lockDialog.open()
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // ===== 修改记录面板 =====
                Item {
                    visible: mainPage.changeLogVisible
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ColumnLayout {
                        anchors.fill: parent
                        spacing: 0

                        // 表头
                        Rectangle {
                            Layout.fillWidth: true; height: 36; radius: 8
                            color: Qt.rgba(1,1,1,0.03)
                            RowLayout {
                                anchors.fill: parent; anchors.leftMargin: 16; anchors.rightMargin: 16; spacing: 12
                                Text { text: qsTr("时间"); color: "#64748B"; font.pointSize: 10; font.bold: true; Layout.preferredWidth: 150 }
                                Text { text: qsTr("参数"); color: "#64748B"; font.pointSize: 10; font.bold: true; Layout.preferredWidth: 200 }
                                Text { text: qsTr("变更"); color: "#64748B"; font.pointSize: 10; font.bold: true; Layout.fillWidth: true }
                            }
                        }

                        // 空状态
                        Item {
                            visible: changeLogModel.count === 0
                            Layout.fillWidth: true; Layout.fillHeight: true
                            ColumnLayout {
                                anchors.centerIn: parent; spacing: 8
                                Text { text: "📋"; font.pointSize: 36; Layout.alignment: Qt.AlignHCenter; opacity: 0.4 }
                                Text { text: qsTr("暂无修改记录"); color: "#475569"; font.pointSize: 13; Layout.alignment: Qt.AlignHCenter }
                                Text { text: qsTr("当你编辑并保存配置后，修改记录会自动出现在这里"); color: "#334155"; font.pointSize: 10; Layout.alignment: Qt.AlignHCenter }
                            }
                        }

                        // 记录列表
                        ScrollView {
                            visible: changeLogModel.count > 0
                            Layout.fillWidth: true; Layout.fillHeight: true
                            clip: true
                            ScrollBar.vertical.policy: ScrollBar.AsNeeded

                            ListView {
                                id: changeLogListView
                                model: changeLogModel
                                spacing: 2

                                delegate: Rectangle {
                                    width: changeLogListView.width - 8
                                    height: 48
                                    radius: 8
                                    color: logItemMA.containsMouse ? Qt.rgba(1,1,1,0.04) : "transparent"

                                    MouseArea { id: logItemMA; anchors.fill: parent; hoverEnabled: true }

                                    RowLayout {
                                        anchors.fill: parent; anchors.leftMargin: 16; anchors.rightMargin: 16; spacing: 12

                                        // 时间 + 文件
                                        ColumnLayout {
                                            Layout.preferredWidth: 150; spacing: 0
                                            Text {
                                                text: {
                                                    var t = model.changedAt || ""
                                                    // 格式化为短时间
                                                    if (t.length > 10) return t.substring(5, 16).replace("T", " ")
                                                    return t
                                                }
                                                color: "#94A3B8"; font.pointSize: 10
                                            }
                                            Text {
                                                text: { var fp = model.filePath || ""; return fp.split('/').pop() || fp }
                                                color: "#60A5FA"; font.pointSize: 9
                                                elide: Text.ElideRight
                                                Layout.maximumWidth: 140
                                            }
                                        }

                                        // 参数名
                                        Text {
                                            text: model.key || ""
                                            color: "#CBD5E1"; font.pointSize: 11; font.bold: true; font.family: "monospace"
                                            elide: Text.ElideRight
                                            Layout.preferredWidth: 200
                                        }

                                        // 变更值
                                        RowLayout {
                                            Layout.fillWidth: true; spacing: 6
                                            // 旧值
                                            Rectangle {
                                                visible: (model.oldValue || "") !== ""
                                                Layout.maximumWidth: 160; height: 24; radius: 6
                                                width: oldText.implicitWidth + 12
                                                color: Qt.rgba(239/255, 68/255, 68/255, 0.12)
                                                Text {
                                                    id: oldText; anchors.centerIn: parent
                                                    text: model.oldValue || ""
                                                    color: "#F87171"; font.pointSize: 9
                                                    font.strikeout: true
                                                    elide: Text.ElideRight
                                                    maximumLineCount: 1
                                                }
                                            }
                                            Text { text: "→"; color: "#475569"; font.pointSize: 11 }
                                            // 新值
                                            Rectangle {
                                                Layout.maximumWidth: 200; height: 24; radius: 6
                                                width: newText.implicitWidth + 12
                                                color: Qt.rgba(34/255, 197/255, 94/255, 0.12)
                                                Text {
                                                    id: newText; anchors.centerIn: parent
                                                    text: model.newValue || ""
                                                    color: "#4ADE80"; font.pointSize: 9; font.bold: true
                                                    elide: Text.ElideRight
                                                    maximumLineCount: 1
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // ===== 底部操作栏 =====
                Rectangle {
                    Layout.fillWidth: true; height: 1; color: Qt.rgba(1,1,1,0.06); Layout.topMargin: 4
                }

                RowLayout {
                    Layout.fillWidth: true; Layout.topMargin: 8
                    spacing: 10

                    // 保存提示
                    Text {
                        visible: settingsModel.count > 0 && !mainPage.changeLogVisible
                        text: qsTr("💡 修改后点击保存，原文件将自动备份为 .bak")
                        color: "#475569"; font.pointSize: 9
                    }

                    Item { Layout.fillWidth: true }

                    // 取消按钮
                    Rectangle {
                        width: 80; height: 38; radius: 10
                        color: cancelBtnMA.containsMouse ? "#1E293B" : "transparent"
                        border.color: Qt.rgba(1,1,1,0.1); border.width: 1
                        Text { anchors.centerIn: parent; text: qsTr("取消"); color: "#94A3B8"; font.pointSize: 12 }
                        MouseArea {
                            id: cancelBtnMA; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor
                            onClicked: mainPage.settingsVisible = false
                        }
                    }

                    // 保存按钮
                    Rectangle {
                        visible: !mainPage.changeLogVisible
                        width: 100; height: 38; radius: 10
                        gradient: Gradient {
                            orientation: Gradient.Horizontal
                            GradientStop { position: 0; color: saveBtnMA.containsMouse ? "#3B82F6" : "#2563EB" }
                            GradientStop { position: 1; color: saveBtnMA.containsMouse ? "#8B5CF6" : "#7C3AED" }
                        }
                        Text { anchors.centerIn: parent; text: qsTr("💾 保存"); color: "white"; font.pointSize: 12; font.bold: true }
                        MouseArea {
                            id: saveBtnMA; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                if (!mainPage.settingsFilePath) { console.warn("未选择文件"); return; }
                                var arr = [];
                                var readOnlyCount = 0;
                                for (var i=0;i<settingsModel.count;i++) {
                                    var it = settingsModel.get(i);
                                    // 只读字段也保存，只是不允许用户修改
                                    arr.push({ key: it.key, value: it.value })
                                    if (it.readOnly) {
                                        readOnlyCount++
                                    }
                                }
                                if (readOnlyCount > 0) {
                                    console.log("包含", readOnlyCount, "个只读字段")
                                }
                                if (typeof searchVM.writeConfigFile === 'function') {
                                    var ok = searchVM.writeConfigFile(mainPage.settingsFilePath, arr);
                                    if (ok) {
                                        try { searchVM.buildKeyIndex(); searchVM.updateSearchResults(); } catch(e) {}
                                        mainPage.settingsVisible = false;
                                    } else {
                                        console.warn("保存文件失败")
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    function loadSettingsFromFile(path) {
        settingsModel.clear()
        if (!path || path.length === 0) return
        var arr = []
        if (typeof searchVM.readConfigFile === 'function') {
            try { arr = searchVM.readConfigFile(path) } catch(e) { console.warn('readConfigFile failed', e); arr = [] }
        } else {
            console.warn('readConfigFile not available; rebuild the app')
        }
        
        // 加载只读字段列表
        var readOnlyKeys = {}
        if (DB && typeof DB.getReadOnlyFields === 'function') {
            var roFields = DB.getReadOnlyFields(path)
            for (var ri=0; ri<roFields.length; ri++) {
                readOnlyKeys[roFields[ri].key] = true
            }
        }
        
        // 添加到模型，包含只读状态
        for (var i=0;i<arr.length;i++) {
            var key = arr[i].key || arr[i].k || ''
            settingsModel.append({ 
                key: key, 
                value: arr[i].value || arr[i].v || '',
                readOnly: readOnlyKeys[key] || false
            })
        }
    }

    function loadChangeLogs() {
        changeLogModel.clear()
        if (!DB || typeof DB.getChangeLogs !== 'function') {
            // 如果指定了文件，尝试按文件查询
            if (mainPage.settingsFilePath && DB && typeof DB.getChangeLogsForFile === 'function') {
                var fileArr = DB.getChangeLogsForFile(mainPage.settingsFilePath, 50)
                for (var j=0; j<fileArr.length; j++) {
                    changeLogModel.append({
                        filePath: fileArr[j].filePath || "",
                        key: fileArr[j].key || "",
                        oldValue: fileArr[j].oldValue || "",
                        newValue: fileArr[j].newValue || "",
                        changedAt: fileArr[j].changedAt || ""
                    })
                }
            }
            return
        }
        var arr = []
        if (mainPage.settingsFilePath && typeof DB.getChangeLogsForFile === 'function') {
            arr = DB.getChangeLogsForFile(mainPage.settingsFilePath, 50)
        } else {
            arr = DB.getChangeLogs(50)
        }
        for (var i=0; i<arr.length; i++) {
            changeLogModel.append({
                filePath: arr[i].filePath || "",
                key: arr[i].key || "",
                oldValue: arr[i].oldValue || "",
                newValue: arr[i].newValue || "",
                changedAt: arr[i].changedAt || ""
            })
        }
    }

    // 快捷按钮：根据文件名关键词打开设置弹窗
    function openConfigByName(fileKeyword) {
        if (!DB || typeof DB.listFiles !== 'function') {
            console.warn("DB.listFiles not available")
            return
        }
        var files = DB.listFiles()
        var matchedPath = ""
        var kw = fileKeyword.toLowerCase()
        // 优先精确匹配文件名（不含路径、不含扩展名）
        for (var i = 0; i < files.length; i++) {
            var p = files[i].path || ""
            var fname = p.split('/').pop().toLowerCase()
            var nameNoExt = fname.replace(/\.[^/.]+$/, "")
            if (nameNoExt === kw) {
                matchedPath = p
                break
            }
        }
        // 如果没精确匹配，尝试包含匹配
        if (!matchedPath) {
            for (var j = 0; j < files.length; j++) {
                var p2 = files[j].path || ""
                var fname2 = p2.split('/').pop().toLowerCase()
                if (fname2.indexOf(kw) >= 0) {
                    matchedPath = p2
                    break
                }
            }
        }
        if (matchedPath) {
            // 填充文件下拉列表
            fileModel.clear()
            for (var k = 0; k < files.length; k++) {
                var pp = files[k].path || ""
                var name = pp.split('/').pop() || pp
                name = name.replace(/\.[^/.]+$/, "")
                fileModel.append({ path: pp, format: files[k].format, display: name })
            }
            // 设置当前文件并加载内容
            settingsFilePath = matchedPath
            loadSettingsFromFile(matchedPath)
            // 设置 ComboBox 选中项
            for (var ci = 0; ci < fileModel.count; ci++) {
                if (fileModel.get(ci).path === matchedPath) {
                    fileComboBox.currentIndex = ci
                    break
                }
            }
            mainPage.settingsVisible = true
        } else {
            console.warn("未找到匹配文件:", fileKeyword)
            // 仍然搜索该关键词
            searchField.text = fileKeyword
            if (searchVM.aiEnabled) searchVM.analyzeSearchQuery(fileKeyword)
        }
    }

    // ========== AI 管理面板 ==========
    property bool aiManagementVisible: false

    Rectangle {
        id: aiManagementPanel
        anchors.fill: parent
        color: "#000000"
        opacity: 0.7
        visible: mainPage.aiManagementVisible
        z: 100
        MouseArea { anchors.fill: parent; onClicked: mainPage.aiManagementVisible = false }

        Rectangle {
            id: aiPanelContent
            anchors.centerIn: parent
            width: Math.min(parent.width * 0.85, 900)
            height: Math.min(parent.height * 0.85, 700)
            color: cardColor
            radius: 16
            border.color: borderColor
            border.width: 1
            z: 101

            property bool dataLoaded: false
            onVisibleChanged: {
                if (visible) {
                    loadUserDictionary()
                    loadSearchHistory()
                }
            }

            // 关闭按钮
            Rectangle {
                anchors.top: parent.top; anchors.right: parent.right; anchors.margins: 12
                width: 32; height: 32; radius: 16
                color: "transparent"; border.color: dangerColor; border.width: 1
                MouseArea { anchors.fill: parent; onClicked: mainPage.aiManagementVisible = false; cursorShape: Qt.PointingHandCursor }
                Text { text: "✕"; anchors.centerIn: parent; color: dangerColor; font.pointSize: 16 }
            }

            // 标题
            Text {
                anchors.top: parent.top; anchors.left: parent.left; anchors.margins: 20
                text: "🤖 AI 智能管理"; color: primaryColor; font.pointSize: 18; font.bold: true
            }

            // 选项卡
            RowLayout {
                id: aiTabs
                anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                anchors.topMargin: 60; anchors.leftMargin: 20; anchors.rightMargin: 20
                spacing: 8
                property int selectedIndex: 0
                Repeater {
                    model: ["📚 用户词典", "📝 搜索历史", "⚙️ AI 设置"]
                    delegate: Rectangle {
                        color: aiTabs.selectedIndex === index ? primaryColor : surfaceColor
                        radius: 8; height: 36
                        Layout.preferredWidth: tabText.paintedWidth + 24
                        border.color: aiTabs.selectedIndex === index ? primaryLight : borderColor
                        border.width: 1
                        MouseArea { anchors.fill: parent; onClicked: aiTabs.selectedIndex = index; cursorShape: Qt.PointingHandCursor }
                        Text {
                            id: tabText; text: modelData; anchors.centerIn: parent
                            color: aiTabs.selectedIndex === index ? "#FFFFFF" : textSecondary; font.pointSize: 12
                        }
                    }
                }
                Item { Layout.fillWidth: true }
            }

            // 内容区域 - 用户词典
            Rectangle {
                anchors.fill: parent; anchors.topMargin: 110; anchors.bottomMargin: 20
                anchors.leftMargin: 20; anchors.rightMargin: 20
                color: "transparent"
                visible: aiTabs.selectedIndex === 0
                ColumnLayout {
                    anchors.fill: parent; spacing: 12
                    Rectangle {
                        color: surfaceColor; radius: 10
                        Layout.fillWidth: true; implicitHeight: addLayout.implicitHeight + 20
                        border.color: borderColor; border.width: 1
                        ColumnLayout {
                            id: addLayout; anchors.fill: parent; anchors.margins: 12; spacing: 8
                            Text { text: "添加自定义词条"; color: textPrimary; font.pointSize: 13; font.bold: true }
                            RowLayout {
                                Layout.fillWidth: true; spacing: 8
                                TextField {
                                    id: newTermKey; placeholderText: "英文键名 (如：exposure_time)"
                                    Layout.fillWidth: true; height: 36; color: textPrimary; font.pointSize: 12
                                    background: Rectangle { color: cardColor; radius: 8; border.color: borderColor; border.width: 1 }
                                }
                                TextField {
                                    id: newTermChinese; placeholderText: "中文名 (如：曝光时间)"
                                    Layout.fillWidth: true; height: 36; color: textPrimary; font.pointSize: 12
                                    background: Rectangle { color: cardColor; radius: 8; border.color: borderColor; border.width: 1 }
                                }
                            }
                            TextField {
                                id: newTermSynonyms; placeholderText: "同义词 (用逗号分隔)"
                                Layout.fillWidth: true; height: 36; color: textPrimary; font.pointSize: 12
                                background: Rectangle { color: cardColor; radius: 8; border.color: borderColor; border.width: 1 }
                            }
                            Button {
                                text: "➕ 添加词条"; height: 36; Layout.preferredWidth: 120
                                onClicked: {
                                    if (newTermKey.text.trim() && newTermChinese.text.trim()) {
                                        var syms = newTermSynonyms.text.split(/[,,]/).map(function(s){return s.trim()}).filter(function(s){return s})
                                        searchVM.addUserTerm(newTermKey.text.trim(), newTermChinese.text.trim(), syms)
                                        newTermKey.text = ""; newTermChinese.text = ""; newTermSynonyms.text = ""
                                        userDictModel.clear(); loadUserDictionary()
                                    }
                                }
                                background: Rectangle { color: primaryColor; radius: 8 }
                                contentItem: Text { text: parent.text; color: "#FFFFFF"; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                            }
                        }
                    }
                    Text { text: "已定义 " + userDictModel.count + " 个自定义词条"; color: textSecondary; font.pointSize: 11 }
                    Rectangle {
                        color: cardColor; radius: 10; Layout.fillWidth: true; Layout.fillHeight: true
                        border.color: borderColor; border.width: 1
                        Flickable {
                            anchors.fill: parent; clip: true
                            contentHeight: userDictListView.contentHeight
                            flickableDirection: Flickable.VerticalFlick
                            ListView {
                                id: userDictListView; model: userDictModel; spacing: 6; anchors.fill: parent
                                delegate: Rectangle {
                                    width: userDictListView.width - 20; height: 60; radius: 8
                                    color: surfaceColor; border.color: borderColor; border.width: 1
                                    RowLayout {
                                        anchors.fill: parent; anchors.margins: 12; spacing: 12
                                        Rectangle { width: 4; height: 40; radius: 2; color: accentColor }
                                        ColumnLayout {
                                            Layout.fillWidth: true; spacing: 4
                                            Text { text: modelData.key; color: primaryLight; font.pointSize: 13; font.bold: true }
                                            Text { text: "→ " + modelData.chinese; color: textSecondary; font.pointSize: 11 }
                                            Text { text: modelData.synonyms ? "同义词：" + modelData.synonyms : ""; color: textMuted; font.pointSize: 10 }
                                        }
                                        Button {
                                            text: "删除"; height: 30; Layout.preferredWidth: 60
                                            onClicked: { searchVM.removeUserTerm(modelData.key); userDictModel.remove(index) }
                                            background: Rectangle { color: "#3f1a1a"; radius: 6; border.color: dangerColor; border.width: 1 }
                                            contentItem: Text { text: parent.text; color: dangerColor; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter; font.pointSize: 11 }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // 内容区域 - 搜索历史
            Rectangle {
                anchors.fill: parent; anchors.topMargin: 110; anchors.bottomMargin: 20
                anchors.leftMargin: 20; anchors.rightMargin: 20
                color: "transparent"
                visible: aiTabs.selectedIndex === 1
                ColumnLayout {
                    anchors.fill: parent; spacing: 12
                    RowLayout {
                        Layout.fillWidth: true
                        Text { text: "📝 搜索历史"; color: textPrimary; font.pointSize: 14; font.bold: true }
                        Item { Layout.fillWidth: true }
                        Button {
                            text: "清空历史"; height: 32; Layout.preferredWidth: 80
                            onClicked: { searchVM.clearSearchHistory(); historyModel.clear(); hotSearchModel.clear() }
                            background: Rectangle { color: "#3f1a1a"; radius: 8; border.color: dangerColor; border.width: 1 }
                            contentItem: Text { text: parent.text; color: dangerColor; anchors.fill: parent; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter; font.pointSize: 11 }
                        }
                    }
                    RowLayout { Layout.fillWidth: true; Layout.fillHeight: true; spacing: 16
                        Rectangle {
                            color: cardColor; radius: 10; Layout.fillWidth: true; Layout.fillHeight: true
                            border.color: borderColor; border.width: 1
                            ColumnLayout {
                                anchors.fill: parent; anchors.margins: 12; spacing: 8
                                Text { text: "最近搜索"; color: "#94a3b8"; font.pointSize: 12 }
                                Rectangle {
                                    color: "#1e293b"; radius: 8; Layout.fillWidth: true; Layout.fillHeight: true
                                    border.color: borderColor; border.width: 1
                                    Flickable {
                                        anchors.fill: parent; clip: true
                                        contentHeight: historyListView.contentHeight
                                        flickableDirection: Flickable.VerticalFlick
                                        ListView {
                                            id: historyListView; model: historyModel; spacing: 4; anchors.fill: parent
                                            delegate: Rectangle {
                                                width: parent.width - 16; height: 40; radius: 6
                                                color: index % 2 === 0 ? "#0f172a" : "#1e293b"
                                                border.color: "#334155"
                                                border.width: 1
                                                RowLayout {
                                                    anchors.fill: parent; anchors.margins: 10; spacing: 8
                                                    Text { 
                                                        text: model.query || ""
                                                        color: "#f1f5f9"
                                                        font.pointSize: 13
                                                        font.bold: true
                                                        elide: Text.ElideRight
                                                        Layout.fillWidth: true
                                                    }
                                                    Text { 
                                                        text: model.intent || ""
                                                        color: "#94a3b8"
                                                        font.pointSize: 11
                                                    }
                                                    Item { Layout.fillWidth: true }
                                                    Text { 
                                                        text: model.time || ""
                                                        color: "#64748b"
                                                        font.pointSize: 11
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        Rectangle {
                            color: cardColor; radius: 10; Layout.preferredWidth: 250; Layout.fillHeight: true
                            border.color: borderColor; border.width: 1
                            ColumnLayout {
                                anchors.fill: parent; anchors.margins: 12; spacing: 8
                                Text { text: "🔥 热门搜索"; color: "#94a3b8"; font.pointSize: 12 }
                                Rectangle {
                                    color: "#1e293b"; radius: 8; Layout.fillWidth: true; Layout.fillHeight: true
                                    border.color: borderColor; border.width: 1
                                    Flickable {
                                        anchors.fill: parent; clip: true
                                        contentHeight: hotSearchListView.contentHeight
                                        flickableDirection: Flickable.VerticalFlick
                                        ListView {
                                            id: hotSearchListView; model: hotSearchModel; spacing: 4; anchors.fill: parent
                                            delegate: Rectangle {
                                                width: parent.width - 16; height: 36; radius: 6; color: "transparent"
                                                RowLayout {
                                                    anchors.fill: parent; anchors.margins: 8; spacing: 8
                                                    Text { 
                                                        text: (index + 1) + "."
                                                        color: index < 3 ? "#F59E0B" : "#64748b"
                                                        font.pointSize: 11
                                                        font.bold: index < 3
                                                    }
                                                    Text { 
                                                        text: model.query || ""
                                                        color: "#f1f5f9"
                                                        font.pointSize: 12
                                                    }
                                                    Item { Layout.fillWidth: true }
                                                    Text { 
                                                        text: (model.frequency || 0) + "次"
                                                        color: "#64748b"
                                                        font.pointSize: 10
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // 内容区域 - AI 设置
            Rectangle {
                anchors.fill: parent; anchors.topMargin: 110; anchors.bottomMargin: 20
                anchors.leftMargin: 20; anchors.rightMargin: 20
                color: "transparent"
                visible: aiTabs.selectedIndex === 2
                ColumnLayout {
                    anchors.fill: parent; spacing: 16
                    Rectangle {
                        color: surfaceColor; radius: 10; Layout.fillWidth: true; implicitHeight: 70
                        border.color: borderColor; border.width: 1
                        RowLayout {
                            anchors.fill: parent; anchors.margins: 16; spacing: 16
                            Text { text: "🤖"; font.pointSize: 28; opacity: searchVM.aiEnabled ? 1.0 : 0.5 }
                            ColumnLayout {
                                Layout.fillWidth: true; spacing: 4
                                Text { text: "AI 智能增强"; color: textPrimary; font.pointSize: 14; font.bold: true }
                                Text { text: "自动分析搜索意图，提供智能建议"; color: textSecondary; font.pointSize: 11 }
                            }
                            Rectangle {
                                width: 56; height: 28; radius: 14
                                color: searchVM.aiEnabled ? primaryColor : cardColor
                                border.color: searchVM.aiEnabled ? primaryLight : borderColor; border.width: 1
                                Rectangle {
                                    width: 24; height: 24; radius: 12; color: "#FFFFFF"
                                    x: searchVM.aiEnabled ? parent.width - 26 : 2; y: 2
                                    Behavior on x { NumberAnimation { duration: 200 } }
                                }
                                MouseArea { anchors.fill: parent; onClicked: searchVM.aiEnabled = !searchVM.aiEnabled; cursorShape: Qt.PointingHandCursor }
                            }
                        }
                    }
                    Rectangle {
                        color: surfaceColor; radius: 10; Layout.fillWidth: true; implicitHeight: 70
                        border.color: borderColor; border.width: 1
                        RowLayout {
                            anchors.fill: parent; anchors.margins: 16; spacing: 16
                            Text { text: "🧠"; font.pointSize: 28 }
                            ColumnLayout {
                                Layout.fillWidth: true; spacing: 4
                                Text { text: "搜索历史学习"; color: textPrimary; font.pointSize: 14; font.bold: true }
                                Text { text: "记录搜索历史，优化建议排序"; color: textSecondary; font.pointSize: 11 }
                            }
                            Rectangle {
                                width: 56; height: 28; radius: 14
                                color: searchVM.learningEnabled ? primaryColor : cardColor
                                border.color: searchVM.learningEnabled ? primaryLight : borderColor; border.width: 1
                                Rectangle {
                                    width: 24; height: 24; radius: 12; color: "#FFFFFF"
                                    x: searchVM.learningEnabled ? parent.width - 26 : 2; y: 2
                                    Behavior on x { NumberAnimation { duration: 200 } }
                                }
                                MouseArea { anchors.fill: parent; onClicked: searchVM.setLearningEnabled(!searchVM.learningEnabled); cursorShape: Qt.PointingHandCursor }
                            }
                        }
                    }
                    Rectangle {
                        color: surfaceColor; radius: 10; Layout.fillWidth: true; implicitHeight: 100
                        border.color: borderColor; border.width: 1
                        ColumnLayout {
                            anchors.fill: parent; anchors.margins: 16; spacing: 12
                            Text { text: "📊 统计信息"; color: textPrimary; font.pointSize: 14; font.bold: true }
                            RowLayout {
                                Layout.fillWidth: true; spacing: 16
                                Repeater {
                                    model: [
                                        {count: userDictModel.count, label: "自定义词条", color: primaryLight},
                                        {count: historyModel.count, label: "搜索历史", color: accentColor},
                                        {count: hotSearchModel.count, label: "热门搜索", color: warningColor}
                                    ]
                                    delegate: Rectangle {
                                        color: cardColor; radius: 8
                                        Layout.preferredWidth: 150; Layout.preferredHeight: 50
                                        border.color: borderColor; border.width: 1
                                        ColumnLayout {
                                            anchors.centerIn: parent; spacing: 2
                                            Text { text: modelData.count; color: modelData.color; font.pointSize: 20; font.bold: true }
                                            Text { text: modelData.label; color: textMuted; font.pointSize: 10 }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Item { Layout.fillHeight: true }
                    Rectangle {
                        color: cardColor; radius: 8; Layout.fillWidth: true; implicitHeight: 60
                        border.color: borderColor; border.width: 1
                        ColumnLayout {
                            anchors.fill: parent; anchors.margins: 12; spacing: 4
                            Text { text: "数据文件位置"; color: textMuted; font.pointSize: 10 }
                            Text {
                                text: searchVM.getUserDictionaryPath ? searchVM.getUserDictionaryPath() : "未知"
                                color: textSecondary; font.pointSize: 10; font.family: "monospace"
                                wrapMode: Text.WrapAnywhere
                            }
                        }
                    }
                }
            }
        }
    }

    function loadUserDictionary() {
        var terms = searchVM.getUserTerms()
        userDictModel.clear()
        for (var i = 0; i < terms.length; i++) {
            userDictModel.append({
                key: terms[i].key,
                chinese: terms[i].chinese,
                synonyms: terms[i].synonyms ? terms[i].synonyms.join(", ") : ""
            })
        }
    }

    function loadSearchHistory() {
        historyModel.clear()
        hotSearchModel.clear()
        var history = searchVM.getSearchHistory(50)
        for (var i = 0; i < history.length; i++) {
            var h = history[i]
            historyModel.append({
                query: h.query,
                intent: h.intent === "search_key" ? "🔑 配置项" : h.intent === "search_value" ? "📊 参数值" : "📝 中文",
                time: h.timestamp ? new Date(h.timestamp).toLocaleTimeString() : ""
            })
        }
        var hot = searchVM.getHotSearches(20)
        for (var j = 0; j < hot.length; j++) {
            hotSearchModel.append({ query: hot[j].query, frequency: hot[j].frequency })
        }
    }

    // ===== 锁定/解锁密码对话框 =====
    Rectangle {
        id: lockOverlay
        anchors.fill: parent
        color: "#000000AA"
        visible: lockDialog.visible
        z: 2000
        MouseArea { anchors.fill: parent; onClicked: lockDialog.close() }

        Rectangle {
            id: lockDialog
            width: 380
            height: lockContent.implicitHeight + 40
            anchors.centerIn: parent
            radius: 16
            color: cardColor
            border.color: primaryColor
            border.width: 2
            visible: false

            property string currentKey: ""
            property bool currentReadOnly: false
            property int currentIndex: -1

            function open() {
                passwordField.text = ""
                passwordField.forceActiveFocus()
                visible = true
                lockOverlay.visible = true
            }

            function close() {
                visible = false
                lockOverlay.visible = false
                currentKey = ""
                currentReadOnly = false
                currentIndex = -1
            }

            function confirm() {
                if (passwordField.text === "aoi2024") {
                    var newReadOnly = !currentReadOnly
                    if (DB && typeof DB.setFieldReadOnly === 'function') {
                        DB.setFieldReadOnly(settingsFilePath, currentKey, newReadOnly)
                        settingsModel.setProperty(currentIndex, "readOnly", newReadOnly)
                    }
                    close()
                } else {
                    passwordError.visible = true
                    passwordField.selectAll()
                    passwordField.forceActiveFocus()
                }
            }

            ColumnLayout {
                id: lockContent
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.margins: 24
                spacing: 16

                // 标题
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12

                    Rectangle {
                        width: 40; height: 40; radius: 10
                        color: primaryColor
                        Text {
                            anchors.centerIn: parent
                            text: "CW"
                            color: "#FFFFFF"
                            font.pointSize: 14
                            font.bold: true
                        }
                    }

                    ColumnLayout {
                        spacing: 4
                        Text {
                            text: currentReadOnly ? "解锁字段" : "锁定字段"
                            color: textPrimary
                            font.pointSize: 15
                            font.bold: true
                        }
                        Text {
                            text: "操作需要验证密码"
                            color: textMuted
                            font.pointSize: 10
                        }
                    }

                    Item { Layout.fillWidth: true }

                    // 关闭按钮
                    Rectangle {
                        width: 32; height: 32; radius: 16
                        color: closeLockMA.containsMouse ? "#374151" : "transparent"
                        Text { text: "✕"; anchors.centerIn: parent; color: "#94A3B8"; font.pointSize: 12 }
                        MouseArea {
                            id: closeLockMA; anchors.fill: parent; hoverEnabled: true; cursorShape: Qt.PointingHandCursor
                            onClicked: lockDialog.close()
                        }
                    }
                }

                // 字段名显示
                Rectangle {
                    Layout.fillWidth: true
                    height: 40
                    radius: 8
                    color: "#0F1117"
                    border.color: Qt.rgba(1,1,1,0.08)
                    Text {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.margins: 12
                        text: lockDialog.currentKey || ""
                        color: primaryLight
                        font.pointSize: 11
                        font.family: "monospace"
                        elide: Text.ElideMiddle
                    }
                }

                // 密码输入
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 6

                    Text {
                        text: "请输入密码"
                        color: textSecondary
                        font.pointSize: 11
                    }

                    TextField {
                        id: passwordField
                        Layout.fillWidth: true
                        height: 40
                        font.pointSize: 13
                        color: textPrimary
                        echoMode: TextInput.Password
                        placeholderText: "输入密码..."
                        placeholderTextColor: textMuted
                        selectionColor: primaryColor
                        selectedTextColor: "white"

                        background: Rectangle {
                            color: passwordField.activeFocus ? "#1E293B" : "#111318"
                            radius: 10
                            border.color: passwordError.visible ? "#EF4444" : (passwordField.activeFocus ? primaryColor : borderColor)
                            border.width: passwordField.activeFocus ? 2 : 1
                        }

                        onAccepted: lockDialog.confirm()

                        Keys.onPressed: {
                            if (event.key === Qt.Key_Escape) {
                                lockDialog.close()
                            }
                        }
                    }

                    Text {
                        id: passwordError
                        text: "密码错误，请重试"
                        color: "#EF4444"
                        font.pointSize: 10
                        visible: false
                    }
                }

                // 提示
                Rectangle {
                    Layout.fillWidth: true
                    height: 36
                    radius: 8
                    color: Qt.rgba(37/255, 99/255, 235/255, 0.1)
                    border.color: Qt.rgba(37/255, 99/255, 235/255, 0.2)
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 8
                        spacing: 6

                        Text { text: "💡"; font.pointSize: 12 }
                        Text {
                            text: "锁定后的字段在保存时不会被修改"
                            color: textMuted
                            font.pointSize: 10
                            Layout.fillWidth: true
                        }
                    }
                }

                // 按钮
                RowLayout {
                    Layout.fillWidth: true
                    Layout.topMargin: 8
                    spacing: 10

                    // 取消按钮
                    Rectangle {
                        id: cancelBtn
                        Layout.fillWidth: true
                        height: 40
                        radius: 10
                        color: cancelMA.containsMouse ? "#334155" : surfaceColor
                        border.color: borderColor
                        border.width: 1
                        Text {
                            anchors.centerIn: parent
                            text: "取消"
                            color: textSecondary
                            font.pointSize: 12
                        }
                        MouseArea {
                            id: cancelMA
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: lockDialog.close()
                        }
                    }

                    // 锁定/解锁按钮
                    Rectangle {
                        id: confirmBtn
                        Layout.fillWidth: true
                        height: 40
                        radius: 10
                        color: confirmMA.containsMouse ? "#3B82F6" : primaryColor
                        Text {
                            anchors.centerIn: parent
                            text: lockDialog.currentReadOnly ? "解锁" : "锁定"
                            color: "#FFFFFF"
                            font.pointSize: 12
                            font.bold: true
                        }
                        MouseArea {
                            id: confirmMA
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: lockDialog.confirm()
                        }
                    }
                }
            }
        }
    }
}
