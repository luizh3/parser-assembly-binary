import QtQuick 2.0
import QtQuick.Controls 2.0

import br.com.InputCodeController 1.0

import "../"

Rectangle {
    id: inputCodeScreen
    anchors.right: parent.right

    signal confirmText(var text)
    signal message(var tpError, var title, var description)

    InputCodeController {
        id: control
        onShowMessage: function (tpError, title, description) {
            inputCodeScreen.message(tpError, title, description)
        }
    }

    Column {
        id: columnInput
        width: parent.width
        height: parent.height
        spacing: 20
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            top: parent.top
            leftMargin: 100
            rightMargin: 100
            topMargin: 80 - (columnInput.spacing * 2)
            bottomMargin: 80
        }

        Label {
            id: textDescription
            text: "Informe o código que deseja converter"
            font.family: "Helvetica"
            font.pointSize: 18
            font.bold: true
            color: "#fff"
        }

        // TODO aumentar tamanho do texto
        TextArea {
            id: inputTextArea
            width: parent.width
            height: parent.height - button.height - textDescription.height
            color: "#fff"
            font.family: "Arial Black"
            font.pixelSize: 14
            wrapMode: "WordWrap"
            selectByMouse: true

            background: Rectangle {
                color: "#323232"
                radius: 2
            }

            text: control.readText()
        }

        // TODO criar component/colocar icone no botao
        ButtonCustom {
            id: button
            icon: "../../img/confirm.png"
            text: "Confirm"
            colorPressed: "#c8e6c9"
            colorTextDefault: "#4caf50"
            onClicked: {
                control.writeText(inputTextArea.text)
                control.onRunCode()
                inputCodeScreen.confirmText(inputTextArea.text)
            }
        }
    }
}
