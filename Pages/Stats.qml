import QtQuick 2.0

import "../Components"

Item {
    signal pageChanged(string pageName)

    function loadElements() {
        statsModel.append({name: "Total games: ", value: gameModel.totalGames});
        statsModel.append({name: "Player 1 scores: ", value: gameModel.score1});
        statsModel.append({name: "Player 2 scores: ", value: gameModel.score2});
    }

    ListModel {
        signal modelUpdated
        id: statsModel

        Component.onCompleted: {
            loadElements();
        }

        onModelUpdated: {
            clear();
            loadElements();
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

        Row {
            spacing: 10
            CustomButton {
                text: "Clear stats"
                width: 125
                height: 35

                onClicked: {
                    gameModel.clearStats();
                    statsModel.modelUpdated();
                    message.showDialog();
                }
            }

            CustomButton {
                text: "Go to menu"
                width: 125
                height: 35

                onClicked: {
                    pageChanged("Pages/MainMenu.qml")
                }
            }
        }
    }

    DialogBox {
        id: message
        textToShow: "Stats has been cleared."
    }
}
