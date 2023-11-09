// DetailLocalPageView

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1

ColumnLayout {

    Rectangle {
        Layout.fillWidth: true
        width: parent.width
        height: 60
        color: "#00000000"

        Text {
            x: 10
            verticalAlignment: Text.AlignBottom
            text: qsTr("本地音乐")
            font.family: window.mFONT_FAMILY
            font.pointSize: 25
        }
    }

    RowLayout {
        height: 80
        Item {
            width: 10
        }

        MusicTextButton {
            btnText: "添加本地音乐"
            btnHeight: 50
            btnWidth: 200
            onClicked: {
                fileDialog.open()
            }
        }
        MusicTextButton {
            btnText: "刷新记录"
            btnHeight: 50
            btnWidth: 120
            onClicked: {

            }
        }
        MusicTextButton {
            btnText: "清空记录"
            btnHeight: 50
            btnWidth: 120
            onClicked: {

            }
        }
    }

    MusicListView {
        id: localListView
    }

    FileDialog {
        id: fileDialog
        fileMode: FileDialog.OpenFiles
        nameFilters: ["MP3 Music Files(*.mp3)", "FLAC Music Files(*.flac)"]
        folder: StandardPaths.standardLocations(StandardPaths.MusicLocation)[0]
        acceptLabel: "确定"
        rejectLabel: "取消"

        onAccepted: {
            var list = []
            for (var index in files) {
                var path = files[index]
                var arr = path.split("/")
                var fileNameArr = arr[arr.length - 1].split(".")
                // 去掉后缀
                fileNameArr.pop()
                var fileName = fileNameArr.join(".")
                // 歌手-名称.mp3
                var nameArr = fileName.split("-")
                var name = "curcal"
                var artist = "crucal"
                if (nameArr.length > 1) {
                    artist = nameArr[0]
                    nameArr.shift()
                }
                name = nameArr.join("-")
                list.push({
                              id: path + "",
                              name, artist,
                              url: path + "",
                              album: "本地音乐",
                              type: "1" // 1 表示本地音乐，0表示网络
                          })
                localListView.musicList = list
            }
        }
    }
}
