// MusicListView.qml

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQml 2.3
import QtQuick.Shapes 1.15

Frame {

    property var musicList: []
    property int all: 0
    property int pageSize: 60
    property int current: 0

    property bool deleteable: true
    property bool favoriteable: true

    signal loadMore(int offset, int current)
    signal deleteItem(int index)

    onMusicListChanged: {
        listViewModel.clear()
        listViewModel.append(musicList)
    }

    Layout.fillHeight: true
    Layout.fillWidth: true
    clip: true
    spacing: 0
    padding: 0
    background: Rectangle {
        color: "#00000000"
    }

    ListView {
        id: listView
        anchors.fill: parent
        anchors.bottomMargin: 70
        model: ListModel {
            id: listViewModel
        }
        delegate: listViewDelegate
        ScrollBar.vertical: ScrollBar {
            anchors.right: parent.right
        }
        header: listViewHeader
        highlight: Rectangle{
            color: "#20f0f0f0"
        }
        highlightMoveDuration: 0
        highlightResizeDuration: 0
    }

    Component {
        id: listViewDelegate
        Rectangle {
            id: listViewDelegateItem
            //            color: "#aaa"
            height: 45
            width: listView.width
            color: "#00000000"

            Shape {
                anchors.fill: parent
                ShapePath {
                    strokeColor: "#50000000"
                    strokeStyle: ShapePath.SolidLine
                    startX: 0
                    startY: listViewDelegateItem.height
                    PathLine {
                        x: 0; y: listViewDelegateItem.height
                    }
                    PathLine {
                        x: listView.width; y: listViewDelegateItem.height
                    }
                }
            }

            MouseArea {
                onDoubleClicked: {
                    // 播放音乐
                    playMusic()
                }

                RowLayout {
                    width: parent.width
                    height: parent.height
                    // 元素间距
                    spacing: 15
                    // 缩进
                    x: 5
                    Text {
                        text: index + 1 + pageSize * current
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.preferredWidth: parent.width * 0.05
                        font.family: window.mFONT_FAMILY
                        font.pointSize: 13
                        color: "#eeffffff"
                        elide: Qt.ElideRight
                    }
                    Text {
                        text: name
                        Layout.preferredWidth: parent.width * 0.4
                        font.family: window.mFONT_FAMILY
                        font.pointSize: 13
                        color: "#eeffffff"
                        elide: Qt.ElideRight
                    }
                    Text {
                        text: artist
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.preferredWidth: parent.width * 0.15
                        font.family: window.mFONT_FAMILY
                        font.pointSize: 13
                        color: "#eeffffff"
                        elide: Qt.ElideMiddle
                    }
                    Text {
                        text: album
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.preferredWidth: parent.width * 0.15
                        font.family: window.mFONT_FAMILY
                        font.pointSize: 13
                        color: "#eeffffff"
                        elide: Qt.ElideMiddle
                    }
                    Item {
                        Layout.preferredWidth: parent.width * 0.15
                        RowLayout {
                            anchors.centerIn: parent
                            MusicIconButton {
                                iconSource: "qrc:/images/pause"
                                iconHeight: 16
                                iconWidth: 16
                                toolTip: "播放"
                                onClicked: {
                                    // 播放音乐
                                    playMusic()
                                }
                            }
                            MusicIconButton {
                                visible: favoriteable
                                iconSource: "qrc:/images/favorite"
                                iconHeight: 16
                                iconWidth: 16
                                toolTip: "喜欢"
                                onClicked: {
                                    // 喜欢
                                    console.log("喜欢id...", musicList[index].id)
                                    layoutBottomView.saveFavorite({
                                                                      id: musicList[index].id,
                                                                      name: musicList[index].name,
                                                                      artist: musicList[index].artist,
                                                                      url: musicList[index].url ? musicList[index].url : "",
                                                                      album: musicList[index].album,
                                                                      type: musicList[index].type ? musicList[index].type : "0"
                                                                  })
                                }
                            }
                            MusicIconButton {
                                visible: deleteable
                                iconSource: "qrc:/images/clear"
                                iconHeight: 16
                                iconWidth: 16
                                toolTip: "删除"
                                onClicked: {
                                    // 删除
                                    deleteItem(index)
                                }
                            }
                        }
                    }
                }

                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onEntered: {
                    color = "#20f0f0f0"
                }

                onExited: {
                    color = "#00000000"
                }

                onClicked: {
                    listViewDelegateItem.ListView.view.currentIndex = index
                }
            }
        }
    }

    Component {
        id: listViewHeader
        Rectangle {
            color: "#3000AAAA"
            height: 45
            width: listView.width
            RowLayout {
                width: parent.width
                height: parent.height
                // 元素间距
                spacing: 15
                // 缩进
                x: 5
                Text {
                    text: "序号"
                    horizontalAlignment: Qt.AlignHCenter
                    Layout.preferredWidth: parent.width * 0.05
                    font.family: window.mFONT_FAMILY
                    font.pointSize: 13
                    color: "#eeffffff"
                    elide: Qt.ElideRight
                }
                Text {
                    text: "歌名"
                    //                    horizontalAlignment: Qt.AlignHCenter
                    Layout.preferredWidth: parent.width * 0.4
                    font.family: window.mFONT_FAMILY
                    font.pointSize: 13
                    color: "#eeffffff"
                    elide: Qt.ElideRight
                }
                Text {
                    text: "歌手"
                    horizontalAlignment: Qt.AlignHCenter
                    Layout.preferredWidth: parent.width * 0.15
                    font.family: window.mFONT_FAMILY
                    font.pointSize: 13
                    color: "#eeffffff"
                    elide: Qt.ElideMiddle
                }
                Text {
                    text: "专辑"
                    horizontalAlignment: Qt.AlignHCenter
                    Layout.preferredWidth: parent.width * 0.15
                    font.family: window.mFONT_FAMILY
                    font.pointSize: 13
                    color: "#eeffffff"
                    elide: Qt.ElideMiddle
                }
                Text {
                    text: "操作"
                    horizontalAlignment: Qt.AlignHCenter
                    Layout.preferredWidth: parent.width * 0.15
                    font.family: window.mFONT_FAMILY
                    font.pointSize: 13
                    color: "#eeffffff"
                    elide: Qt.ElideRight
                }
            }
        }
    }

    Item {
        id: pageItem
        visible: musicList.length !== 0 && all !== 0
        width: parent.width
        height: 40
        anchors.top: listView.bottom
        anchors.topMargin: 20

        ButtonGroup {
            buttons: buttons.children
        }
        RowLayout {
            id: buttons
            anchors.centerIn: parent
            Repeater {
                id: repeater
                model: all / pageSize > 9 ? 9 : all / pageSize
                Button {
                    Text {
                        anchors.centerIn: parent
                        text: modelData + 1
                        font.family: window.mFONT_FAMILY
                        font.pointSize: 14
                        color: checked ? "#497563" : "#eeffffff"
                    }
                    background: Rectangle {
                        implicitHeight: 30
                        implicitWidth: 30
                        color: checked ? "#e2f0f8" : "#20e9f4ff"
                        radius: 3
                    }
                    checkable: true
                    checked: modelData === current
                    onClicked: {
                        if (current === index) return
                        loadMore(current * pageSize, index)
                    }
                }
            }
        }
    }

    function playMusic() {
        // 播放音乐
        layoutBottomView.current = -1
        layoutBottomView.playList = musicList
        layoutBottomView.current = index
    }
}
