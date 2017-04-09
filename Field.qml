import QtQuick 2.0

Item {
    property int playerTurn: 0
    signal pageChanged(string pageName)

    id: field

    Grid {
        columns: 3
        anchors.centerIn: parent
        anchors.margins: 8
        spacing: 1
        Repeater {
            model: 9
            Cell {
                width: 100; height: 100;

                onGameFinished: {
                    pageChanged("MainMenu.qml")
                }
            }
        }
    }
}
