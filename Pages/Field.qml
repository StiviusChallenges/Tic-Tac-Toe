import QtQuick 2.0

import "../Components"
import "../GameComponents"


Item {
    signal pageChanged(string pageName)

    id: field

    Column {
        anchors.centerIn: parent
        spacing: 5

        Grid {
            columns: settings.sideSize
            anchors.margins: 8
            spacing: 1
            Repeater {
                model: settings.sideSize * settings.sideSize
                Cell {
                    width: 155; height: 155;
                    number: index
                }
            }
        }

        CustomButton {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Back"
            width: 180
            height: 50
            font.pixelSize: 28

            onClicked: {
                pageChanged("Pages/MainMenu.qml")
            }
        }
    }

}
