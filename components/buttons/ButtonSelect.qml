import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: buttonSelect
    width: 100
    height: 40

    property bool checked: false

    signal leftButtonClicked
    signal clicked

    property string colorChecked: "#323232"
    property string colorDefault: "#818385"

    property alias text: description.text

    color: checked ? colorChecked : (mouseArea.containsMouse ? "#939596" : colorDefault)

    //    Rectangle {
    //        width: parent.width
    //        height: 2
    //        color: isChecked ? "#1f6ff2" : colorDefault
    //    }
    Label {
        id: description
        font.pixelSize: 15
        color: "#fff"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Helvetica"
        font.bold: true
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true
        acceptedButtons: Qt.RightButton | Qt.LeftButton

        onClicked: {

            if (mouse.button === Qt.RightButton) {
                buttonSelect.leftButtonClicked()
                return
            }

            buttonSelect.clicked()
        }
    }
}
