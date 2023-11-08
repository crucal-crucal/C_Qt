// DetailHistoryPageView

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Rectangle {
    Layout.fillWidth: true
    width: parent.width
    height: 60
    color: "#00000000"

    Text {
        x: 10
        verticalAlignment: Text.AlignBottom
        text: qsTr("历史播放")
        font.family: window.mFONT_FAMILY
        font.pointSize: 25
    }
}
