import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import org.game.engine 1.0
import org.settings.model 1.0

import "Components"

Window {
    id: mainWindow

    visible: true
    minimumWidth: 550;  minimumHeight: 550;
    maximumWidth: 550;  maximumHeight: 550;

    Rectangle {
        width: parent.width
        height: parent.height
        border.width: 2
    }

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
        }
    }

    GameModel {
        id: gameModel
        winSequence: settings.winSequence

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
    }

    SettingsModel {
        id: settings
    }
}
