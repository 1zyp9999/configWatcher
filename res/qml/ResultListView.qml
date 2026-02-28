import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


Rectangle {
    id: resultListView
    color: "transparent"
    width: parent.width
    height: parent.height

    property var modelData: []
    property string selectedTitle: ""
    property string selectedContent: ""
    property string selectedFormat: ""

    signal itemSelected(string title, string content, string format)

    ListView {
        id: listView
        anchors.fill: parent
        spacing: 8
        model: resultListView.modelData
        clip: true

        delegate: Rectangle {
            width: listView.width - 16
            height: 48
            radius: Styles.radiusSmall
            color: "#000000CC"
            border.color: Styles.borderColor
            border.width: 1
            anchors.leftMargin: 8
            anchors.rightMargin: 8

            RowLayout {
                anchors.fill: parent
                anchors.margins: 8
                spacing: 12

                Text {
                    id: fieldName
                    text: modelData?.chineseKey || modelData?.chinese || modelData?.key || modelData?.name || qsTr("未知字段")
                    color: Styles.textColor
                    font.pointSize: Styles.fontSizeMedium
                    font.bold: true
                    elide: Text.ElideRight
                    Layout.preferredWidth: listView.width * 0.45
                }

                RowLayout {
                    spacing: 8
                    Layout.alignment: Qt.AlignRight

                    Button {
                        text: qsTr("值")
                        Layout.preferredWidth: 56
                        height: 28

                        onClicked: {
                            resultListView.itemSelected(
                                qsTr("值：") + (modelData?.key || ""),
                                modelData?.value || modelData?.raw_value || "",
                                modelData?.format || modelData?.fileFormat || ""
                            )
                        }

                        background: Rectangle { 
                            radius: Styles.radiusSmall
                            color: Styles.primaryColor
                            border.color: Styles.primaryDark
                        }

                        contentItem: Text { 
                            text: parent.text
                            color: "#fff"
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    Button {
                        text: qsTr("中文名")
                        Layout.preferredWidth: 72
                        height: 28

                        onClicked: {
                            resultListView.itemSelected(
                                qsTr("中文名：") + (modelData?.key || ""),
                                modelData?.chineseKey || modelData?.chinese || "",
                                modelData?.format || modelData?.fileFormat || ""
                            )
                        }

                        background: Rectangle { 
                            radius: Styles.radiusSmall
                            color: Styles.successColor
                            border.color: "#059669"
                        }

                        contentItem: Text { 
                            text: parent.text
                            color: "#fff"
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    Button {
                        text: qsTr("含义")
                        Layout.preferredWidth: 56
                        height: 28

                        onClicked: {
                            resultListView.itemSelected(
                                qsTr("含义：") + (modelData?.key || ""),
                                modelData?.description || modelData?.chinese || "",
                                modelData?.format || modelData?.fileFormat || ""
                            )
                        }

                        background: Rectangle { 
                            radius: Styles.radiusSmall
                            color: Styles.warningColor
                            border.color: "#d97706"
                        }

                        contentItem: Text { 
                            text: parent.text
                            color: "#fff"
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }
        }

        // 空状态提示
        Text {
            anchors.centerIn: parent
            text: qsTr("暂无搜索结果")
            color: Styles.textMuted
            font.pointSize: Styles.fontSizeMedium
            visible: listView.count === 0
        }
    }
}
