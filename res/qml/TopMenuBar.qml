import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


Rectangle {
    id: topMenuBar
    height: 40
    color: Styles.boxColor
    radius: Styles.radiusSmall
    border.color: Styles.borderColor
    border.width: 1

    signal menuClicked(string label)

    RowLayout {
        anchors.fill: parent
        anchors.margins: 8
        spacing: 12

        Repeater {
            model: ["开始", "系统", "修改", "帮助", "关于"]
            delegate: Rectangle {
                id: menuItemRect
                color: "transparent"
                radius: Styles.radiusSmall
                Layout.preferredWidth: menuText.paintedWidth + 20
                Layout.preferredHeight: topMenuBar.height - 16

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    property string label: modelData
                    onClicked: topMenuBar.menuClicked(label)
                    onEntered: menuItemRect.color = Styles.boxColorSolid
                    onExited: menuItemRect.color = "transparent"
                }

                Text {
                    id: menuText
                    text: modelData
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    color: Styles.textColor
                    font.pointSize: Styles.fontSizeMedium
                }
            }
        }

        // 文件选择按钮
        Rectangle {
            id: fileMenuBtnRect
            color: "transparent"
            radius: Styles.radiusSmall
            Layout.preferredWidth: fileMenuText.paintedWidth + 20
            Layout.preferredHeight: topMenuBar.height - 16
            
            visible: showFileButton
            property bool showFileButton: false

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: fileButtonClicked()
                onEntered: fileMenuBtnRect.color = Styles.boxColorSolid
                onExited: fileMenuBtnRect.color = "transparent"
            }
            
            Text { 
                id: fileMenuText
                text: qsTr("文件")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 8
                color: Styles.textColor
                font.pointSize: Styles.fontSizeMedium
            }
        }

        signal fileButtonClicked()

        // 占位，推动内容靠右
        Item { Layout.fillWidth: true }
    }
}
