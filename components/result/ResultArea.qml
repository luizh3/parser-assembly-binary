import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    color: "#323232"

    property alias text: inputTextArea.text

    Flickable {
        clip: true
        width: parent.width
        height: parent.height * 0.99
        contentHeight: parent.height > inputTextArea.height ? parent.height : inputTextArea.height
        flickableDirection: Flickable.VerticalFlick
        anchors.centerIn: parent

        ScrollBar.vertical: ScrollBar {
            active: hovered || pressed
            hoverEnabled: true
            snapMode: ScrollBar.SnapOnRelease
        }

        Label {
            id: inputTextArea
            color: "#f5f5f5"
            font.family: "Arial Black"
            font.pixelSize: 14
            wrapMode: "WordWrap"
            padding: 15
            anchors.left: parent.left
            anchors.top: parent.top
        }
    }
}
