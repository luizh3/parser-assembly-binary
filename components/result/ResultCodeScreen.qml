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
            updateResultCodeByIdOptions(inputTextArea, 1)
            buttonGroupSelect.setCheckedButton(1)
            columnSecondTextArea.visible = false
        }
    }

    function getOptionById(listOption, idOption) {

        for (var i = 0; i < listOption.count; ++i) {
            if (listOption.get(i).idElement === idOption) {
                return listOption.get(i)
            }
        }

        return null
    }

    function removeOptionById(listOption, idOption) {

        for (var i = 0; i < listOption.count; ++i) {
            if (listOption.get(i).idElement === idOption) {
                listOption.remove(i, 1)
                break
            }
        }
    }

    function hasOptionById(listOptions, idOption) {

        for (var i = 0; i < listOptions.count; ++i) {
            if (listOptions.get(i).idElement === idOption) {
                return true
            }
        }

        return false
    }

    function updateResultCodeByIdOptions(componentUpdate, idOption) {

        switch (idOption) {
        case ResultCodeScreen.TypeResultEnum.C:
            componentUpdate.text = parserController.dsCodeInputC
            break
        case ResultCodeScreen.TypeResultEnum.ASSEMBLY:
            componentUpdate.text = parserController.dsCodeResultAssembly
            break
        case ResultCodeScreen.TypeResultEnum.BINARY:
            componentUpdate.text = parserController.dsCodeResultBinary
            break
        case ResultCodeScreen.TypeResultEnum.ULA:
            componentUpdate.text = parserController.dsCodeResultUla
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

    ListModel {
        id: optionsGroupSelectSecond
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

        Row {
            id: columnResult
            width: parent.width
            height: parent.height - buttonComeBack.height - textDescription.height
            spacing: 10

            Column {
                width: inputTextAreaSecond.visible ? parent.width / 2 : parent.width
                height: parent.height

                ButtonGroupSelect {
                    id: buttonGroupSelect
                    width: inputTextAreaSecond.visible ? parent.width : parent.width / 2
                    height: 40
                    options: optionsGroupSelect

                    onOptionSelected: function (idOption) {
                        updateResultCodeByIdOptions(inputTextArea, idOption)
                    }

                    onLeftButtonClicked: function (idOption) {
                        columnSecondTextArea.visible = true

                        var option = getOptionById(optionsGroupSelect, idOption)

                        if (!hasOptionById(optionsGroupSelectSecond,
                                           idOption)) {
                            optionsGroupSelectSecond.append(option)

                            buttonGroupSelectSecond.setCheckedButton(idOption)

                            updateResultCodeByIdOptions(inputTextAreaSecond,
                                                        idOption)
                        }
                    }
                }

                ResultArea {
                    id: inputTextArea
                    width: parent.width
                    height: parent.height - buttonGroupSelect.height
                }
            }

            Column {
                id: columnSecondTextArea
                width: columnResult.width / 2
                height: parent.height
                visible: false

                ButtonGroupSelect {
                    id: buttonGroupSelectSecond
                    width: parent.width
                    height: 40
                    options: optionsGroupSelectSecond
                    hasCloseActive: true

                    onOptionSelected: function (idOption) {
                        updateResultCodeByIdOptions(inputTextAreaSecond,
                                                    idOption)
                    }

                    onClosed: function (idOption) {

                        removeOptionById(optionsGroupSelectSecond, idOption)

                        if (optionsGroupSelectSecond.count <= 0) {
                            columnSecondTextArea.visible = false
                            return
                        }

                        var idElementFirstOption = optionsGroupSelectSecond.get(
                                    0).idElement

                        updateResultCodeByIdOptions(inputTextAreaSecond,
                                                    idElementFirstOption)

                        buttonGroupSelectSecond.setCheckedButton(
                                    idElementFirstOption)
                    }
                }

                ResultArea {
                    id: inputTextAreaSecond
                    width: parent.width
                    height: parent.height - buttonGroupSelect.height
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
