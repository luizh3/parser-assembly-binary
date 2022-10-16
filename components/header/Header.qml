import QtQuick 2.0
import QtQuick.Controls 2.0

import "../buttons/icon"

Rectangle {
    id: header
    width: parent.width
    height: 50
    color: "#3b3b3b"
    visible: true
    z: 1

    signal changeVisibleMode

    Row {
        width: parent.width
        height: parent.height

        Row {
            width: childrenRect.width
            height: parent.height
            anchors.right: parent.right
            anchors.rightMargin: 10
            spacing: 0

            ButtonIcon {
                width: 60
                height: 40
                source: "/img/minimize.png"
                colorDefault: header.color
                colorPressedIcon: "#000"
                radius: 3
                heightImg: 20
                widthImg: 20
                anchors.verticalCenter: parent.verticalCenter
                visibleDescription: false
                onClicked: {
                    showMinimized()
                }
            }

            ButtonIcon {
                width: 60
                height: 40
                source: "/img/quadrado.png"
                colorDefault: header.color
                colorPressedIcon: "#000"
                radius: 3
                heightImg: 20
                widthImg: 20
                anchors.verticalCenter: parent.verticalCenter
                visibleDescription: false
                onClicked: {
                    header.changeVisibleMode()
                }
            }

            ButtonIcon {
                width: 60
                height: 40
                source: "/img/x.png"
                colorDefault: header.color
                colorPressed: "#ff4040"
                radius: 3
                heightImg: 20
                widthImg: 20
                anchors.verticalCenter: parent.verticalCenter
                visibleDescription: false
                onClicked: {
                    close()
                }
            }
        }
    }
}
