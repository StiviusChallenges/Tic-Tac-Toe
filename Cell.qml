import QtQuick 2.0

Item {
    id: cell
    property color clr: "black"
    property bool occupied: false
    signal gameFinished

    Rectangle {
        id: rect
        width: 100
        height: 100
        border.color: "black"

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                if(!occupied) {
                    cell.state = (gameModel.currentPlayer === 1) ? "cross" :"nought"
                    occupied = true
                    gameModel.currentPlayer = (gameModel.currentPlayer === 1) ? 2 : 1
                }
            }

            onEntered: {
                if(!occupied) {
                    cell.state = (gameModel.currentPlayer === 1) ? "cross" :"nought"
                }
            }

            onExited: {
                if(!occupied) {
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

        property: "clr"
        value: clr
    }

    states: [
        State {
            name: "empty"
            PropertyChanges { target: dialLoader; source: ""; }
        },
        State {
            name: "nought"
            PropertyChanges { target: cell; clr: (occupied) ? "black" : "darkgrey"; }
            PropertyChanges { target: dialLoader; source: "Nought.qml"; }
        },
        State {
            name: "cross"
            PropertyChanges { target: cell; clr: (occupied) ? "black" : "darkgrey"; }
            PropertyChanges { target: dialLoader; source: "Cross.qml"; }
        }
    ]
}
