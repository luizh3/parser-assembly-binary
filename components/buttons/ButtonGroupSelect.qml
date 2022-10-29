import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: buttonGroupSelect

    property var options: []

    signal optionSelected(var idOption)

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
                width: buttonGroupSelect.width / modelList.count
                height: 40
                text: dsButton
                checked: isChecked

                onClicked: {
                    setCheckedButton(idElement)
                    buttonGroupSelect.optionSelected(idElement)
                }
            }
        }
    }
}
