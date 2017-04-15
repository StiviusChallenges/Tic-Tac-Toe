import QtQuick 2.0

Item {
    property int playerTurn: 0
    signal pageChanged(string pageName)

    id: field

    Grid {
        columns: gameModel.sideSize
        anchors.centerIn: parent
        anchors.margins: 8
        spacing: 1
        Repeater {
            model: gameModel.sideSize * gameModel.sideSize
            Cell {
                width: 100; height: 100;
                number: index
            }
        }
    }
}
