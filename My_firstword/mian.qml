import QtQuick 2.9
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import QtQuick.Window
import QtQuick.Layouts 1.3
import QtQml

Window {
    width: 1000
    height: 600
    visible: true
    title: qsTr("MyWord")

    Row {
        id: row
        x: 0 ;y: 0

        property var btnTexts: ["New", "Open", "Save", "Copy", "Paste", "Cut", "Save_as"]
        property var btnImages: ["qrc:/images/new2.bmp", "qrc:/images/open3.bmp", "qrc:/images/430.bmp",
            "qrc:/images/120.bmp", "qrc:/images/paste.bmp", "qrc:/images/cut.bmp", "qrc:/images/Save_as1.jpg"]

        Repeater {
            model: parent.btnTexts.length // 重复生成5个组件

            Rectangle {
                id: btn

                property string icon_src: icon.source
                property string btn_text: button.text

                property color clr_enter: "#dcdcdc"
                property color clr_exit: "#000000"
                property color clr_click: "#aba9b2"
                property color clr_release: "#ffffff"

                // 自定义信号
                signal clickedLeft()
                signal clickedRight()
                signal release()

                width: 50; height: 100
                // 圆角半径为10px
                radius: 10
                Image {
                    id: icon
                    source: row.btnImages[modelData]
                    width: parent.width
                    height: parent.width - 20
                    clip: true
                    anchors {
                        top: parent.top
                        left: parent.left
                        right: parent.right
                        margins: 10
                    }
                }

                Text {
                    id: button
                    text: row.btnTexts[modelData] // 使用 modelData 关键字获取当前按钮的文本

                    anchors {
                        top: icon.bottom
                        topMargin: 5
                        horizontalCenter: icon.horizontalCenter
                        bottom: icon.bottom
                        bottomMargin: 5
                    }

                    font {
                        bold: true
                        pointSize: 7
                    }
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    // 接收鼠标悬停事件
                    hoverEnabled: true

                    // 接受左键和右键输入
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onCanceled: {
                        // 左键点击
                        if (mouse.button == Qt.LeftButton) {
                            console.log("左键点击")
                            parent.clickedLeft()
                        } else if (mouse.button == Qt.RightButton) {
                            console.log("右键点击")
                            parent.clickedRight()
                        }
                    }

                    // 按下
                    onPressed: {
                        button.color = btn.clr_click
                    }

                    // 释放
                    onReleased: {
                        button.color = btn.clr_enter
                        parent.release()
                        console.log("Release")
                    }

                    // 指针进入
                    onEntered: {
                        button.color = btn.clr_enter
                    }

                    // 指针退出
                    onExited: {
                        button.color = btn.clr_exit
                    }
                }
            }
        }

        property var abtnTexts: ["Italic", "Bold", "Underline"]
        property var abtnImages: ["qrc:/images/ITL.BMP", "qrc:/images/BLD.BMP", "qrc:/images/UNDRLN.BMP"]

        Repeater {
            model: parent.abtnTexts.length
            Rectangle {
                id: abtn

                //                property string icon_src: icon.source
                //                property string btn_text: button.text

                width: 50; height: 100
                // 圆角半径为10px
                radius: 10

                Button {
                    //                    y: 3
                    checkable: true
                    Image {
                        id: italic_img
                        source: row.abtnImages[modelData]
                        width: parent.width
                        height: parent.height - 20
                        clip: true
                        anchors {
                            top: parent.top
                            left: parent.left
                            right: parent.right
                            margins: 10
                        }
                    }

                    Text {
                        id: btn_text
                        text: row.abtnTexts[modelData]
                        width: parent.width
                        anchors {
                            top: italic_img.bottom
                        }
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font {
                            bold: true
                            pointSize: 7
                        }
                    }
                    //                    text: btnTexts[modelData]

                    width: 50; height: 50
                    // 圆角半径为10px
                    //                    radius: 10


                    onClicked: {
                        console.log("button clicked: " + text)
                    }
                }
            }
        }
    }

    RowLayout {
        anchors.left: row.right
        y: 10
        spacing: 10

        Label {
            text: "字体大小"
        }

        SpinBox {
            value: 9
            Layout.alignment: Qt.AlignLeft
        }
        ComboBox {
            Layout.alignment: Qt.AlignLeft
            id: control
            model: ["宋体", "微软雅黑", "楷体"]
            delegate: ItemDelegate { //呈现标准视图项 以在各种控件和控件中用作委托
                width: control.width
                contentItem: Text {
                    text: modelData   //即model中的数据
                    color: "green"
                    font: control.font
                    verticalAlignment: Text.AlignVCenter
                }
            }

            contentItem: Text { //界面上显示出来的文字
                leftPadding: 5 //左部填充为5
                text: control.displayText //表示ComboBox上显示的文本
                font: control.font    //文字大小
                color: control.pressed ? "orange" : "black"   //文字颜色
                verticalAlignment: Text.AlignVCenter  //文字位置
            }

            background: Rectangle {   //背景项
                implicitWidth: 120
                implicitHeight: 40
                color: "white"
                border.width: 1
                radius: 2
            }

            popup: Popup {    //弹出项
                y: control.height
                width: control.width
                implicitHeight: contentItem.implicitHeight
                padding: 1
                //istView具有一个模型和一个委托。模型model定义了要显示的数据
                contentItem: ListView {   //显示通过ListModel创建的模型中的数据
                    clip: true
                    implicitHeight: contentHeight
                    model: control.popup.visible ? control.delegateModel : null
                }
                background: Rectangle {
                    border.color: "green"
                    radius: 2
                }
            }
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.top: row.bottom
        width: parent.width
        height: parent.height - row.height
        TextEdit {
            id: textEdit
            text: "请在此处编辑文本"
            anchors.left: parent.left
            width: parent.width; height: parent.height
        }

//        MouseArea {
//            doubleClicked: {
//                textEdit.text = ""
//            }
//        }
    }
}
