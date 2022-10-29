import QtQuick 2.0
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0

import "../"

import br.com.SettingsController 1.0

Popup {
    id: popup
    focus: true
    modal: true
    anchors.centerIn: parent

    closePolicy: function () {
        return Popup.CloseOnEscape || Popup.CloseOnPressOutsideParent
    }

    background: Rectangle {
        border.color: "#fff"
        radius: 5
    }

    SettingsController {
        id: control
    }

    Rectangle {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.rightMargin: 10

        Image {
            id: img
            width: mouseAreaClose.containsMouse ? 20 : 18
            height: mouseAreaClose.containsMouse ? 20 : 18
            source: "../../img/close-icon.png"
            anchors.centerIn: parent
        }
        ColorOverlay {
            anchors.fill: img
            source: img
            color: "#9298ad"
        }

        MouseArea {
            id: mouseAreaClose
            anchors.fill: img
            hoverEnabled: true

            onClicked: {
                popup.close()
            }
        }
    }

    Column {
        width: parent.width / 1.2
        height: parent.height / 1.2
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 30

        Column {
            width: parent.width
            height: parent.height - buttonSave.height
            spacing: 40

            Label {
                text: "Configurações"
                color: "#4285f4"
                font.pointSize: 17
            }

            Row {
                width: parent.width
                height: parent.height

                Column {
                    width: parent.width - switchCustom.width
                    height: parent.height
                    spacing: 10

                    Label {
                        text: "Executar codigo"
                        color: "#4285f4"
                        font.pointSize: 13
                    }

                    Label {
                        text: "Habilitar execução do código ao convertê-lo"
                        color: "#9298ad"
                        font.pointSize: 8
                    }
                }

                SwitchCustom {
                    id: switchCustom
                    checked: control.isRunCode
                }
            }
        }

        ButtonCustom {
            id: buttonSave
            colorDefault: "#4285f4"
            colorPressed: "#1f6ff2"
            width: parent.width / 2
            text: "Save"

            onClicked: {
                control.writeConfigs(switchCustom.checked)
                popup.close()
            }
        }
    }
}
