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
                width: buttonGroupSelect.width / 4.5
                text: dsButton
                checked: isChecked

                Rectangle {
                    width: 15
                    height: 15
                    anchors.margins: 2
                    anchors.top: parent.top
                    anchors.right: parent.right
                    visible: buttonGroupSelect.hasCloseActive && checked
                    color: "transparent"
                    radius: 2

                    Image {
                        id: img
                        width: 10
                        height: 10
                        source: "../../img/close-small.png"
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
