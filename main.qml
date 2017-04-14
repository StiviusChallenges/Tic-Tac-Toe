import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import org.game.engine 1.0

Window {
    id: mainWindow

    visible: true
    width: 325
    height: 325

    Loader {
        id: loader
        width: parent.width
        height: parent.height

        source: "MainMenu.qml"
    }

    Connections {
        id: connection
        target: loader.item

        onPageChanged: {
            loader.source = pageName
        }
    }

    DialogBox {
        id: dialog

        onDialogClosed: {
            loader.source = "MainMenu.qml"
            gameModel.restartGame();
        }
    }

    GameModel {
        id: gameModel
        currentPlayer: 1

        onWinnerChange: {
            dialog.textToShow = "Player " + gameModel.winner + " won this game!"
            dialog.showDialog();
        }
    }
}
