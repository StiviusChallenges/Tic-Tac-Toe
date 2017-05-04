import QtQuick 2.0
import QtQuick.Layouts 1.3

import "../Components"

Item {
    signal pageChanged(string pageName)

    ColumnLayout {
        spacing: 30
        anchors.centerIn: parent

        CustomButton {
            width: 350
            height: 80
            text: "New game"
            font.pixelSize: 36
            onClicked:  {
                pageChanged("Pages/Field.qml");
            }
        }

        CustomButton {
            width: 350
            height: 80
            text: "Stats"
            font.pixelSize: 36
            onClicked:  {
                pageChanged("Pages/Stats.qml");
            }
        }

        CustomButton {
            width: 350
            height: 80
            text: "Settings"
            font.pixelSize: 36
            onClicked:  {
                pageChanged("Pages/Settings.qml");
            }
        }


        CustomButton {
            width: 350
            height: 80
            text: "Exit"
            font.pixelSize: 36
            onClicked:  {
                Qt.quit();
            }
        }
    }
}
