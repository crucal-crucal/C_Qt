// 工具栏

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3

ToolBar {
    background: Rectangle {
        color: "#00AAAA"
    }

    width: parent.width
    Layout.fillWidth: true
    RowLayout {
        anchors.fill: parent

        MusicToolButton {
            iconSource: "qrc:/images/music"
            toolTip: "关于"

            onClicked: {
                aboutPop.open()
            }
        }
        MusicToolButton {
            iconSource: "qrc:/images/about"
            toolTip: "CRUCAL"

            onClicked: {
                Qt.openUrlExternally("https://gitee.com/crucal/Qt6_Qt5/tree/master/demo_music")
            }
        }
        MusicToolButton {
            id: smallWindow
            iconSource: "qrc:/images/small-window"
            toolTip: "小窗播放"

            onClicked: {
                setWindowSize(330, 650)

                normalWindow.visible = true
                smallWindow.visible = false
            }
        }
        MusicToolButton {
            id: normalWindow
            iconSource: "qrc:/images/exit-small-window"
            toolTip: "退出小窗播放"
            visible: false

            onClicked: {
                setWindowSize()
                normalWindow.visible = false
                smallWindow.visible = true
            }
        }
        Item {
            Layout.fillWidth: true
            height: parent.height
            Text {
                anchors.centerIn: parent
                text: qsTr("crucal")
                font.family: window.mFONT_FAMILY
                font.pointSize: 15
                color: "#ffffff"
            }
        }
        MusicToolButton {
            iconSource: "qrc:/images/minimize-screen"
            toolTip: "最小化"

            onClicked: {
                window.hide()
            }
        }
        MusicToolButton {
            id: maxWindow
            iconSource: "qrc:/images/full-screen"
            toolTip: "全屏"

            onClicked: {
                window.visibility = Window.Maximized
                maxWindow.visible = false
                resize.visible = true
            }
        }
        MusicToolButton {
            id: resize
            iconSource: "qrc:/images/small-screen"
            toolTip: "退出全屏"
            visible: false

            onClicked: {
                window.visibility = Window.AutomaticVisibility
                setWindowSize()
                maxWindow.visible = true
                resize.visible = false
            }
        }
        MusicToolButton {
            iconSource: "qrc:/images/power"
            toolTip: "退出"

            onClicked: {
                Qt.quit()
            }
        }
    }

    Popup {
        id: aboutPop

        parent: Overlay.overlay
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        width: 250
        height: 230

        background: Rectangle {
            color: "#e9f4ff"
            radius: 5
            border.color: "#2273a7ab"
        }

        contentItem: ColumnLayout {
            width: parent.width
            height: parent.height
            Layout.alignment: Qt.AlignHCenter

            Image {
                Layout.preferredHeight: 60
                source: "qrc:/images/music"
                Layout.fillWidth: true
                fillMode: Image.PreserveAspectFit
            }

            Text {
                text: qsTr("crucal")
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 18
                color: "#8573a7ab"
                font.family: window.mFONT_FAMILY
                font.bold: true
            }

            Text {
                text: qsTr("这是我的Cloud Music Player")
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 16
                color: "#8573a7ab"
                font.family: window.mFONT_FAMILY
                font.bold: true
            }

            Text {
                text: qsTr("https://gitee.com/")
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 16
                color: "#8573a7ab"
                font.family:  window.mFONT_FAMILY
                font.bold: true
            }
        }
    }

    function setWindowSize(width = window.mWINDOW_WIDTH, height = window.mWINDOW_HEIGHT) {
        window.width = width
        window.height = height
//                window.x = (Screen.desktopAvailableWidth - window.width) / 2
//                window.y = (Screen.desktopAvailableHeight - window.height) / 2
    }
}
