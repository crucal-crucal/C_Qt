// 自定义ToolButton

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

ToolButton {

    property string iconSource: ""

    property string toolTip: ""

    property bool isCanCheckable: false
    property bool isCanChecked: false

    id: self

    icon.source: iconSource

    MusicToolTip {
        visible: parent.hovered
        text: toolTip
    }

    width: 32
    height: 32

    background: Rectangle {
        color: self.down || (isCanCheckable && self.checked) ? "#eeeeee" : "#00000000"
    }

    icon.color: self.down || (isCanCheckable && self.checked) ? "#00000000" : "#eeeeee"

    checkable: isCanCheckable
    checked: isCanChecked
}
