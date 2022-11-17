import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.0

import "./components/header"
import "./components/inputcode"
import "./components/sidebar"
import "./components/mensage"
import "./components/config"
import "./components/result"

import br.com.ParserController 1.0

ApplicationWindow {
    id: root
    width: Screen.desktopAvailableWidth / 1.6
    height: Screen.desktopAvailableHeight / 1.4
    visible: true
    title: qsTr("Parser")
    flags: Qt.FramelessWindowHint | Qt.WindowMinimizeButtonHint | Qt.Window
    visibility: "FullScreen"
    color: "#3b3b3b"

    property var currentScreen: inputCodeScreen

    // TODO rever esse metodo, ver se existe algum metodo/enum do proprio QT
    property bool hasWindowed: false
    function changeVisibleMode() {
        hasWindowed = !hasWindowed
        root.visibility = hasWindowed ? "Windowed" : "FullScreen"
    }

    function changeScreenVisible(newScreen) {
        currentScreen.visible = false
        currentScreen = newScreen
        currentScreen.visible = true
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            pos = Qt.point(mouse.x, mouse.y)
        }
        onPositionChanged: {
            var diff = Qt.point(mouse.x - pos.x, mouse.y - pos.y)
            ApplicationWindow.window.x += diff.x
            ApplicationWindow.window.y += diff.y
        }
        property point pos
    }

    // TODO arrumar nome do component
    MensagePopup {
        id: messagePopup
        width: 350
        height: 300
        anchors.centerIn: parent
    }

    SettingsScreen {
        id: settingsScreen
        width: root.width / 2.8
        height: root.height / 1.4
        anchors.centerIn: parent
    }

    ParserController {
        id: control

        onParserFnished: {
            changeScreenVisible(resultCodeScreen)
        }
    }

    Row {
        width: parent.width
        height: parent.height

        SideBar {
            id: sideBar
            width: 80
            height: parent.height

            onConfig: {
                settingsScreen.open()
            }
        }

        Column {
            id: columnMain
            width: parent.width - sideBar.width
            height: parent.height

            Header {
                id: header
                width: parent.width
                onChangeVisibleMode: root.changeVisibleMode()
            }

            InputCodeScreen {
                id: inputCodeScreen
                width: parent.width
                height: parent.height - header.height
                color: root.color
                visible: true

                onConfirmText: function (text) {
                    control.makeParser(text)
                }

                onMessage: function (tpError, title, description) {
                    messagePopup.title = title
                    messagePopup.description = description
                    messagePopup.open()
                }
            }

            ResultCodeScreen {
                id: resultCodeScreen
                width: parent.width
                height: parent.height - header.height
                color: root.color
                visible: false
                parserController: control

                onGoBack: {
                    changeScreenVisible(inputCodeScreen)
                }
            }
        }
    }
}
