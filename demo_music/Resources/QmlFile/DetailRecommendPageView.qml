// DetailRecommendPageView

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQml 2.3

ScrollView {
    // 如果元素超出父组件，自动裁剪
    clip: true
    ColumnLayout {
        Rectangle {
            Layout.fillWidth: true
            width: parent.width
            height: 60
            color: "#00000000"

            Text {
                x: 10
                verticalAlignment: Text.AlignBottom
                text: qsTr("推荐内容")
                font.family: window.mFONT_FAMILY
                font.pointSize: 25
                color: "#eeffffff"
            }
        }

        MusicBannerView {
            id: bannerView
            Layout.preferredWidth: window.width - 200
            Layout.preferredHeight: (window.width - 200) * 0.3
            Layout.fillWidth: true
            Layout.fillHeight: true
        }


        Rectangle {
            Layout.fillWidth: true
            width: parent.width
            height: 60
            color: "#00000000"

            Text {
                x: 10
                verticalAlignment: Text.AlignBottom
                text: qsTr("热门歌单")
                font.family: window.mFONT_FAMILY
                font.pointSize: 25
                color: "#eeffffff"
            }
        }

        MusicGridHotView {
            id: hotView
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: (window.width - 250) * 0.8 + 30 * 4 + 20
            Layout.bottomMargin: 20
        }


        Rectangle {
            Layout.fillWidth: true
            width: parent.width
            height: 60
            color: "#00000000"

            Text {
                x: 10
                verticalAlignment: Text.AlignBottom
                text: qsTr("新歌推荐")
                font.family: window.mFONT_FAMILY
                font.pointSize: 25
                color: "#eeffffff"
            }
        }

        MusicGridLatestView {
            id: latestView
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: (window.width - 230) * 0.1 * 10 + 20
            Layout.bottomMargin: 20
        }
    }

    Component.onCompleted: {
        getBannerList()
    }

    function getBannerList() {

        function onReply(reply) {
            http.onReplySignal.disconnect(onReply)
            // 将 string 转成 Json
            var banners = JSON.parse(reply).banners
            bannerView.bannerList = banners
            getHotList()
        }

        http.onReplySignal.connect(onReply)
        http.connect("banner")
    }


    function getHotList() {

        function onReply(reply) {
            http.onReplySignal.disconnect(onReply)
            // 将 string 转成 Json
            var playlists = JSON.parse(reply).playlists
            hotView.list = playlists
            getLatestList()
        }

        http.onReplySignal.connect(onReply)
        http.connect("top/playlist/highquality?limit=20")
    }

    function getLatestList() {

        function onReply(reply) {
            http.onReplySignal.disconnect(onReply)
            // 将 string 转成 Json
            var latestList = JSON.parse(reply).data
            latestView.list = latestList.slice(0, 30)
        }

        http.onReplySignal.connect(onReply)
        http.connect("top/song")
    }
}
