pragma Singleton
import QtQuick 2.15

QtObject {
    // 颜色定义
    readonly property color primaryColor: "#2196F3"
    readonly property color primaryDark: "#1976D2"
    readonly property color accentColor: "#5eead4"
    readonly property color backgroundColor: "#07101a"
    readonly property color boxColor: "#0b1220cc"
    readonly property color boxColorSolid: "#0b1220"
    readonly property color textColor: "#d3d7de"
    readonly property color textMuted: "#bfc4cc"
    readonly property color borderColor: "#1f2937"
    readonly property color inputBackground: "#E5E7EBCC"
    readonly property color inputText: "#2f2f2f"
    readonly property color errorColor: "#e53935"
    readonly property color successColor: "#10b981"
    readonly property color warningColor: "#f59e0b"

    // 尺寸定义
    readonly property real radiusSmall: 6
    readonly property real radiusMedium: 10
    readonly property real radiusLarge: 14
    readonly property real radiusXLarge: 18

    // 间距定义
    readonly property real spacingSmall: 8
    readonly property real spacingMedium: 16
    readonly property real spacingLarge: 24

    // 字体大小
    readonly property real fontSizeSmall: 11
    readonly property real fontSizeMedium: 13
    readonly property real fontSizeLarge: 15
    readonly property real fontSizeXLarge: 16
    readonly property real fontSizeTitle: 30

    // 缩放因子（用于登录页面等特殊场景）
    readonly property real scaleFactor: 0.7 * 0.8

    // 阴影效果
    readonly property color shadowColor: "#000000"
    readonly property real shadowOpacity: 0.28
}
