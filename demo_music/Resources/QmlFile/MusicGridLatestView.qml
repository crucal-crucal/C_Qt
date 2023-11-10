// MusicGridLatestView.qml

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQml 2.3

Item {

    property alias list: gridRepater.model

    Grid {
        id: gridLayout
        anchors.fill: parent
        columns: 3
        // 可以构造相同格式的组件
        Repeater {
            id: gridRepater
            Frame {
                padding: 5
                width: parent.width * 0.333
                height: parent.width * 0.1
                background: Rectangle {
                    id: background
                    color: "#00000000"
                }
                clip: true

                MusicBorderImage {
                    id: img
                    width: parent.width * 0.25
                    height: parent.width * 0.25
                    imgSrc: modelData.album.picUrl
                }

                Text {
                    id: name
                    anchors {
                        left: img.right
                        verticalCenter: parent.verticalCenter
                        bottomMargin: 10
                        leftMargin: 5
                        horizontalCenter: parent.horizontalCenter
                    }
                    text: modelData.album.name
                    font.family: window.mFONT_FAMILY
                    font.pointSize: 11
                    height: 30
                    width: parent.width * 0.72
                    // 超出部分自动省略
                    elide: Qt.ElideMiddle
                    color: "#eeffffff"
                }

                Text {
                    anchors {
                        left: img.right
                        top: name.bottom
                        leftMargin: 5
                    }
                    text: modelData.artists[0].name
                    font.family: window.mFONT_FAMILY
                    height: 30
                    width: parent.width * 0.72
                    // 超出部分自动省略
                    elide: Qt.ElideRight
                    color: "#eeffffff"
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
