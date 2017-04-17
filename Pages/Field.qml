import QtQuick 2.0

import "../Components"
import "../GameComponents"


Item {
    property int playerTurn: 0
    signal pageChanged(string pageName)

    id: field

    Column {
        anchors.centerIn: parent
        spacing: 5

        Grid {
            columns: gameModel.sideSize
            anchors.margins: 8
            spacing: 1
            Repeater {
                model: gameModel.sideSize * gameModel.sideSize
                Cell {
                    width: 100; height: 100;
                    number: index
                }
            }
        }

        CustomButton {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Back"
            width: 100
            height: 35
            font.pixelSize: 16

            onClicked: {
                pageChanged("Pages/MainMenu.qml")
            }
        }
    }

}