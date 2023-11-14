// 自定义Button

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Button {

    property string iconSource: ""

    property string toolTip: ""

    property bool isCanCheckable: false
    property bool isCanChecked: false

    property int iconWidth: 32
    property int iconHeight: 32

    id: self

    icon.source: iconSource
    icon.width: iconWidth
    icon.height: iconHeight

    MusicToolTip {
        visible: parent.hovered
        text: toolTip
    }

    background: Rectangle {
        color: self.down || (isCanCheckable && self.checked) ? "#497563" : "#20e9f4ff"
        radius: 3
    }

    icon.color: self.down || (isCanCheckable && self.checked) ? "#ffffff" : "#e2f0f8"

    checkable: isCanCheckable
    checked: isCanChecked
}
