import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import ConfigWatcher 1.0

Item {
    id: loginPage
    property int defaultWidth: 800
    property int defaultHeight: 600
    width: (parent && parent.width) ? parent.width : defaultWidth
    height: (parent && parent.height) ? parent.height : defaultHeight
    property StackView stackView: null

    // ========== 全屏背景：深色渐变 ==========
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#020617" }
            GradientStop { position: 0.4; color: "#0f172a" }
            GradientStop { position: 1.0; color: "#020617" }
        }
        z: -2
    }

    // 背景图（低透明度）
    Image {
        id: bgImage
        anchors.fill: parent
        source: "qrc:/images/login_background.png"
        fillMode: Image.AspectFill
        opacity: 0.12
        visible: status === Image.Ready
        z: -1
    }

    // ========== 左侧品牌区 ==========
    Item {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width * 0.55

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 16
            width: parent.width * 0.7

            // Logo 圆标
            Rectangle {
                Layout.alignment: Qt.AlignHCenter
                width: 72; height: 72; radius: 18
                color: "#2563eb"
                Text {
                    text: "CW"
                    anchors.centerIn: parent
                    color: "#ffffff"
                    font.pointSize: 26
                    font.bold: true
                }
            }

            // 主标题
            Text {
                text: "ConfigWatcher"
                font.pointSize: 36
                font.bold: true
                color: "#f1f5f9"
                Layout.alignment: Qt.AlignHCenter
            }

            // 副标题
            Text {
                text: qsTr("AOI 属性快搜 · 高效配置管理")
                font.pointSize: 15
                color: "#64748b"
                Layout.alignment: Qt.AlignHCenter
            }

            Item { height: 20 }

            // 特性标签
            Row {
                Layout.alignment: Qt.AlignHCenter
                spacing: 12

                Repeater {
                    model: [qsTr("快速检索"), qsTr("多格式支持"), qsTr("智能联想")]
                    delegate: Rectangle {
                        width: tagText.paintedWidth + 24
                        height: 30
                        radius: 15
                        color: "#1e293b"
                        border.color: "#334155"
                        border.width: 1
                        Text {
                            id: tagText
                            text: modelData
                            anchors.centerIn: parent
                            color: "#94a3b8"
                            font.pointSize: 11
                        }
                    }
                }
            }
        }
    }

    // ========== 右侧登录卡片 ==========
    Rectangle {
        id: loginCard
        width: Math.min(Math.round(loginPage.width * 0.34), 380)
        height: cardContent.implicitHeight + 72
        anchors.right: parent.right
        anchors.rightMargin: Math.round(loginPage.width * 0.06)
        anchors.verticalCenter: parent.verticalCenter
        radius: 16
        color: "#0f172a"
        border.color: "#1e293b"
        border.width: 1

        // 卡片顶部蓝色装饰条
        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 3
            radius: 16
            color: "#2563eb"
        }

        ColumnLayout {
            id: cardContent
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 32
            spacing: 20

            // 卡片标题
            Text {
                text: qsTr("欢迎登录")
                font.pointSize: 20
                font.bold: true
                color: "#f1f5f9"
                Layout.alignment: Qt.AlignLeft
            }
            Text {
                text: qsTr("请输入您的账号和密码")
                font.pointSize: 12
                color: "#64748b"
                Layout.alignment: Qt.AlignLeft
                Layout.bottomMargin: 4
            }

            // 用户名标签 + 输入框
            Text {
                text: qsTr("用户名")
                font.pointSize: 12
                color: "#94a3b8"
                Layout.bottomMargin: -14
            }
            TextField {
                id: usernameField
                text: ""
                Component.onCompleted: {
                    if (loginVM.username) text = loginVM.username
                    else text = "admin"
                }
                onTextChanged: loginVM.username = text
                placeholderText: qsTr("请输入用户名")
                placeholderTextColor: "#475569"
                font.pointSize: 14
                Layout.fillWidth: true
                height: 44
                color: "#e2e8f0"
                background: Rectangle {
                    radius: 8
                    color: "#1e293b"
                    border.color: usernameField.activeFocus ? "#2563eb" : "#334155"
                    border.width: usernameField.activeFocus ? 2 : 1
                }
            }

            // 密码标签 + 输入框
            Text {
                text: qsTr("密码")
                font.pointSize: 12
                color: "#94a3b8"
                Layout.bottomMargin: -14
            }
            TextField {
                id: passwordField
                text: loginVM.password || ""
                onTextChanged: loginVM.password = text
                placeholderText: qsTr("请输入密码")
                placeholderTextColor: "#475569"
                font.pointSize: 14
                echoMode: TextField.Password
                Layout.fillWidth: true
                height: 44
                color: "#e2e8f0"
                background: Rectangle {
                    radius: 8
                    color: "#1e293b"
                    border.color: passwordField.activeFocus ? "#2563eb" : "#334155"
                    border.width: passwordField.activeFocus ? 2 : 1
                }
                onAccepted: loginButton.clicked()
            }

            // 记住密码
            RowLayout {
                Layout.fillWidth: true
                spacing: 6
                CheckBox {
                    id: rememberCheck
                    checked: loginVM.rememberPassword
                    onCheckedChanged: loginVM.rememberPassword = checked
                    scale: 0.85
                }
                Text {
                    text: qsTr("记住密码")
                    font.pointSize: 12
                    color: "#64748b"
                }
                Item { Layout.fillWidth: true }
            }

            // 登录按钮
            Button {
                id: loginButton
                text: qsTr("登  录")
                font.pointSize: 15
                font.bold: true
                height: 48
                Layout.fillWidth: true
                background: Rectangle {
                    radius: 8
                    color: loginButton.pressed ? "#1d4ed8" : (loginButton.hovered ? "#3b82f6" : "#2563eb")
                }
                contentItem: Text {
                    text: parent.text
                    color: "#ffffff"
                    font.bold: true
                    font.pointSize: 15
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                onClicked: {
                    console.log("登录按钮被点击");
                    console.log("用户名:", usernameField.text);
                    console.log("密码:", passwordField.text);
                    console.log("stackView:", stackView);
                    var result = loginVM.checkLogin();
                    console.log("checkLogin 结果:", result);
                    if (result && stackView) {
                        console.log("准备跳转到主页面...");
                        try {
                            stackView.push("qrc:/qml/MainPage.qml");
                            console.log("跳转成功");
                        } catch(e) {
                            console.log("跳转失败:", e);
                        }
                    } else {
                        console.log("登录失败或 stackView 为空");
                    }
                }
            }

            // 错误信息
            Text {
                text: loginVM.errorMessage
                font.pointSize: 12
                color: "#ef4444"
                Layout.alignment: Qt.AlignCenter
                visible: text !== "" && text !== undefined
            }
        }
    }

    // ========== 底部版权 ==========
    Text {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        anchors.horizontalCenter: parent.horizontalCenter
        text: "© 2026 ConfigWatcher"
        font.pointSize: 11
        color: "#334155"
    }

    LoginViewModel {
        id: loginVM
    }
}
