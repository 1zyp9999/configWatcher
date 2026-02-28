import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import ConfigWatcher 1.0

Item {
    id: mainPage
    property string selectedTitle: ""
    property string selectedContent: ""
    property string selectedFormat: ""
    property bool aboutVisible: false
    property bool settingsVisible: false

    // 配色
    readonly property color primaryColor: "#00d9ff"
    readonly property color secondaryColor: "#7b2cbf"
    readonly property color accentColor: "#f72585"
    readonly property color bgColor: "#0a0e17"
    readonly property color cardBg: "#111827"
    readonly property color textColor: "#e5e7eb"
    readonly property color textMuted: "#9ca3af"

    width: parent ? parent.width : 1200
    height: parent ? parent.height : 800

    SearchViewModel {
        id: searchVM
    }

    // 背景
    Rectangle {
        anchors.fill: parent
        color: bgColor
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 16

        // 标题栏
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 60
            color: cardBg
            border.color: primaryColor
            border.width: 1
            radius: 10

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 20
                anchors.rightMargin: 20

                Text {
                    text: "⚡ ConfigWatcher"
                    font.pixelSize: 22
                    font.bold: true
                    color: primaryColor
                }

                Item { Layout.fillWidth: true }

                Button {
                    text: "关于"
                    onClicked: aboutVisible = true
                    background: Rectangle { color: primaryColor; radius: 6 }
                    contentItem: Text { text: "关于"; color: "#000"; anchors.centerIn: parent }
                }
            }
        }

        // 搜索栏
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 70
            color: cardBg
            border.color: accentColor
            border.width: 1
            radius: 10

            RowLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 12

                TextField {
                    id: searchField
                    placeholderText: "输入关键字搜索..."
                    Layout.fillWidth: true
                    height: 40
                    color: textColor
                    onAccepted: doSearch()
                    background: Rectangle { color: "#0d1117"; radius: 6; border.color: "#374151"; border.width: 1 }
                }

                ComboBox {
                    id: searchModeCombo
                    model: ["模糊搜索", "精准搜索"]
                    Layout.preferredWidth: 120
                    height: 40
                    background: Rectangle { color: "#0d1117"; radius: 6; border.color: "#374151"; border.width: 1 }
                    contentItem: Text { text: searchModeCombo.currentText; color: textColor; anchors.centerIn: parent }
                    popup.background: Rectangle { color: cardBg }
                }

                Button {
                    text: "🔍 搜索"
                    onClicked: doSearch()
                    background: Rectangle { color: primaryColor; radius: 6 }
                    contentItem: Text { text: "🔍 搜索"; color: "#000"; anchors.centerIn: parent }
                }

                Button {
                    text: "清空"
                    onClicked: { searchField.text = ""; searchVM.searchText = ""; searchVM.updateSearchResults() }
                    background: Rectangle { color: "#374151"; radius: 6 }
                    contentItem: Text { text: "清空"; color: "#fff"; anchors.centerIn: parent }
                }
            }
        }

        // 进度条
        ProgressBar {
            Layout.fillWidth: true
            value: searchVM.isLoading ? 1 : (searchVM.loadProgress / 100)
            visible: searchVM.isLoading
            background: Rectangle { color: "#1f2937"; radius: 3 }
            contentItem: Rectangle { color: primaryColor; radius: 3 }
        }

        // 结果统计
        Text {
            text: "共 " + (searchVM.searchResults ? searchVM.searchResults.length : 0) + " 条结果"
            color: textMuted
        }

        // 结果列表
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: cardBg
            border.color: "#1f2937"
            border.width: 1
            radius: 10

            ScrollView {
                anchors.fill: parent
                clip: true

                ListView {
                    id: resultListView
                    width: parent.width
                    height: contentHeight
                    model: searchVM.searchResults
                    spacing: 8

                    delegate: Rectangle {
                        width: resultListView.width - 16
                        height: 60
                        color: "#1f2937"
                        radius: 6

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 12

                            ColumnLayout {
                                Layout.fillWidth: true

                                Text {
                                    text: (modelData && modelData.key) ? modelData.key : "未知"
                                    color: primaryColor
                                    font.bold: true
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }

                                Text {
                                    text: "值：" + ((modelData && modelData.value) ? modelData.value : "")
                                    color: textMuted
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                            }

                            Button {
                                text: "查看"
                                onClicked: {
                                    selectedTitle = (modelData && modelData.key) ? modelData.key : ""
                                    selectedContent = (modelData && modelData.value) ? modelData.value : ""
                                    detailDialog.open()
                                }
                                background: Rectangle { color: accentColor; radius: 4 }
                                contentItem: Text { text: "查看"; color: "#fff"; anchors.centerIn: parent }
                            }
                        }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: searchField.text === "" ? "请输入关键字搜索" : "未找到结果"
                        color: textMuted
                        visible: resultListView.count === 0
                    }
                }
            }
        }
    }

    // 详情对话框
    Dialog {
        id: detailDialog
        modal: true
        width: 500
        height: 400
        parent: Overlay.overlay
        background: Rectangle { color: cardBg; border.color: primaryColor; border.width: 2; radius: 10 }
        header: Text { text: selectedTitle; color: primaryColor; font.bold: true; anchors.centerIn: parent }
        contentItem: ScrollView {
            Text { text: selectedContent; color: textColor; wrapMode: Text.Wrap; width: parent.width }
        }
        footer: Button {
            text: "关闭"
            onClicked: detailDialog.close()
            background: Rectangle { color: primaryColor; radius: 6 }
            contentItem: Text { text: "关闭"; color: "#000"; anchors.centerIn: parent }
        }
    }

    // 关于对话框
    Dialog {
        id: aboutDialog
        modal: true
        width: 400
        height: 300
        parent: Overlay.overlay
        visible: aboutVisible
        onVisibleChanged: if (!visible) aboutVisible = false
        title: "关于"
        standardButtons: Dialog.Close
        background: Rectangle { color: cardBg; border.color: accentColor; border.width: 2; radius: 10 }
        contentItem: ColumnLayout {
            Text { text: "ConfigWatcher"; color: primaryColor; font.pixelSize: 24; font.bold: true }
            Text { text: "AOI 属性快搜系统"; color: textMuted }
        }
    }

    function doSearch() {
        searchVM.searchText = searchField.text
        searchVM.searchMode = searchModeCombo.currentIndex
        searchVM.updateSearchResults()
    }
}
