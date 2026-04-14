

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import UntitledProject

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    Rectangle {
        id: rectangle1
        x: 790
        y: 300
        width: 341
        height: 526
        color: "#ffffff"

        Button {
            id: button1
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -64
            anchors.horizontalCenterOffset: 61
            Connections {
                target: button1
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button2
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("clr")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button2
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 229
            anchors.horizontalCenterOffset: -127
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button3
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("0")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button3
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 229
            anchors.horizontalCenterOffset: -65
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button4
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("=")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button4
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 229
            anchors.horizontalCenterOffset: 62
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button5
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr(".")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button5
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 229
            anchors.horizontalCenterOffset: -1
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button7
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button7
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 113
            anchors.horizontalCenterOffset: -129
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button8
            x: 335
            y: 181
            width: 44
            height: 96
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button8
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 197
            anchors.horizontalCenterOffset: 119
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button9
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button9
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 169
            anchors.horizontalCenterOffset: 61
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button10
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button10
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 170
            anchors.horizontalCenterOffset: -1
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button11
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button11
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 171
            anchors.horizontalCenterOffset: -65
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button12
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button12
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 171
            anchors.horizontalCenterOffset: -127
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button13
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button13
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 113
            anchors.horizontalCenterOffset: 121
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button14
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button14
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 113
            anchors.horizontalCenterOffset: 61
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button15
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button15
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 113
            anchors.horizontalCenterOffset: -1
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button16
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button16
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 113
            anchors.horizontalCenterOffset: -65
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button17
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button17
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: -122
            anchors.horizontalCenterOffset: 121
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button18
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button18
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: -122
            anchors.horizontalCenterOffset: 61
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button19
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button19
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: -122
            anchors.horizontalCenterOffset: -1
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button20
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button20
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: -122
            anchors.horizontalCenterOffset: -65
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button21
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button21
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 53
            anchors.horizontalCenterOffset: 62
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button22
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button22
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 53
            anchors.horizontalCenterOffset: -1
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button23
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button23
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 53
            anchors.horizontalCenterOffset: -65
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button24
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button24
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 53
            anchors.horizontalCenterOffset: -129
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button25
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button25
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: -122
            anchors.horizontalCenterOffset: -129
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button26
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button26
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: -64
            anchors.horizontalCenterOffset: 119
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button27
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button27
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: -64
            anchors.horizontalCenterOffset: -1
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button28
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button28
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: -64
            anchors.horizontalCenterOffset: -65
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button29
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button29
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: -64
            anchors.horizontalCenterOffset: -129
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button30
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button30
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: -6
            anchors.horizontalCenterOffset: -65
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button31
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button31
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: -6
            anchors.horizontalCenterOffset: -129
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button32
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button32
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: -6
            anchors.horizontalCenterOffset: -1
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button33
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button33
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: 53
            anchors.horizontalCenterOffset: 119
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button34
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button34
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: -6
            anchors.horizontalCenterOffset: 61
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: button35
            x: 335
            y: 181
            width: 44
            height: 40
            text: qsTr("Press me")
            anchors.verticalCenter: parent.verticalCenter
            Connections {
                target: button35
                function onClicked() {
                    animation.start()
                }
            }
            checkable: true
            anchors.verticalCenterOffset: -6
            anchors.horizontalCenterOffset: 119
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    states: [
        State {
            name: "clicked"
        }
    ]
}
