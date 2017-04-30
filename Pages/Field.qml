import QtQuick 2.0
import org.game.engine 1.0

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

        onDialogClosed: {
            loader.source = "MainMenu.qml"
        }
    }

    GameModel {
        id: gameModel
        onWinnerChange: {
            if(gameModel.winner)
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
            startGame(settings.sideSize, settings.gameMode,
                      settings.difficulty, settings.winSequence);
        }
    }

}
