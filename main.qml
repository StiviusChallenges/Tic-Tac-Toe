import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import org.game.engine 1.0

import "Components"

Window {
    id: mainWindow

    visible: true
    width: 100 * gameModel.sideSize * 1.2
    height: 100 * gameModel.sideSize * 1.2

    Loader {
        id: loader
        width: parent.width
        height: parent.height

        source: "Pages/MainMenu.qml"
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
            loader.source = "Pages/MainMenu.qml"
            gameModel.restartGame();
        }
    }

    GameModel {
        id: gameModel
        currentPlayer: 1
        sideSize: 4

        onWinnerChange: {
            dialog.showDialog();
        }
    }
}
