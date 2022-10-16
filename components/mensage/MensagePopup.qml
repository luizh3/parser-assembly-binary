import QtQuick 2.0

import QtQuick.Controls 2.0

Popup {
    id: popup
    focus: true
    modal: true
    anchors.centerIn: parent

    property alias title: titleLabel.text
    property alias description: descriptionLabel.text

    closePolicy: function () {
        return Popup.CloseOnEscape || Popup.CloseOnPressOutsideParent
    }

    background: Rectangle {
        border.color: "#fff"
        radius: 5
    }

    Column {
        width: parent.width / 1.2
        height: parent.height / 1.5
        anchors.centerIn: parent
        spacing: 20

        Image {
            id: icon
            source: "../../img/close.png"
            width: 48
            height: 48
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Label {
            id: titleLabel
            text: "Compile Error!"
            font.pixelSize: 15
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Label {
            id: descriptionLabel
            text: "Falha ao compilar o codigo"
            font.pixelSize: 13
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            text: "OK"
            width: parent.width
            height: 50
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: close()
        }
    }
}
