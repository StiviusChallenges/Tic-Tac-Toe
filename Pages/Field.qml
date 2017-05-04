import QtQuick 2.0
import org.game.engine 1.0
import org.stats.model 1.0
import org.settings.model 1.0

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
                id: repeater
                model: settings.sideSize * settings.sideSize
                Cell {
                    width: 155 * 3/settings.sideSize; height: 155  * 3/settings.sideSize;
                    number: index
                }
            }
        }

        CustomButton {
            id: back
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

    DialogBox {
        id: dialog
        textSecondButton: "Close"

        onSecondButtonChosen: {
            loader.source = "MainMenu.qml"
        }
    }

    DialogBox {
        id: choiceBox
        textToShow: "Choose your side"
        textFirstButton: "Crosses"
        textSecondButton: "Noughts"

        onFirstButtonChosen: {
            gameModel.startGame(settings.sideSize, settings.difficulty, settings.winSequence, SettingsModel.Computer, 2);
        }

        onSecondButtonChosen: {
            gameModel.startGame(settings.sideSize, settings.difficulty, settings.winSequence, SettingsModel.Computer, 1);
        }
    }

    GameModel {
        id: gameModel
        onWinnerChange: {
            if(winner)
            {
                dialog.textToShow = "Player " + gameModel.winner + " won this game!"
            }
            else
            {
                dialog.textToShow = "Draw! Nobody won this game."
            }
            dialog.showDialog();
        }

        onCellOccupied: {
            repeater.itemAt(cell).state = (gameModel.currentPlayer === 1) ? "cross" :"nought"
            repeater.itemAt(cell).occupied = true
            gameModel.changeTurn();
        }

        Component.onCompleted: {
            if(settings.gameMode === SettingsModel.Computer)
            {
                choiceBox.showDialog();
            }
            else
            {
                startGame(settings.sideSize, settings.difficulty,
                          settings.winSequence, SettingsModel.TwoPlayers);
            }
        }
    }

}
