import QtQuick 2.0
import QtQuick.Controls 2.0

import "../"
import "../buttons/"

import br.com.ParserController 1.0

Rectangle {
    id: resultCodeScreen
    anchors.right: parent.right

    property ParserController parserController

    signal goBack

    enum TypeResultEnum {
        C = 1,
        ASSEMBLY = 2,
        BINARY = 3,
        ULA = 4
    }

    onVisibleChanged: function () {
        if (resultCodeScreen.visible) {
            updateResultCodeByIdOptions(1)
            buttonGroupSelect.setCheckedButton(1)
        }
    }

    function updateResultCodeByIdOptions(idOption) {

        // TODO criar enum
        switch (idOption) {
        case ResultCodeScreen.TypeResultEnum.C:
            inputTextArea.text = parserController.dsCodeInputC
            break
        case ResultCodeScreen.TypeResultEnum.ASSEMBLY:
            inputTextArea.text = parserController.dsCodeResultAssembly
            break
        case ResultCodeScreen.TypeResultEnum.BINARY:
            inputTextArea.text = parserController.dsCodeResultBinary
            break
        case ResultCodeScreen.TypeResultEnum.ULA:
            inputTextArea.text = parserController.dsCodeResultUla
            break
        default:
            break
        }
    }

    // TODO ajustar para usar o TypeResultEnum
    ListModel {
        id: optionsGroupSelect

        ListElement {
            idElement: 1
            dsButton: "C"
            isChecked: true
        }

        ListElement {
            idElement: 2
            dsButton: "Assembly"
            isChecked: false
        }

        ListElement {
            idElement: 3
            dsButton: "Binary"
            isChecked: false
        }
        ListElement {
            idElement: 4
            dsButton: "Ula"
            isChecked: false
        }
    }

    Column {
        id: columnMain
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
            topMargin: 80 - (columnMain.spacing * 2)
            bottomMargin: 80
        }

        Label {
            id: textDescription
            text: "Resultados"
            font.family: "Helvetica"
            font.pointSize: 18
            font.bold: true
            color: "#fff"
        }

        Column {
            id: columnResult
            width: parent.width
            height: parent.height - buttonComeBack.height - textDescription.height

            ButtonGroupSelect {
                id: buttonGroupSelect
                width: 300
                height: 40
                options: optionsGroupSelect

                onOptionSelected: function (idOption) {
                    updateResultCodeByIdOptions(idOption)
                }
            }

            TextArea {
                id: inputTextArea
                width: parent.width
                height: parent.height - buttonGroupSelect.height
                color: "#f5f5f5"
                font.family: "Arial Black"
                font.pixelSize: 14
                wrapMode: "WordWrap"
                enabled: false
                padding: 15

                background: Rectangle {
                    color: "#323232"
                    radius: 2
                }
            }
        }

        ButtonCustom {
            id: buttonComeBack
            colorDefault: "#4285f4"
            colorPressed: "#1f6ff2"
            text: "Voltar"
            icon: "../../img/esquerda-seta.png"

            onClicked: {
                resultCodeScreen.goBack()
            }
        }
    }
}