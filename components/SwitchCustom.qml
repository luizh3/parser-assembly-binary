import QtQuick 2.0
import QtQuick.Controls 2.0

Switch {
    id: control

    indicator: Rectangle {
        implicitWidth: 48
        implicitHeight: 26
        x: control.width - width - control.rightPadding
        y: parent.height / 2 - height / 2
        radius: 13
        color: control.checked ? "#4285f4" : "#9aa0a6"
        border.color: "#f2f4f5"

        Rectangle {
            x: control.checked ? parent.width - width : 0
            width: 24
            height: 24
            radius: 13
            border.color: "#f2f4f5"
            anchors.verticalCenter: parent.verticalCenter
            Behavior on x {
                NumberAnimation {
                    duration: 100
                }
            }
        }
    }
}
