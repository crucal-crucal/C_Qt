// DetailSearchPageView

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

ColumnLayout {

    Layout.fillWidth: true
    Layout.fillHeight: true

    Rectangle {
        Layout.fillWidth: true
        width: parent.width
        height: 60
        color: "#00000000"

        Text {
            x: 10
            verticalAlignment: Text.AlignBottom
            text: qsTr("搜索音乐")
            font.family: window.mFONT_FAMILY
            font.pointSize: 25
        }
    }

    RowLayout {
        Layout.fillWidth: true

        TextField {
            id: searchInput
            font.family: window.mFONT_FAMILY
            font.pointSize: 14
            selectByMouse: true
            selectionColor: "#999999"
            placeholderText: qsTr("请输入搜索关键词")
            color: "#000000"
            background: Rectangle {
                color: "#00000000"
                opacity: 0.5
                implicitHeight: 40
                implicitWidth: 400
            }
            focus: true
            Keys.onPressed: {
                if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return) {
                    doSearch()
                }
            }
        }

        MusicIconButton {
            iconSource: "qrc:images/search"
            toolTip: "搜索"
            onClicked: {
                doSearch()
            }
        }
    }

    MusicListView {
        id: musicListView
        onLoadMore: doSearch(offset, current)
        Layout.topMargin: 10
    }

    function doSearch(offset = 0, current = 0) {
        var keywords = searchInput.text
        if (keywords.length < 1) {
            return
        }

        function onReply(reply) {
            http.onReplySignal.disconnect(onReply)
            var result = JSON.parse(reply).result
            // 将 string 转成 Json
            var songsList = JSON.parse(reply).result.songs
            musicListView.current = current
            musicListView.all = result.songCount
            musicListView.musicList = songsList.map(item => {
                                                        return {
                                                            id: item.id,
                                                            name: item.name,
                                                            artist: item.artists[0].name,
                                                            album: item.album.name,
                                                            cover: ""
                                                        }
                                                    })
        }

        http.onReplySignal.connect(onReply)
        http.connect("search?keywords=" + keywords + "&offset=" + offset + "&limit=60")
    }
}
