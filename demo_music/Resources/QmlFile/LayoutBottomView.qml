// 底部工具栏

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtMultimedia 5.9

Rectangle {

    property var playList: []
    property int current: -1

    property int sliderValue: 0
    property int sliderFrom: 0
    property int sliderTo: 100

    property int currentPlayMode: 0
    property var playModeList: [
        {icon:"single-repeat", name: "单曲循环"},
        {icon:"repeat", name: "顺序播放"},
        {icon:"random", name: "随机播放"}]

    property bool playbackStateChangeCallbackEnable: false

    property string musicName: "crucal"
    property string musicArtist: "crucal"
    property string musicCover: "qrc:/images/player"

    property int playingState: 0

    Layout.fillWidth: true
    height: 60
    color: "#00AAAA"

    RowLayout {
        anchors.fill: parent
        Item {
            Layout.preferredWidth: parent.width / 10
            Layout.fillWidth: true
        }
        MusicIconButton {
            iconSource: "qrc:/images/previous"
            iconWidth: 32
            iconHeight: 32
            toolTip: "上一曲"
            onClicked: playPrevious()
        }
        MusicIconButton {
            iconSource: playingState === 0 ? "qrc:/images/stop" : "qrc:/images/pause"
            iconWidth: 32
            iconHeight: 32
            toolTip: "暂停/播放"
            onClicked: {
                if (!mediaPlayer.source) {
                    return
                }

                if (mediaPlayer.playbackState === MediaPlayer.PlayingState) {
                    mediaPlayer.pause()
                } else if (mediaPlayer.playbackState === MediaPlayer.PausedState) {
                    mediaPlayer.play()
                }
            }
        }
        MusicIconButton {
            iconSource: "qrc:/images/next"
            iconWidth: 32
            iconHeight: 32
            toolTip: "下一曲"
            onClicked: playNext("")
        }
        Item {
            Layout.preferredWidth: parent.width / 2
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: 25

            Text {
                anchors.left: slider.left
                anchors.bottom: slider.top
                anchors.leftMargin: 5
                text: musicName + "-" + musicArtist
                font.family: window.mFONT_FAMILY
                color: "#ffffff"
            }
            Text {
                id: timeText
                anchors.right: slider.right
                anchors.bottom: slider.top
                anchors.leftMargin: 5
                text: qsTr("00:00/05:30")
                font.family: window.mFONT_FAMILY
                color: "#ffffff"
            }

            Slider {
                id: slider
                width: parent.width
                Layout.fillWidth: true
                height: 25
                value: sliderValue
                from: sliderFrom
                to: sliderTo

                onMoved: {
                    mediaPlayer.seek(value)
                }

                background: Rectangle {
                    x: slider.leftPadding
                    y: slider.topPadding + (slider.availableHeight - height) / 2
                    width: slider.availableWidth // 可用宽度
                    height: 4
                    radius: 2
                    color: "#e9f4ff"
                    Rectangle {
                        width: slider.visualPosition * parent.width
                        height: parent.height
                        color: "#73a7ab"
                        radius: 2
                    }
                }
                // 滑块
                handle: Rectangle {
                    x: slider.leftPadding + (slider.availableWidth - width) * slider.visualPosition
                    y: slider.topPadding + (slider.availableHeight - height) / 2
                    width: 15
                    height: 15
                    radius: 5
                    color: "#f0f0f0"
                    border.color: "#73a7ab"
                    border.width: 0.5
                }
            }
        }

        MusicBorderImage {
            imgSrc: musicCover
            width: 50
            height: 45
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor

                onPressed: {
                    musicCover.scale = 0.9
                }

                onReleased: {
                    musicCover.scale = 1.0
                }

                onClicked: {
                    pageDetailView.visible = !pageDetailView.visible
                    pageHomeView.visible = !pageHomeView.visible
                }
            }
        }

        MusicIconButton {
            Layout.preferredWidth: 50
            iconSource: "qrc:/images/favorite"
            iconWidth: 32
            iconHeight: 32
            toolTip: "喜欢"
        }
        MusicIconButton {
            id: playMode
            Layout.preferredWidth: 50
            iconSource: "qrc:/images/" + playModeList[currentPlayMode].icon
            iconWidth: 32
            iconHeight: 32
            toolTip: playModeList[currentPlayMode].name
            onClicked: changePlayMode()
        }
        Item {
            Layout.preferredWidth: parent.width / 10
            Layout.fillWidth: true
        }
    }


    Component.onCompleted: {
        //        console.log("settings Value...", settings.value("currentPlayMode", 0))
        // 从配置文件中拿到 currentPlayMode
        currentPlayMode = settings.value("currentPlayMode", 0)
    }

    onCurrentChanged: {
        playbackStateChangeCallbackEnable = false
        playMusic(current)
    }

    function playPrevious() {
        if (playList.length < 1) {
            return
        }

        switch (currentPlayMode) {
        case 0:
        case 1:
            current = (current + playList.length - 1) % playList.length
            break
        case 2: {
            var random = parseInt(Math.random() * playList.length)
            current = current === random ? random + 1 : random
            break
        }
        }
    }

    function playNext(type ='natural') {
        if (playList.length < 1) {
            return
        }

        switch (currentPlayMode) {
        case 0:
            if (type === 'natural') {
                mediaPlayer.play()
                break
            }
        case 1:
            current = (current + 1) % playList.length
            break
        case 2: {
            var random = parseInt(Math.random() * playList.length)
            current = current === random ? random + 1 : random
            break
        }
        }
    }

    function changePlayMode() {
        currentPlayMode = (currentPlayMode + 1) % playModeList.length
        settings.setValue("currentPlayMode", currentPlayMode)
    }

    // 播放音乐索引
    function playMusic() {
        if (current < 0) {
            return
        }

        // 获取播放链接
        getUrl()
    }

    function getUrl() {
        if (playList.length < 1) {
            return
        }
        var id = playList[current].id
        console.log("播放id...", id)
        if (!id) {
            return
        }
        // 设置详情
        musicName = playList[current].name
        musicArtist = playList[current].artist

        function onReply(reply) {
            http.onReplySignal.disconnect(onReply)
            // 将 string 转成 Json
            var data = JSON.parse(reply).data[0]
            var url = data.url
            var time = data.time

            // 设置 Slider
            setSlider(0, time, 0)

            if (!url) {
                return
            }

            // 请求 Cover
            var cover = playList[current].cover
            if (cover.length < 1) {
                getCover(id)
            } else {
                musicCover = cover
            }

            mediaPlayer.source = url
            mediaPlayer.play()
            console.log("mediaPlayer...Play")

            playbackStateChangeCallbackEnable = true
        }

        http.onReplySignal.connect(onReply)
        http.connect("song/url?id=" + id)
    }

    function getCover(id) {

        function onReply(reply) {
            http.onReplySignal.disconnect(onReply)
            var song = JSON.parse(reply).songs[0]
            var cover = song.al.picUrl

            musicCover = cover
            if (musicName.length < 1)
                musicName = song.name
            if (musicArtist.length < 1)
                musicArtist = song.ar[0].name
        }

        http.onReplySignal.connect(onReply)
        http.connect("song/detail?ids=" + id)
    }

    function setSlider(from = 0, to = 100, value = 0) {
        sliderFrom = from
        sliderTo = to
        sliderValue = value

        var va_mm = parseInt(value / 1000 / 60) + ""
        va_mm = va_mm.length < 2 ? "0" + va_mm : va_mm
        var va_ss = parseInt(value / 1000 % 60)+ ""
        va_ss = va_ss.length < 2 ? "0" + va_ss : va_ss

        var to_mm = parseInt(to / 1000 / 60) + ""
        to_mm = to_mm.length < 2 ? "0" + to_mm : to_mm
        var to_ss = parseInt(to / 1000 % 60)+ ""
        to_ss = to_ss.length < 2 ? "0" + to_ss : to_ss

        timeText.text = va_mm + ":" + va_ss + "/" + to_mm + ":" + to_ss
    }
}
