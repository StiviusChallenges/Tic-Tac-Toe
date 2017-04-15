import QtQuick 2.0

Item {
    signal pageChanged(string pageName)

    ListModel {
        id: statsModel

        Component.onCompleted: {
             append({name: "Total games: ", value: gameModel.totalGames});
             append({name: "Player 1 scores: ", value: gameModel.score1});
             append({name: "Player 2 scores: ", value: gameModel.score2});
        }
    }

    Column {
        spacing: 30
        anchors.centerIn: parent

        Repeater {
            model: statsModel

            delegate: Text {
                text: name + value
                color: "black"
                font.pixelSize: 22
            }
        }

        Button {
            textButton: "Go to menu"
            width: 160
            height: 40

            onButtonClicked: {
                pageChanged("MainMenu.qml")
            }
        }
    }


}
