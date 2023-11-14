// MusicToolTip.qml

import QtQuick 2.15

Rectangle {

    property alias text: content.text
    property int margin: 15

    id: self

    color: "white"
    radius: 4
    width: content.width + 20
    height: content.height + 20

    anchors {
        top: getGlobalPosition(parent).y + parent.height + margin + height < window.height ? parent.bottom : undefined
        bottom: getGlobalPosition(parent).y + parent.height + margin + height >= window.height ? parent.top : undefined

        left: (width - parent.width) / 2 > getGlobalPosition(parent).x ? parent.left : undefined
        right: width - getGlobalPosition(parent).width > window.width ? parent.right : undefined

        topMargin: margin
        bottomMargin: margin
    }

    x: (width - parent.width) / 2 <= getGlobalPosition(parent).x && width - getGlobalPosition(parent).width <= window.width ? (-width + parent.width) / 2 : 0

    Text {
        id: content
        text: qsTr("这是一段提示文字")
        lineHeight: 1.2
        anchors.centerIn: parent
        font.family: window.mFONT_FAMILY

    }

    function getGlobalPosition(targetObject) {
        var positionX = 0
        var positionY = 0
        var obj = targetObject        /* 遍历所有的父窗口 */
        while (obj !== null) {        /* 累加计算坐标 */
            positionX += obj.x
            positionY += obj.y
            obj = obj.parent
        }
        return {"x": positionX, "y": positionY}
    }
}
