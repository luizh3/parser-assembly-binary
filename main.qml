import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Styles 1.4

import "./components/header"
import "./components/inputcode"
import "./components/sidebar"
import "./components/mensage"
import "./components/config"

ApplicationWindow {
    id: root
    width: 1300
    height: 800
    visible: true
    title: qsTr("Hello World")
    flags: Qt.FramelessWindowHint | Qt.WindowMinimizeButtonHint | Qt.Window
    visibility: "Windowed"
    color: "#3b3b3b"

    Material.theme: Material.Dark
    Material.accent: Material.Blue
    Material.elevation: 0

    Component.onCompleted: {

        //console.log(Qt.fontFamilies())
    }

    // TODO rever esse metodo, ver se existe algum metodo/enum do proprio QT
    property bool hasWindowed: true
    function changeVisibleMode() {
        hasWindowed = !hasWindowed
        root.visibility = hasWindowed ? "Windowed" : "FullScreen"
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
        width: 500
        height: 600
        anchors.centerIn: parent
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
                width: parent.width
                height: parent.height - header.height
                color: root.color

                onMessage: function (tpError, title, description) {
                    messagePopup.title = title
                    messagePopup.description = description
                    messagePopup.open()
                }
            }
        }
    }
}
