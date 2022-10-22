import QtQuick 2.0
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: root

    signal clicked

    property string colorDefault: "#1C1C1C"
    property string colorPressed: "#DDDDDD"

    property string colorDefaultIcon: "#fff"
    property string colorPressedIcon: "#fff"

    property int widthImg: 24
    property int heightImg: 24

    property alias source: img.source
    property alias visibleDescription: description.visible

    property alias textDescription: description.text

    color: mouseArea.containsMouse ? root.colorPressed : root.colorDefault

    Behavior on width {
        NumberAnimation {
            duration: 75
        }
    }

    // TODO refatorar isso, pois o tamanho da img esta maior que o do button
    Rectangle {
        id: rectangleImg
        width: root.width
        height: parent.height
        color: root.color
        radius: root.radius
        Image {
            id: img
            width: widthImg
            height: heightImg
            source: source
            anchors.centerIn: parent
        }
        ColorOverlay {
            anchors.fill: img
            source: img
            color: mouseArea.containsMouse ? root.colorPressedIcon : root.colorDefaultIcon
        }
    }

    Label {
        id: description
        width: root.width
        font.pixelSize: 19
        color: "#fff"
        anchors.left: rectangleImg.right
        anchors.verticalCenter: root.verticalCenter
        font.family: "Helvetica"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: root.clicked()
    }
}
