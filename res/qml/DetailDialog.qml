import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


Dialog {
    id: detailDialog
    modal: true
    width: 500
    height: 400
    padding: Styles.spacingMedium
    
    property string dialogTitle: ""
    property string dialogContent: ""
    property string dialogFormat: ""
    
    title: dialogTitle
    
    background: Rectangle {
        color: Styles.boxColor
        radius: Styles.radiusLarge
        border.color: Styles.borderColor
        border.width: 1
    }
    
    header: Rectangle {
        color: "transparent"
        implicitHeight: 60
        
        Text {
            text: dialogTitle
            color: Styles.textColor
            font.pointSize: Styles.fontSizeXLarge
            font.bold: true
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    
    contentItem: ColumnLayout {
        spacing: Styles.spacingMedium
        
        // 内容显示区域
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: Styles.backgroundColor
            radius: Styles.radiusMedium
            border.color: Styles.borderColor
            border.width: 1
            
            ScrollView {
                anchors.fill: parent
                anchors.margins: Styles.spacingSmall
                clip: true
                
                Text {
                    width: parent.width - Styles.spacingSmall * 2
                    text: dialogContent
                    color: Styles.textColor
                    font.pointSize: Styles.fontSizeMedium
                    wrapMode: Text.Wrap
                }
            }
        }
        
        // 格式信息
        Text {
            text: dialogFormat ? qsTr("格式：%1").arg(dialogFormat) : ""
            color: Styles.textMuted
            font.pointSize: Styles.fontSizeSmall
            visible: dialogFormat !== ""
        }
    }
    
    footer: Rectangle {
        color: "transparent"
        implicitHeight: 50
        
        Button {
            anchors.centerIn: parent
            text: qsTr("关闭")
            font.pointSize: Styles.fontSizeMedium
            width: 100
            height: 36
            
            onClicked: detailDialog.close()
            
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
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
