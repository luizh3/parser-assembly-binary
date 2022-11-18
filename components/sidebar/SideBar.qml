import QtQuick 2.0
import QtQuick.Controls 2.0

import "../buttons/icon"

Rectangle {
    id: root
    color: "#323232"

    signal config
    signal details
    signal subtitle

    property alias visibleSubtitle: buttonSubtitle.visible
    property alias visibleInformation: buttonInformation.visible

    Column {
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.topMargin: 10
        spacing: 15

        ButtonIcon {
            width: 50
            height: 40
            source: "/img/gear.png"
            colorDefault: "#3b3b3b"
            colorPressed: "#DDDDDD"
            colorPressedIcon: "#000"
            radius: 3
            heightImg: 24
            widthImg: 24
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                root.config()
            }
        }

        ButtonIcon {
            id: buttonInformation
            width: 50
            height: 40
            source: "/img/information.png"
            colorDefault: "#3b3b3b"
            colorPressed: "#DDDDDD"
            colorPressedIcon: "#000"
            radius: 3
            heightImg: 24
            widthImg: 24
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                root.details()
            }
        }

        ButtonIcon {
            id: buttonSubtitle
            width: 50
            height: 40
            source: "/img/legendas.png"
            colorDefault: "#3b3b3b"
            colorPressed: "#DDDDDD"
            colorPressedIcon: "#000"
            radius: 3
            heightImg: 24
            widthImg: 24
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                root.subtitle()
            }
        }
    }
}
