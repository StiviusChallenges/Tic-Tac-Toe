import QtQuick 2.0

import "../Components"

Item {
    signal pageChanged(string pageName)

    Column {
        spacing: 30
        anchors.centerIn: parent

        CustomButton {
            width: 200
            height: 60
            text: "New game"
            font.pixelSize: 24
            onClicked:  {
                pageChanged("Pages/Field.qml");
            }
        }

        CustomButton {
            width: 200
            height: 60
            text: "Stats"
            font.pixelSize: 24
            onClicked:  {
                pageChanged("Pages/Stats.qml");
            }
        }

        CustomButton {
            width: 200
            height: 60
            text: "Settings"
            font.pixelSize: 24
            onClicked:  {
                pageChanged("Pages/Settings.qml");
            }
        }


        CustomButton {
            width: 200
            height: 60
            text: "Exit"
            font.pixelSize: 24
            onClicked:  {
                Qt.quit();
            }
        }
    }
}
