import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import ConfigWatcher 1.0

Window {
    id: miniWindow
    visible: false
    width: 450
    height: 80
    color: "transparent"
    flags: Qt.Window | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool
    
    property var searchVM: null
    
    onVisibleChanged: {
        if (visible && searchVM) {
            searchField.text = searchVM.searchText
        }
    }
    
    // 关闭按钮
    Rectangle {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 5
        width: 20
        height: 20
        radius: 10
        color: closeMouse.containsMouse ? "#ef4444" : "transparent"
        border.color: "#ef4444"
        border.width: 1
        
        MouseArea {
            id: closeMouse
            anchors.fill: parent
            hoverEnabled: true
            onClicked: miniWindow.visible = false
        }
        
        Text {
            text: "×"
            anchors.centerIn: parent
            color: "#ef4444"
            font.pointSize: 14
            font.bold: true
        }
    }
    
    // 主内容
    Rectangle {
        anchors.fill: parent
        anchors.margins: 5
        color: "#1e293b"
        radius: 12
        border.color: "#3b82f6"
        border.width: 2
        
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 15
            anchors.rightMargin: 15
            anchors.topMargin: 8
            anchors.bottomMargin: 8
            spacing: 8
            
            // 搜索图标
            Text {
                text: "🔍"
                font.pointSize: 16
                Layout.preferredWidth: 24
            }
            
            // 搜索框
            TextField {
                id: searchField
                placeholderText: "搜索配置项... (Ctrl+Alt+Q)"
                text: searchVM ? searchVM.searchText : ""
                Layout.fillWidth: true
                height: 36
                font.pointSize: 13
                color: "#f1f5f9"
                placeholderTextColor: "#64748b"
                
                background: Rectangle {
                    color: "#0f172a"
                    radius: 8
                    border.width: 1
                    border.color: searchField.activeFocus ? "#3b82f6" : "#334155"
                }
                
                onAccepted: {
                    if (searchVM) {
                        searchVM.searchText = text
                        searchVM.updateSearchResults()
                        showResults()
                    }
                }
            }
            
            // 搜索按钮
            Rectangle {
                width: 60
                height: 36
                radius: 8
                color: searchMouse.containsMouse ? "#2563eb" : "#3b82f6"
                
                MouseArea {
                    id: searchMouse
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if (searchVM) {
                            searchVM.searchText = searchField.text
                            searchVM.updateSearchResults()
                            showResults()
                        }
                    }
                }
                
                Text {
                    text: "搜索"
                    anchors.centerIn: parent
                    color: "#ffffff"
                    font.pointSize: 12
                    font.bold: true
                }
            }
            
            // 完整模式按钮
            Rectangle {
                width: 36
                height: 36
                radius: 8
                color: fullMouse.containsMouse ? "#1e3a5f" : "transparent"
                border.color: "#60a5fa"
                border.width: 1
                
                ToolTip {
                    visible: fullMouse.containsMouse
                    text: "切换到完整模式"
                    timeout: 1500
                }
                
                MouseArea {
                    id: fullMouse
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        miniWindow.visible = false
                        if (fullWindow) fullWindow.show()
                    }
                }
                
                Text {
                    text: "⛶"
                    anchors.centerIn: parent
                    color: "#60a5fa"
                    font.pointSize: 14
                }
            }
        }
    }
    
    // 结果弹窗
    Popup {
        id: resultsPopup
        parent: miniWindow
        anchors.top: miniWindow.bottom
        anchors.left: miniWindow.left
        width: miniWindow.width
        height: 300
        modal: false
        focus: false
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        background: Rectangle {
            color: "#1e293b"
            radius: 12
            border.color: "#3b82f6"
            border.width: 2
        }
        
        ListView {
            anchors.fill: parent
            anchors.margins: 10
            model: searchVM ? searchVM.searchResults : []
            clip: true
            spacing: 4
            
            delegate: Rectangle {
                width: resultsPopup.width - 20
                height: 45
                radius: 8
                color: delegateMouse.containsMouse ? "#253348" : "#0f172a"
                border.color: "#334155"
                border.width: 1
                
                MouseArea {
                    id: delegateMouse
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        searchField.text = modelData.key
                        resultsPopup.close()
                    }
                }
                
                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 12
                    anchors.rightMargin: 12
                    spacing: 8
                    
                    Rectangle {
                        width: 3
                        height: 25
                        radius: 2
                        color: "#3b82f6"
                    }
                    
                    Text {
                        text: modelData.chineseKey || modelData.key || "未知"
                        color: "#f1f5f9"
                        font.pointSize: 11
                        font.bold: true
                        elide: Text.ElideRight
                        Layout.fillWidth: true
                    }
                    
                    Text {
                        text: modelData.value ? modelData.value.substring(0, 20) + (modelData.value.length > 20 ? "..." : "") : ""
                        color: "#64748b"
                        font.pointSize: 10
                        elide: Text.ElideRight
                        Layout.preferredWidth: 120
                    }
                }
            }
        }
    }
    
    function showResults() {
        if (searchVM && searchVM.searchResults && searchVM.searchResults.length > 0) {
            resultsPopup.open()
        }
    }
    
    // 拖动窗口
    property point clickPos: "0,0"
    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        onPressed: clickPos = Qt.point(mouse.x, mouse.y)
        onPositionChanged: {
            if (pressed && !searchMouse.containsMouse && !fullMouse.containsMouse && !closeMouse.containsMouse) {
                miniWindow.x += (mouse.x - clickPos.x)
                miniWindow.y += (mouse.y - clickPos.y)
            }
        }
    }
}
