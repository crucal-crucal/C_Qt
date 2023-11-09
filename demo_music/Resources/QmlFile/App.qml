// App.qml

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import MyUtils 1.0
import QtMultimedia 5.9
import Qt.labs.settings 1.1

ApplicationWindow {
    id: window

    property int mWINDOW_WIDTH: 1200
    property int mWINDOW_HEIGHT: 800

    property string mFONT_FAMILY: "微软雅黑"

    width: mWINDOW_WIDTH
    height: mWINDOW_HEIGHT
    visible: true
    title: qsTr("Demo Cloud Music Player")

    HttpUtils {
        id: http
    }

    Settings {
        id: settings
        fileName: "conf/settings.ini"
    }

    ColumnLayout {
        anchors.fill: parent

        spacing: 0

        LayoutHeaderView {
            id: layoutheaderView
        }

        PageDetailView {
            id: pageDetailView
            visible: false
        }

        PageHomeView {
            id: pageHomeView
        }

        LayoutBottomView {
            id: layoutBottomView
        }
    }

    MediaPlayer {
        id: mediaPlayer

        onPositionChanged: {
            layoutBottomView.setSlider(0, duration, position)
        }

        onPlaybackStateChanged: {
            layoutBottomView.playingState = playbackState === MediaPlayer.PlayingState ? 1 : 0
            if (playbackState === MediaPlayer.StoppedState && layoutBottomView.playbackStateChangeCallbackEnable) {
                layoutBottomView.playNext()
            }
        }
    }

}
