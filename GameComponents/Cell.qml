import QtQuick 2.0
import org.game.engine 1.0

Item {
    id: cell
    property color shapeColor: "black"
    property int number
    property bool occupied: false

    Rectangle {
        id: rect
        width: parent.width
        height: parent.height
        border.color: "black"

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                if(!occupied && !gameModel.gameFinished) {
                    gameModel.setCellOccupied(number);
                }
            }

            onEntered: {
                if(!occupied && !gameModel.gameFinished) {
                    cell.state = (gameModel.currentPlayer === 1) ? "cross" :"nought"
                }
            }

            onExited: {
                if(!occupied && !gameModel.gameFinished) {
                    cell.state = "empty"
                }
            }
        }
    }

    Loader {
        id: dialLoader
        anchors.fill: parent

        onLoaded: {
            binder.target = dialLoader.item;
        }
    }

    Binding {
        id: binder

        property: "shapeColor"
        value: shapeColor
    }

    states: [
        State {
            name: "empty"
            PropertyChanges { target: dialLoader; source: ""; }
        },
        State {
            name: "nought"
            PropertyChanges { target: cell; shapeColor: occupied ? "black" : "darkgrey"; }
            PropertyChanges { target: dialLoader; source: "Nought.qml"; }
        },
        State {
            name: "cross"
            PropertyChanges { target: cell; shapeColor: occupied ? "black" : "darkgrey"; }
            PropertyChanges { target: dialLoader; source: "Cross.qml"; }
        }
    ]
}
