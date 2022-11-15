import QtQuick 2.0

Rectangle {
    width: 200
    height: 200

    ListModel {
        id: model

        ListElement {
            upCode: "01010"
            description: "LOAD"
        }

        ListElement {
            upCode: "12121"
            description: "MOV"
        }
    }

    Rectangle {

        width: 200
        height: 200
        anchors.centerIn: parent

        Column {
            anchors.fill: parent
            anchors.margins: 20

            Row {
                width: parent.width
                height: 30
                spacing: 20

                Text {
                    text: "UPCODE"
                    color: "#4285f4"
                    font.pointSize: 10
                }

                Text {
                    text: "DESCRICAO"
                    color: "#4285f4"
                    font.pointSize: 10
                }
            }

            Repeater {
                model: model

                Row {
                    width: parent.width
                    height: 25
                    spacing: 40

                    Text {
                        text: upCode
                        color: "#565656"
                    }

                    Text {
                        text: description
                        color: "#565656"
                    }
                }
            }
        }
    }
}
