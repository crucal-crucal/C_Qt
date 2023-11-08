// MusicGridHotView.qml

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQml 2.3

Item {

    property alias list: gridRepater.model

    Grid {
        id: gridLayout
        anchors.fill: parent
        columns: 5
        // 可以构造相同格式的组件
        Repeater {
            id: gridRepater
            model: []
            Frame {
                padding: 10
                width: parent.width * 0.2
                height: parent.width * 0.2 + 30
                background: Rectangle {
                    id: background
                    color: "#00000000"
                }
                clip: true

                MusicRoundImage {
                    id: img
                    width: parent.width
                    height: parent.width
                    imgSrc: modelData.coverImgUrl
                }

                Text {
                    anchors {
                        top: img.bottom
                        horizontalCenter: parent.horizontalCenter
                    }
                    text: modelData.name
                    font.family: window.mFONT_FAMILY
                    height: 30
                    width: parent.width
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    // 超出部分自动省略
                    elide: Qt.ElideMiddle
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onEntered: {
                        background.color = "#50000000"
                    }

                    onExited: {
                        background.color = "#00000000"
                    }
                }
            }
        }
    }
}
