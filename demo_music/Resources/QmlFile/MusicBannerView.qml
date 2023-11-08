// 自定义轮播图

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQml 2.3

Frame {
    property int current: 0
    property alias bannerList: bannerView.model

    background: Rectangle {
        color: "#00000000"
    }

    PathView {
        id: bannerView
        width: parent.width
        height: parent.height

        clip: true

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onEntered: {
                bannerTimer.stop()
            }

            onExited: {
                bannerTimer.start()
            }
        }

        delegate: Item {
            id: delegateItem
            width: bannerView.width * 0.7
            height: bannerView.height
            z: PathView.z ? PathView.z : 0
            scale: PathView.scale ? PathView.scale : 1.0

            MusicRoundImage {
                id: image
                imgSrc: modelData.imageUrl
                width: delegateItem.width
                height: delegateItem.height
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    if (bannerView.currentIndex === index) {
                        var item = bannerView.model[index]
                        var targetId = item.targetId + ""
                        var targetType = item.targetType + "" // 1.单曲，10：专辑，1000：歌单
                        switch (targetType) {
                        case "1":
                            // 播放歌曲
                            break
                        case "10":
                            // 打开专辑
                        case "1000":
                            // 打开播放列表
                            PageHomeView.showPlayList(targetId, targetType)
                            break
                        }

                        console.log(targetId, targetType)
                    } else {
                        bannerView.currentIndex = index
                    }
                }
            }
        }

        pathItemCount: 3
        path: bannerPath
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
    }

    Path {
        id: bannerPath
        startX: 0
        startY: bannerView.height / 2 - 10

        PathAttribute {name: "z"; value: 0}
        PathAttribute {name: "scale"; value: 0.6}

        PathLine {
            x: bannerView.width / 2
            y: bannerView.height / 2 - 10
        }

        PathAttribute {name: "z"; value: 2}
        PathAttribute {name: "scale"; value: 0.85}

        PathLine {
            x: bannerView.width
            y: bannerView.height / 2 - 10
        }

        PathAttribute {name: "z"; value: 0}
        PathAttribute {name: "scale"; value: 0.6}
    }

    PageIndicator {
        id: indicator
        anchors {
            top: bannerView.bottom
            horizontalCenter: parent.horizontalCenter
            topMargin: -10
        }
        count: bannerView.count
        currentIndex: bannerView.currentIndex
        spacing: 10
        delegate: Rectangle {
            width: 20
            height: 5
            radius: 5
            color: index === bannerView.currentIndex ? "black" : "gray"

            Behavior on color {
                ColorAnimation {
                    duration: 200
                }
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onEntered: {
                    bannerTimer.stop()
                    bannerView.currentIndex = index
                }

                onExited: {
                    bannerTimer.start()
                }
            }
        }
    }

    Timer {
        id: bannerTimer
        running: true
        repeat: true
        interval: 3000
        onTriggered: {
            if (bannerView.count) {
                bannerView.currentIndex = (bannerView.currentIndex + 1) % bannerView.count
            }
        }
    }

    /*
    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true
        onEntered: {
            bannerTimer.stop()
        }

        onExited: {
            bannerTimer.start()
        }
    }

    MusicRoundImage {
        id: leftImage
        width: parent.width * 0.6
        height: parent.height * 0.8
        anchors {
            left: parent.left
            bottom: parent.bottom
            bottomMargin: 20
        }
        imgSrc: getLeftImgSrc()

        onImgSrcChanged: {
            leftImageAnim.start()
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if (bannerList.length > 0) {
                    current = current == 0 ? bannerList.length - 1 : current - 1
                }
            }
        }


        NumberAnimation {
            id: leftImageAnim
            target: leftImage
            property: "scale"
            from: 0.8
            to: 1.0
            duration: 200
        }
    }

    MusicRoundImage {
        id: centerImage
        width: parent.width * 0.6
        height: parent.height
        z: 2
        anchors.centerIn: parent
        imgSrc: getCenterImgSrc()

        onImgSrcChanged: {
            centerImageAnim.start()
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
        }

        NumberAnimation {
            id: centerImageAnim
            target: centerImage
            property: "scale"
            from: 0.8
            to: 1.0
            duration: 200
        }
    }

    MusicRoundImage {
        id: rightImage
        width: parent.width * 0.6
        height: parent.height * 0.8
        anchors {
            right: parent.right
            bottom: parent.bottom
            bottomMargin: 20
        }
        imgSrc: getRightImgSrc()

        onImgSrcChanged: {
            rightImageAnim.start()
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if (bannerList.length > 0) {
                    current = current == bannerList.length ? 0 : current + 1
                }
            }
        }
        NumberAnimation {
            id: rightImageAnim
            target: rightImage
            property: "scale"
            from: 0.8
            to: 1.0
            duration: 200
        }
    }

    PageIndicator {
        anchors {
            top: centerImage.bottom
            horizontalCenter: parent.horizontalCenter
        }
        count: bannerList.length
        interactive: true

        onCurrentIndexChanged: {
            current = currentIndex
        }

        delegate: Rectangle {
            width: 20
            height: 5
            radius: 5
            color: current === index ? "black" : "gray"
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true
                onEntered: {
                    bannerTimer.stop()
//                    console.log(index)
                    current = index
                }

                onExited: {
                    bannerTimer.start()
                }
            }
        }
    }

    Timer {
        id: bannerTimer
        running: true
        interval: 2000 // 5s
        repeat: true // 一直存在
        onTriggered: {
            if (bannerList.length) {
                current = current == bannerList.length ? 0 : current + 1
            }
        }
    }


    function getLeftImgSrc() {
        var idx = (current - 1 + bannerList.length) % bannerList.length
        return bannerList.length ? bannerList[idx].imageUrl : ""
    }
    function getCenterImgSrc() {
        return bannerList.length ? bannerList[current].imageUrl : ""
    }
    function getRightImgSrc() {
        var idx = (current + 1 + bannerList.length) % bannerList.length
        return bannerList.length ? bannerList[idx].imageUrl : ""
    }
    */
}
