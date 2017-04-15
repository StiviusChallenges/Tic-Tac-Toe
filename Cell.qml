import QtQuick 2.0

Item {
    id: cell
    property color shapeColor: "black"
    property int number
    property bool occupied: false

    Rectangle {
        id: rect
        width: 100
        height: 100
        border.color: "black"

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                if(!occupied && !gameModel.gameFinished) {
                    cell.state = (gameModel.currentPlayer === 1) ? "cross" :"nought"
                    occupied = true
                    gameModel.currentCell = number
                    gameModel.changeTurn();
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
            PropertyChanges { target: cell; shapeColor: (occupied) ? "black" : "darkgrey"; }
            PropertyChanges { target: dialLoader; source: "Nought.qml"; }
        },
        State {
            name: "cross"
            PropertyChanges { target: cell; shapeColor: (occupied) ? "black" : "darkgrey"; }
            PropertyChanges { target: dialLoader; source: "Cross.qml"; }
        }
    ]
}
