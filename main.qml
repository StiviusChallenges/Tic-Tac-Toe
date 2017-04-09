import QtQuick 2.7
import QtQuick.Window 2.2
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
        target: loader.item

        onPageChanged: {
            loader.source = pageName
        }
    }

    GameModel {
        id: gameModel
        score1: 0
        score2: 0
        currentPlayer: 1
    }
}
