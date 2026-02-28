import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


Rectangle {
    id: toolbarCard
    color: "#23272fcc"
    radius: Styles.radiusLarge
    border.color: Styles.primaryColor
    border.width: 1
    height: 72

    signal searchRequested(string text)
    signal clearRequested()
    signal suggestRequested(string text)
    signal typeChanged(string type)
    signal lightClicked()
    signal cameraClicked()

    property alias searchText: searchField.text
    property alias searchModeIndex: searchModeCombo.currentIndex
    property alias configTypeIndex: configTypeCombo.currentIndex
    property alias suffixIndex: suffixCombo.currentIndex

    RowLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 16

        // 光源按钮
        Rectangle {
            width: 36; height: 36
            color: "transparent"
            radius: Styles.radiusSmall
            border.color: "#fbbf24"
            border.width: 1

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: toolbarCard.lightClicked()
            }

            Canvas {
                anchors.fill: parent
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.clearRect(0,0,width,height);
                    ctx.save();
                    ctx.translate(width/2, height/2);
                    ctx.beginPath();
                    ctx.arc(0, -5, 12, Math.PI*0.15, Math.PI*0.85, false);
                    ctx.bezierCurveTo(-12, 7, 12, 7, 0, -5);
                    ctx.closePath();
                    ctx.fillStyle = "#fde68a";
                    ctx.strokeStyle = "#fbbf24";
                    ctx.lineWidth = 2.2;
                    ctx.fill(); ctx.stroke();
                    ctx.beginPath();
                    ctx.moveTo(-5, 6); ctx.lineTo(0, 2); ctx.lineTo(5, 6);
                    ctx.strokeStyle = "#f59e42";
                    ctx.lineWidth = 2;
                    ctx.stroke();
                    ctx.beginPath();
                    ctx.rect(-5, 9, 10, 5);
                    ctx.fillStyle = "#fbbf24";
                    ctx.fill(); ctx.stroke();
                    ctx.beginPath();
                    ctx.strokeStyle = "#fde68a";
                    ctx.lineWidth = 1.5;
                    for (var i=0;i<8;i++) {
                        var angle = Math.PI*2*i/8;
                        ctx.moveTo(Math.cos(angle)*13, Math.sin(angle)*13-5);
                        ctx.lineTo(Math.cos(angle)*17, Math.sin(angle)*17-5);
                    }
                    ctx.stroke();
                    ctx.restore();
                }
            }

            ToolTip.visible: parent.MouseArea && parent.MouseArea.containsMouse
            ToolTip.text: qsTr("插入 light")
        }

        // 相机按钮
        Rectangle {
            width: 36; height: 36
            color: "transparent"
            radius: Styles.radiusSmall
            border.color: Styles.primaryColor
            border.width: 1

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: toolbarCard.cameraClicked()
            }

            Canvas {
                anchors.fill: parent
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.clearRect(0,0,width,height);
                    ctx.strokeStyle = Styles.primaryColor;
                    ctx.lineWidth = 2;
                    ctx.strokeRect(6, 12, 24, 16);
                    ctx.beginPath();
                    ctx.arc(18, 20, 6, 0, 2*Math.PI);
                    ctx.stroke();
                    ctx.beginPath();
                    ctx.moveTo(10, 12);
                    ctx.lineTo(26, 12);
                    ctx.stroke();
                }
            }

            ToolTip.visible: parent.MouseArea && parent.MouseArea.containsMouse
            ToolTip.text: qsTr("插入 camera")
        }

        // 配置类型选择
        ComboBox {
            id: configTypeCombo
            model: ["相机", "投影", "用户配置", "调整配置", "hardware 配置", "标定配置"]
            Layout.preferredWidth: 120
            font.pointSize: Styles.fontSizeMedium

            background: Rectangle {
                color: Styles.inputBackground
                radius: Styles.radiusMedium
                border.color: "#cbd5e1"
                border.width: 1
            }

            contentItem: Text {
                text: configTypeCombo.currentText
                color: Styles.inputText
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.right: parent.right
            }
        }

        // 后缀选择
        ComboBox {
            id: suffixCombo
            model: ["ini", "xml", "ccf"]
            Layout.preferredWidth: 70
            font.pointSize: Styles.fontSizeMedium
            currentIndex: 0

            background: Rectangle {
                color: Styles.inputBackground
                radius: Styles.radiusMedium
                border.color: "#cbd5e1"
                border.width: 1
            }

            contentItem: Text { 
                text: suffixCombo.currentText
                color: Styles.inputText
                verticalAlignment: Text.AlignVCenter
                anchors.left: parent.left
                anchors.leftMargin: 8
            }
        }

        // 搜索框
        TextField {
            id: searchField
            placeholderText: qsTr("搜索字段名/值（支持中文）...")
            Layout.preferredWidth: 220
            height: 32
            font.pointSize: Styles.fontSizeMedium
            color: Styles.inputText

            onAccepted: toolbarCard.searchRequested(text)

            background: Rectangle {
                color: Styles.inputBackground
                radius: Styles.radiusMedium
                border.width: 1
                border.color: "#cbd5e1"
            }
        }

        // 搜索模式
        ComboBox {
            id: searchModeCombo
            model: [qsTr("模糊搜索"), qsTr("精准搜索")]
            Layout.preferredWidth: 90
            font.pointSize: Styles.fontSizeMedium
            currentIndex: 0

            background: Rectangle {
                color: Styles.inputBackground
                radius: Styles.radiusMedium
                border.color: "#cbd5e1"
                border.width: 1
            }

            contentItem: Text { 
                text: searchModeCombo.currentText
                color: Styles.inputText
                verticalAlignment: Text.AlignVCenter
                anchors.left: parent.left
                anchors.leftMargin: 8
            }
        }

        // 联想按钮
        Button {
            id: suggestBtn
            text: qsTr("联想")
            font.pointSize: Styles.fontSizeMedium
            height: 32
            Layout.preferredWidth: 72

            onClicked: toolbarCard.suggestRequested(searchField.text)

            background: Rectangle { 
                radius: Styles.radiusMedium
                color: "#9CA3AF"
                border.color: "#6B7280"
                border.width: 1
            }

            contentItem: Text { 
                text: parent.text
                color: Styles.backgroundColor
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        // 搜索按钮
        Button {
            id: searchButton
            text: qsTr("搜索")
            font.pointSize: Styles.fontSizeMedium
            height: 32

            onClicked: toolbarCard.searchRequested(searchField.text)

            background: Rectangle {
                radius: Styles.radiusMedium
                gradient: Gradient {
                    GradientStop { position: 0.0; color: Styles.primaryColor }
                    GradientStop { position: 1.0; color: Styles.accentColor }
                }
                border.color: Styles.primaryColor
                border.width: 1
            }

            contentItem: Text {
                text: parent.text
                color: Styles.textColor
                font.pointSize: parent.font.pointSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
            }
        }

        // 清空按钮
        Button {
            text: qsTr("清空")
            font.pointSize: Styles.fontSizeMedium
            height: 32

            onClicked: toolbarCard.clearRequested()

            background: Rectangle {
                radius: Styles.radiusMedium
                gradient: Gradient {
                    GradientStop { position: 0.0; color: Styles.primaryColor }
                    GradientStop { position: 1.0; color: Styles.accentColor }
                }
                border.color: Styles.primaryColor
                border.width: 1
            }

            contentItem: Text {
                text: parent.text
                color: "#fff"
                font.pointSize: parent.font.pointSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
            }
        }
    }
}
