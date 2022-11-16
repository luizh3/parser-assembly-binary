import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: buttonGroupSelect

    property var options: []
    property bool hasCloseActive: false

    signal optionSelected(var idOption)
    signal leftButtonClicked(var idOption)
    signal closed(var idOption)

    color: "transparent"

    function setCheckedButton(idButton) {

        for (var i = 0; i < options.count; i++) {

            var current = options.get(i)

            if (current.idElement !== idButton) {
                current.isChecked = false
                continue
            }

            current.isChecked = true
        }
    }

    Row {
        width: childrenRect.width
        height: 40

        Repeater {
            model: buttonGroupSelect.options

            ButtonSelect {
                height: 40
                text: dsButton
                checked: isChecked

                Rectangle {
                    width: 20
                    height: 20
                    anchors.margins: 10
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    visible: buttonGroupSelect.hasCloseActive && checked
                    color: mouseAreaClose.containsMouse ? "#FFFFFF" : "#818385"
                    radius: 2

                    Image {
                        width: 12
                        height: 12
                        source: "../../img/x.png"
                        anchors.centerIn: parent
                    }

                    MouseArea {
                        id: mouseAreaClose
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            buttonGroupSelect.closed(idElement)
                        }
                    }
                }

                onLeftButtonClicked: function () {
                    buttonGroupSelect.leftButtonClicked(idElement)
                }

                onClicked: function () {
                    setCheckedButton(idElement)
                    buttonGroupSelect.optionSelected(idElement)
                }
            }
        }
    }
}
