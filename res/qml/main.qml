import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: rootWindow
    visible: true
    width: 1200
    height: 800
    color: "transparent"
    title: qsTr("ConfigWatcher - AOI 属性快搜软件")
    visibility: ApplicationWindow.Maximized

    // 精简模式切换信号，C++ 侧连接此信号
    signal requestMiniMode()

    StackView {
        id: mainStackView
        anchors.fill: parent
        initialItem: LoginPage {
            stackView: mainStackView
            width: rootWindow.width
            height: rootWindow.height
        }
    }
}
