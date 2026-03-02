import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import ConfigWatcher 1.0

Window {
    id: miniWindow
    visible: false
    // 居中屏幕顶部，宽度 680，像 Spotlight / Alfred 搜索条
    width: 680
    height: 56
    x: (Screen.width - width) / 2
    y: 60
    color: "transparent"
    title: "ConfigWatcher Mini"
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool

    // 对外信号：请求切换到完整模式
    signal requestFullMode()

    // 内部搜索 VM
    SearchViewModel { id: searchVM }

    // 动态高度：无结果时只显示搜索条，有结果时展开
    property bool hasAiInfo: searchVM.aiEnabled && (searchVM.aiIntent !== "" || searchVM.aiSuggestions.length > 0)
    property bool expanded: resultListView.count > 0 || hasAiInfo
    property int aiPanelHeight: hasAiInfo ? 72 : 0
    property int collapsedHeight: 56
    property int expandedHeight: Math.min(56 + aiPanelHeight + (resultListView.count > 0 ? resultListView.count * 44 + 32 : 0), 560)

    Behavior on height { NumberAnimation { duration: 180; easing.type: Easing.OutCubic } }

    Component.onCompleted: {
        height = collapsedHeight
    }

    onExpandedChanged: {
        height = expanded ? expandedHeight : collapsedHeight
    }

    // 确保精简模式始终在最上层 + 聚焦搜索框
    onVisibleChanged: {
        if (visible) {
            raiseTimer.start()
            miniWindow.raise()
            miniWindow.requestActivate()
            searchField.forceActiveFocus()
            searchField.selectAll()
        } else {
            raiseTimer.stop()
        }
    }

    onActiveChanged: {
        if (visible && !active) {
            miniWindow.raise()
        }
    }

    // 定时器：每隔 500ms 检查并确保窗口在最上层
    Timer {
        id: raiseTimer
        interval: 500
        repeat: true
        running: miniWindow.visible
        onTriggered: {
            if (miniWindow.visible) {
                miniWindow.raise()
            }
        }
    }

    // 背景：圆角毛玻璃风深色卡片
    Rectangle {
        id: bg
        anchors.fill: parent
        radius: 16
        color: "#e6101828"       // 半透明深蓝黑
        border.color: "#334155"
        border.width: 1

        // 可拖动
        MouseArea {
            id: dragArea
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 56
            property point clickPos
            onPressed: clickPos = Qt.point(mouse.x, mouse.y)
            onPositionChanged: {
                var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
                miniWindow.x += delta.x
                miniWindow.y += delta.y
            }
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 0
            spacing: 0

            // ========== 搜索条（始终显示） ==========
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 56
                color: "transparent"

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 16
                    anchors.rightMargin: 12
                    spacing: 10

                    // Logo
                    Rectangle {
                        width: 32; height: 32; radius: 16
                        color: "#2563EB"
                        Layout.alignment: Qt.AlignVCenter
                        Text {
                            text: "CW"
                            anchors.centerIn: parent
                            color: "#FFFFFF"
                            font.pointSize: 10
                            font.bold: true
                        }
                    }

                    // 搜索框
                    TextField {
                        id: searchField
                        placeholderText: "搜索配置项（Esc 隐藏，Enter 搜索）..."
                        Layout.fillWidth: true
                        height: 36
                        font.pointSize: 14
                        color: "#f1f5f9"
                        placeholderTextColor: "#64748b"
                        selectByMouse: true
                        background: Rectangle {
                            color: "transparent"
                        }
                        onAccepted: {
                            searchVM.searchText = text
                            if (searchVM.aiEnabled) searchVM.analyzeSearchQuery(text)
                            searchVM.updateSearchResults()
                        }
                        Keys.onEscapePressed: {
                            miniWindow.hide()
                        }
                        // 实时搜索（防抖 300ms）
                        onTextChanged: debounceTimer.restart()
                    }

                    Timer {
                        id: debounceTimer
                        interval: 300
                        onTriggered: {
                            if (searchField.text.length >= 1) {
                                searchVM.searchText = searchField.text
                                if (searchVM.aiEnabled && searchField.text.length >= 2) {
                                    searchVM.analyzeSearchQuery(searchField.text)
                                }
                                searchVM.updateSearchResults()
                            } else {
                                searchVM.searchText = ""
                                searchVM.updateSearchResults()
                            }
                        }
                    }

                    // 文件类型筛选
                    ComboBox {
                        id: formatCombo
                        model: ["全部", "ini", "json", "xml"]
                        Layout.preferredWidth: 80
                        height: 32
                        font.pointSize: 11
                        currentIndex: 0
                        background: Rectangle {
                            color: "#1e293b"
                            radius: 8
                            border.color: "#475569"
                            border.width: 1
                        }
                        contentItem: Text {
                            text: formatCombo.currentText
                            color: "#94a3b8"
                            font.pointSize: 11
                            verticalAlignment: Text.AlignVCenter
                            leftPadding: 8
                        }
                        onCurrentIndexChanged: {
                            var fmt = currentIndex === 0 ? "" : currentText
                            searchVM.formatFilter = fmt
                            if (searchField.text.length > 0) {
                                searchVM.updateSearchResults()
                            }
                        }
                    }

                    // AI 开关按钮
                    Rectangle {
                        width: 32; height: 32; radius: 8
                        color: searchVM.aiEnabled ? "#1e3a5f" : "transparent"
                        border.color: searchVM.aiEnabled ? "#60a5fa" : "#475569"
                        border.width: 1
                        ToolTip {
                            visible: aiToggleMouse.containsMouse
                            text: searchVM.aiEnabled ? "关闭 AI 增强" : "开启 AI 增强"
                            delay: 600; timeout: 1500
                            y: parent.height + 6
                        }
                        MouseArea {
                            id: aiToggleMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: searchVM.aiEnabled = !searchVM.aiEnabled
                        }
                        Text {
                            text: "🤖"
                            anchors.centerIn: parent
                            font.pointSize: 13
                            opacity: searchVM.aiEnabled ? 1.0 : 0.4
                        }
                    }

                    // 展开为完整版按钮
                    Rectangle {
                        width: 32; height: 32; radius: 8
                        color: expandMouse.containsMouse ? "#1e3a5f" : "transparent"
                        border.color: "#2563EB"; border.width: 1
                        ToolTip {
                            visible: expandMouse.containsMouse
                            text: "切换完整模式"
                            delay: 600; timeout: 1500
                            y: parent.height + 6
                        }
                        MouseArea {
                            id: expandMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: miniWindow.requestFullMode()
                        }
                        Text {
                            text: "⛶"
                            anchors.centerIn: parent
                            color: "#2563EB"
                            font.pointSize: 13
                        }
                    }

                    // 关闭（隐藏）按钮
                    Rectangle {
                        width: 32; height: 32; radius: 8
                        color: closeMouse.containsMouse ? "#3b1c1c" : "transparent"
                        MouseArea {
                            id: closeMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: miniWindow.hide()
                        }
                        Text {
                            text: "✕"
                            anchors.centerIn: parent
                            color: closeMouse.containsMouse ? "#ef4444" : "#64748b"
                            font.pointSize: 13
                        }
                    }
                }
            }

            // ========== AI 智能分析面板（紧凑版） ==========
            Rectangle {
                Layout.fillWidth: true
                Layout.leftMargin: 8
                Layout.rightMargin: 8
                Layout.topMargin: 4
                implicitHeight: aiMiniLayout.implicitHeight + 12
                radius: 10
                color: "#0d1a2e"
                border.color: searchVM.aiConfidence > 0.8 ? "#10B981" : (searchVM.aiConfidence > 0.5 ? "#3B82F6" : "#334155")
                border.width: 1
                visible: miniWindow.hasAiInfo

                ColumnLayout {
                    id: aiMiniLayout
                    anchors.fill: parent
                    anchors.margins: 8
                    spacing: 6

                    // 第一行：意图 + 置信度
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 6

                        Text {
                            text: "✨"
                            font.pointSize: 11
                        }

                        // 意图标签
                        Rectangle {
                            color: searchVM.aiIntent === "search_key" ? "#1e3a5f" :
                                   searchVM.aiIntent === "search_value" ? "#14332a" :
                                   searchVM.aiIntent === "search_chinese" ? "#2d1f3d" :
                                   searchVM.aiIntent === "navigate" ? "#1f3a2d" : "#1e293b"
                            radius: 5; height: 22
                            width: miniIntentText.paintedWidth + 12
                            visible: miniIntentText.text !== ""
                            Text {
                                id: miniIntentText
                                text: {
                                    switch (searchVM.aiIntent) {
                                        case "search_key": return "🔑 搜索配置项"
                                        case "search_value": return "📊 搜索参数值"
                                        case "search_chinese": return "📝 搜索中文"
                                        case "navigate": return "🧭 导航"
                                        default: return "🔍 分析中"
                                    }
                                }
                                anchors.centerIn: parent
                                color: "#f1f5f9"
                                font.pointSize: 10
                            }
                        }

                        // AI 解释文本
                        Text {
                            text: searchVM.aiExplanation || ""
                            color: "#94a3b8"
                            font.pointSize: 10
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                            visible: text !== ""
                        }

                        // 置信度
                        Rectangle {
                            width: 60; height: 6; radius: 3
                            color: "#1e293b"
                            Rectangle {
                                width: parent.width * (searchVM.aiConfidence || 0)
                                height: parent.height; radius: 3
                                color: searchVM.aiConfidence > 0.8 ? "#10B981" : (searchVM.aiConfidence > 0.5 ? "#3B82F6" : "#F59E0B")
                            }
                        }
                        Text {
                            text: Math.round((searchVM.aiConfidence || 0) * 100) + "%"
                            color: "#64748b"
                            font.pointSize: 9
                        }
                    }

                    // 第二行：AI 建议词（可点击）
                    Flow {
                        Layout.fillWidth: true
                        spacing: 6
                        visible: searchVM.aiSuggestions.length > 0

                        Repeater {
                            model: searchVM.aiSuggestions
                            delegate: Rectangle {
                                id: miniSuggestItem
                                width: miniSuggestText.paintedWidth + 14
                                height: 24; radius: 5
                                color: miniSuggestMouse.containsMouse ? "#1e3a5f" : "transparent"
                                border.color: "#3B82F6"; border.width: 1

                                MouseArea {
                                    id: miniSuggestMouse
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        searchField.text = modelData.text
                                        searchVM.searchText = modelData.text
                                        searchVM.analyzeSearchQuery(modelData.text)
                                        searchVM.updateSearchResults()
                                    }
                                }

                                Text {
                                    id: miniSuggestText
                                    text: modelData.text || ""
                                    anchors.centerIn: parent
                                    color: modelData.type === "exact" ? "#60a5fa" :
                                           modelData.type === "synonym" ? "#6ee7b7" : "#a78bfa"
                                    font.pointSize: 10
                                }
                            }
                        }
                    }
                }
            }

            // ========== 搜索结果列表（动态显隐） ==========
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.leftMargin: 8
                Layout.rightMargin: 8
                Layout.bottomMargin: 8
                color: "#0f172a"
                radius: 12
                visible: resultListView.count > 0
                clip: true

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 4
                    spacing: 0

                    // 结果计数
                    Text {
                        text: "  " + resultListView.count + " 条结果"
                        color: "#64748b"
                        font.pointSize: 10
                        Layout.leftMargin: 8
                        Layout.topMargin: 4
                    }

                    ListView {
                        id: resultListView
                        model: searchVM.searchResults || []
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        spacing: 2
                        clip: true

                        onCountChanged: {
                            miniWindow.height = miniWindow.expanded ? miniWindow.expandedHeight : miniWindow.collapsedHeight
                        }

                        delegate: Rectangle {
                            width: resultListView.width
                            height: 40
                            radius: 8
                            color: delegateMouse.containsMouse ? "#1e293b" : "transparent"

                            MouseArea {
                                id: delegateMouse
                                anchors.fill: parent
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    searchField.text = modelData.key
                                }
                                onDoubleClicked: {
                                    // 双击打开完整模式并选中此条目
                                    miniWindow.requestFullMode()
                                }
                            }

                            RowLayout {
                                anchors.fill: parent
                                anchors.leftMargin: 12
                                anchors.rightMargin: 12
                                spacing: 10

                                // 文件格式标签
                                Rectangle {
                                    width: 36; height: 20; radius: 4
                                    color: {
                                        var fmt = modelData.format || ""
                                        if (fmt === "ini") return "#1e3a5f"
                                        if (fmt === "json") return "#1c3a2a"
                                        if (fmt === "xml") return "#3a2a1c"
                                        return "#1e293b"
                                    }
                                    Text {
                                        text: modelData.format || "?"
                                        anchors.centerIn: parent
                                        color: {
                                            var fmt = modelData.format || ""
                                            if (fmt === "ini") return "#60a5fa"
                                            if (fmt === "json") return "#34d399"
                                            if (fmt === "xml") return "#fbbf24"
                                            return "#94a3b8"
                                        }
                                        font.pointSize: 9
                                        font.bold: true
                                    }
                                }

                                // key 名称
                                Text {
                                    text: modelData.chineseKey || modelData.key || ""
                                    color: "#f1f5f9"
                                    font.pointSize: 12
                                    font.bold: true
                                    elide: Text.ElideRight
                                    Layout.preferredWidth: 200
                                }

                                // 分隔符
                                Text { text: "="; color: "#475569"; font.pointSize: 11 }

                                // 值
                                Text {
                                    text: {
                                        var v = modelData.value ? String(modelData.value) : ""
                                        return v.length > 50 ? v.substring(0, 50) + "…" : v
                                    }
                                    color: "#94a3b8"
                                    font.pointSize: 11
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
