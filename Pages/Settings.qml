import QtQuick 2.0
import QtQuick.Controls 2.1

import "../Settings"
import "../Components"

Item {
    signal pageChanged(string pageName)

    Column {
        spacing: 10
        anchors.centerIn: parent

        Text {
            id: title
            text: qsTr("Settings")
            font.pixelSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            spacing: 10

            GameModeSettings {
                id: gameModeSettings
                height: difficultySettings.height
                onGameModeChanged: {
                    if(mode == 1)
                        difficultySettings.visible = false
                    else
                        difficultySettings.visible = true
                }
            }

            DifficultySettings {
                id: difficultySettings
                visible: false
            }

        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            FieldSizeSettings { }
            WinSequenceSettings { }
        }

        CustomButton {
            anchors.horizontalCenter: parent.horizontalCenter

            width: 125
            height: 35
            text: qsTr("Save")
            font.pixelSize: 16

            onClicked:  {
                pageChanged("Pages/MainMenu.qml")
            }
        }
    }
}
