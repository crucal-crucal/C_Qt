// DetailPlayListPageView

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

ColumnLayout {

    property string targetId: ""
    property string targetType: "10" // album, playlist/detail

    onTargetIdChanged: {
        var url = (targetType == "10" ? "album" : "playlist/detail") + "?id=" + (targetId.length < 1 ? "32311" : targetId)
    }

    Rectangle {
        Layout.fillWidth: true
        width: parent.width
        height: 60
        color: "#00000000"

        Text {
            x: 10
            verticalAlignment: Text.AlignBottom
            text: qsTr(targetType === "10" ? "专辑" : "歌单")
            font.family: window.mFONT_FAMILY
            font.pointSize: 25
        }
    }

    RowLayout {
        height: 200
        width: parent.width
        MusicRoundImage {
            id: playListCover
            width: 180
            height: 180
            Layout.leftMargin: 15
        }

        Item {
            Layout.fillWidth: true
            height: parent.height

            Text {
                id: playListDesc
                width: parent.width * 0.95
                anchors.centerIn: parent
                wrapMode: Text.WrapAnywhere
                font.family: window.mFONT_FAMILY
                font.pointSize: 14
                maximumLineCount: 4
                elide: Text.ElideRight
                lineHeight: 1.5
            }
        }
    }

    MusicListView {
        id: playListView
    }
}

