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
                onModeChanged: {
                    if(gameModeSettings.mode == 1)
                    {
                        difficultySettings.hide();
                    }
                    else
                    {
                        difficultySettings.show();
                    }
                }

                Component.onCompleted: {
                    mode = settings.gameMode
                }
            }

            DifficultySettings {
                id: difficultySettings

                Component.onCompleted: {
                    if(settings.gameMode == 1)
                    {
                        hide();
                    }
                    difficulty = settings.difficulty
                }
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            FieldSizeSettings {
                id: fieldSizeSettings

                onSideSizeChanged: {
                    winSequenceSettings.modelUpdated(sideSize);
                }

                Component.onCompleted: {
                    sideSize = settings.sideSize
                }
            }

            WinSequenceSettings {
                id: winSequenceSettings

                Component.onCompleted: {
                    sequence = settings.winSequence
                }
            }
        }

        CustomButton {
            anchors.horizontalCenter: parent.horizontalCenter

            width: 125
            height: 35
            text: qsTr("Save")
            font.pixelSize: 16

            onClicked:  {
                settings.sideSize = fieldSizeSettings.sideSize
                settings.winSequence = winSequenceSettings.sequence
                settings.gameMode = gameModeSettings.mode
                settings.difficulty = difficultySettings.difficulty
                settings.saveSettings();
                pageChanged("Pages/MainMenu.qml")
            }
        }
    }
}
