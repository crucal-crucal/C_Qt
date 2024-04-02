// 圆角图片

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.15

Item {
    property string imgSrc: "qrc:/images/player"

    property int borderRadius: 5

    Image {
        id: image
        anchors.centerIn: parent
        source: imgSrc
        smooth: true
        visible: false
        width: parent.width
        height: parent.height
        // 保持长宽比来裁剪
        fillMode: Image.PreserveAspectCrop
        antialiasing: true
    }

    Rectangle {
        id: mask
        color: "black"
        anchors.fill: parent
        radius: borderRadius
        visible: false
        antialiasing: true
    }

    OpacityMask {
        anchors.fill: image
        source: image
        maskSource: mask
        visible: true
        // 抗锯齿
        antialiasing: true
    }
}
