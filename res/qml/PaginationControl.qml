import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


Rectangle {
    id: paginationControl
    height: 40
    color: "transparent"
    
    property int currentPage: 0
    property int totalPages: 0
    property int totalCount: 0
    
    signal pageChanged(int page)
    signal nextRequested()
    signal previousRequested()
    
    visible: totalPages > 1
    
    RowLayout {
        anchors.fill: parent
        spacing: 8
        
        // 上一页按钮
        Button {
            text: qsTr("上一页")
            font.pointSize: Styles.fontSizeMedium
            height: 32
            enabled: currentPage > 0
            
            onClicked: paginationControl.previousRequested()
            
            background: Rectangle {
                radius: Styles.radiusSmall
                color: parent.enabled ? Styles.primaryColor : "#6B7280"
                border.color: Styles.primaryDark
                border.width: 1
            }
            
            contentItem: Text {
                text: parent.text
                color: "#fff"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        
        // 页码显示
        Text {
            text: qsTr("第 %1 / %2 页").arg(currentPage + 1).arg(totalPages)
            color: Styles.textColor
            font.pointSize: Styles.fontSizeMedium
            Layout.alignment: Qt.AlignVCenter
        }
        
        // 总记录数
        Text {
            text: qsTr("共 %1 条").arg(totalCount)
            color: Styles.textMuted
            font.pointSize: Styles.fontSizeSmall
            Layout.alignment: Qt.AlignVCenter
        }
        
        Item { Layout.fillWidth: true }
        
        // 下一页按钮
        Button {
            text: qsTr("下一页")
            font.pointSize: Styles.fontSizeMedium
            height: 32
            enabled: currentPage < totalPages - 1
            
            onClicked: paginationControl.nextRequested()
            
            background: Rectangle {
                radius: Styles.radiusSmall
                color: parent.enabled ? Styles.primaryColor : "#6B7280"
                border.color: Styles.primaryDark
                border.width: 1
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
