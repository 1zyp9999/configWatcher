import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: rootWindow
    visible: true
    width: 1200
    height: 800
    color: "transparent"
    title: qsTr("ConfigWatcher - AOI属性快搜软件")

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
