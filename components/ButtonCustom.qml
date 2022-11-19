import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: button
    width: 250
    height: 50
    color: mouseAreaButton.containsMouse ? colorPressed : colorDefault
    radius: 2

    property alias text: label.text
    property string icon: ""
    property string colorDefault: "#fff"
    property string colorPressed: ""

    property string colorTextDefault: "#fff"

    signal clicked

    Row {
        width: parent.width
        height: parent.height

        Image {
            id: name
            width: 48
            height: 48
            source: button.icon
            visible: icon.length > 0
        }

        Label {
            id: label
            font.family: "Helvetica"
            font.pointSize: 13
            color: mouseAreaButton.containsMouse ? "#fff" : colorTextDefault
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
        }
    }

    MouseArea {
        id: mouseAreaButton
        hoverEnabled: true
        anchors.fill: parent

        onClicked: {
            button.clicked()
        }
    }
}
