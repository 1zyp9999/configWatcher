import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import ConfigWatcher 1.0

Item {
    id: loginPage
    // 防护：parent 可能未初始化，使用默认值并在 Component.onCompleted 时再调整
    property int defaultWidth: 800
    property int defaultHeight: 600
    width: (parent && typeof parent.width !== 'undefined') ? parent.width : defaultWidth
    height: (parent && typeof parent.height !== 'undefined') ? parent.height : defaultHeight
    property StackView stackView: null

    // ====== 透明背景层 ======
    Rectangle {
        anchors.fill: parent
        color: "transparent"
        z: -1
    }

    // 背景图片（半透明）
    Image {
        id: bgImage
        anchors.fill: parent
        source: "qrc:/images/login_background.png"
        fillMode: Image.AspectFill
        opacity: 1.0
        z: 0
        onStatusChanged: {
            if (status === Image.Error) bgImage.visible = false;
        }
    }

    // ====== 登录卡片 ======
    Rectangle {
        id: loginCard
        // 使用 loginPage（根 Item）的宽高作为参考，避免 parent 未初始化时出现 undefined
        width: Math.round(loginPage.width * 0.36 * 0.7 * 0.8)
        height: Math.round(loginPage.height * 0.62 * 0.7 * 0.8)
        x: Math.round(loginPage.width - width - 60) // 右侧留 60px 间距
        y: Math.round((loginPage.height - height) / 2)
        radius: 18 * 0.7 * 0.8
        opacity: 0.98
        color: "#0b1220cc"   // 深色半透明
        border.color: "#FFFFFFCC" // 白色半透明，显眼
        border.width: 1.2

        // 卡片阴影（简约浅色）
        Rectangle {
            anchors.fill: parent
            radius: 18 * 0.7 * 0.8
            color: "#000"
            opacity: 0.28
            z: -1
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 36 * 0.7 * 0.8
            spacing: 24 * 0.7 * 0.8

            ColumnLayout {
                Layout.alignment: Qt.AlignCenter
                spacing: 8 * 0.7

                Text {
                    text: qsTr("CONFIGWATCHER")
                    font.pointSize: 30 * 0.7
                    font.bold: true
                    color: "#d3d7de"  // 亮银色
                    Layout.alignment: Qt.AlignHCenter
                }

                Text {
                    text: qsTr("AOI属性快搜软件")
                    font.pointSize: 14 * 0.7
                    color: "#bfc4cc"
                    Layout.alignment: Qt.AlignHCenter
                }
            }

            TextField {
                id: usernameField
                // 避免对 loginVM.username 做双向绑定导致 binding loop
                text: ""
                Component.onCompleted: {
                    if (loginVM.username !== undefined && loginVM.username !== "") usernameField.text = loginVM.username;
                    else usernameField.text = "admin";
                }
                onTextChanged: loginVM.username = text
                placeholderText: qsTr("请输入用户名")
                font.pointSize: 15 * 0.7
                Layout.fillWidth: true
                height: 48 * 0.7
                color: "#d3d7de"
                background: Rectangle {
                    radius: 10 * 0.7
                    border.color: "#FFFFFFCC"  // 只改边框颜色为白色半透明
                    border.width: 1.2
                    color: activeFocus ? "#081221" : "#07101a"
                }
            }

            TextField {
                id: passwordField
                // 同样避免直接绑定 password
                text: ""
                Component.onCompleted: {
                    if (loginVM.password !== undefined) passwordField.text = loginVM.password;
                }
                onTextChanged: loginVM.password = text
                placeholderText: qsTr("请输入密码")
                font.pointSize: 15 * 0.7
                echoMode: TextField.Password
                Layout.fillWidth: true
                height: 48 * 0.7
                color: "#d3d7de"
                background: Rectangle {
                    radius: 10 * 0.7
                    border.color: "#FFFFFFCC"  // 只改边框颜色为白色半透明
                    border.width: 1.2
                    color: activeFocus ? "#081221" : "#07101a"
                }
                // 更可靠的回车处理（TextField 的 onAccepted）
                onAccepted: loginButton.onClicked()
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight
                spacing: 8 * 0.7

                CheckBox {
                    id: rememberCheck
                    checked: loginVM.rememberPassword
                    onCheckedChanged: loginVM.rememberPassword = checked
                    // 缩小复选框显示尺寸
                    scale: 0.8
                    Layout.preferredWidth: 18
                    Layout.preferredHeight: 18
                }

                Text {
                    text: qsTr("记住密码")
                    font.pointSize: 13 * 0.7
                    color: "#d3d7de"
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Button {
                id: loginButton
                text: qsTr("登 录")
                font.pointSize: 16 * 0.7
                font.bold: true
                height: 44  // 增高按钮
                Layout.alignment: Qt.AlignHCenter
                Layout.fillWidth: true   // 宽度与登陆框一致
                background: Rectangle {
                    radius: 10
                    color: "#00000088" // 黑色半透明
                    border.color: "#FFFFFFCC" // 白色半透明，更显眼
                    border.width: 1.6
                }
                contentItem: Text {
                    text: parent.text
                    font.pointSize: parent.font.pointSize
                    font.bold: parent.font.bold
                    color: "#d3d7de" // 亮银色文字
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.fill: parent
                }
                onClicked: {
                    if (loginVM.checkLogin() && stackView) {
                        stackView.push("qrc:/qml/MainPage.qml");
                    }
                }
            }

            Text {
                text: loginVM.errorMessage
                font.pointSize: 13 * 0.7
                color: "#e53935"
                Layout.alignment: Qt.AlignCenter
                visible: text !== ""
            }
        }
    }

    // ====== 视图模型 ======
    LoginViewModel {
        id: loginVM
    }
}
