// 中心页面

import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQml 2.3

RowLayout {
    spacing: 0

    property int defaultidx: 0

    property var qmlList: [
        {icon: "recommend-white", value: "推荐内容", qml: "DetailRecommendPageView", menu: true},
        {icon: "cloud-white", value: "搜索音乐", qml: "DetailSearchPageView", menu: true},
        {icon: "local-white", value: "本地音乐", qml: "DetailLocalPageView", menu: true},
        {icon: "history-white", value: "播放历史", qml: "DetailHistoryPageView", menu: true},
        {icon: "favorite-big-white", value: "我喜欢", qml: "DetailFavoritePageView", menu: true},
        {icon: "", value: "", qml: "DetailPlayListPageView", menu: false},
    ]

    Frame {
        Layout.preferredWidth: 200
        Layout.fillHeight: true
        background: Rectangle {
            color: "#1000AAAA"
        }
        padding: 0

        ColumnLayout {
            anchors.fill: parent

            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: 150
                MusicBorderImage {
                    imgSrc: "qrc:images/crucal"
                    anchors.centerIn: parent
                    height: 100
                    width: 100
                    borderRadius: 100
                }
            }

            ListView {
                id: menuView
                height: parent.height
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: ListModel {
                    id: menuViewModel
                }
                delegate: menuViewDelegate
                highlight: Rectangle {
                    color: "#3073a7ab"
                }
//                highlightMoveDuration: 0
//                highlightResizeDuration: 0
            }
        }


        Component {
            id: menuViewDelegate
            Rectangle {
                id: menuViewDelegateItem
                height: 50
                width: 200
                color: "#0000AAAA"
                RowLayout {
                    anchors.fill: parent
                    anchors.centerIn: parent
                    spacing: 15
                    Item {
                        width: 30
                    }
                    Image {
                        source: "qrc:/images/" + icon
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 20
                    }

                    Text {
                        text: value
                        Layout.fillWidth: true
                        font.family: window.mFONT_FAMILY
                        font.pointSize: 12
                        color: "#eeffffff"
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        color = "#aa73a7ab"
                    }
                    onExited: {
                        color = "#00000000"
                    }
                    onClicked: {
                        hidePlayList()
                        repeater.itemAt(menuViewDelegateItem.ListView.view.currentIndex).visible = false
                        menuViewDelegateItem.ListView.view.currentIndex = index
                        var loader = repeater.itemAt(index)
                        loader.visible = true
                        loader.source = qmlList[index].qml + ".qml"
                    }
                }
            }
        }

        // 加载成功调用
        Component.onCompleted: {
            menuViewModel.append(qmlList.filter(item => item.menu))
            var loader = repeater.itemAt(defaultidx)
            loader.visible = true
            loader.source = qmlList[defaultidx].qml + ".qml"

            menuView.currentIndex = defaultidx
        }
    }

    // 把子组件重复显示
    Repeater {
        id: repeater
        // 过滤
        model: qmlList.length

        Loader {
            visible: false
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    function showPlayList(targetId = "", targetType = "10") {
        repeater.itemAt(menuView.currentIndex).visible = false
        var loader = repeater.itemAt(5)
        loader.visible = true
        loader.source = qmlList[5].qml + ".qml"
        loader.item.targetType = targetType
        loader.item.targetId = targetId

    }

    function hidePlayList() {
        repeater.itemAt(menuView.currentIndex).visible = true
        var loader = repeater.itemAt(5)
        loader.visible = false
    }
}

