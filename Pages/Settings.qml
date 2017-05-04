import QtQuick 2.0
import QtQuick.Controls 2.1
import org.settings.model 1.0

import "../Settings"
import "../Components"

Item {
    signal pageChanged(string pageName)

    Column {
        spacing: 20
        anchors.centerIn: parent

        Text {
            id: title
            text: qsTr("Settings")
            font.pixelSize: 36
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            spacing: 15

            GameModeSettings {
                id: gameModeSettings
                width: 225
                height: 250
                onModeChanged: {
                    if(gameModeSettings.mode == SettingsModel.TwoPlayers)
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
                width: 225
                height: 250
                Component.onCompleted: {
                    if(settings.gameMode === SettingsModel.TwoPlayers)
                    {
                        hide();
                    }
                    difficulty = settings.difficulty
                }
            }
        }

        Row {
            spacing: 15
            anchors.horizontalCenter: parent.horizontalCenter

            FieldSizeSettings {
                width: 225
                id: fieldSizeSettings

                onSideSizeChanged: {
                    winSequenceSettings.modelUpdated(sideSize);

                    if(sideSize > 3)
                    {
                        gameModeSettings.mode = SettingsModel.TwoPlayers
                        gameModeSettings.computerModeEnabled = false;
                    }
                    else
                    {
                        gameModeSettings.computerModeEnabled = true;
                    }
                }

                Component.onCompleted: {
                    sideSize = settings.sideSize
                }
            }

            WinSequenceSettings {
                width: 225
                id: winSequenceSettings

                Component.onCompleted: {
                    sequence = settings.winSequence
                }
            }
        }

        CustomButton {
            anchors.horizontalCenter: parent.horizontalCenter

            width: 180
            height: 50
            text: qsTr("Save")
            font.pixelSize: 26

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
