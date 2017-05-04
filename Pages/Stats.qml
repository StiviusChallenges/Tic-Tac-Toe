import QtQuick 2.0
import org.stats.model 1.0

import "../Components"

Item {
    signal pageChanged(string pageName)

    function loadElements() {
        listModel.append({name: "Total games: ", value: statsModel.totalGames});
        listModel.append({name: "Player 1 scores: ", value: statsModel.score1});
        listModel.append({name: "Player 2 scores: ", value: statsModel.score2});
        listModel.append({name: "Draws: ", value: statsModel.totalGames - statsModel.score1 - statsModel.score2});
    }

    ListModel {
        signal modelUpdated
        id: listModel

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
            model: listModel

            delegate: Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: name + value
                color: "black"
                font.pixelSize: 36
            }
        }

        Row {
            spacing: 10
            CustomButton {
                text: "Clear stats"
                width: 200
                height: 60
                font.pixelSize: 24

                onClicked: {
                    statsModel.clearStats();
                    listModel.modelUpdated();
                    message.showDialog();
                }
            }

            CustomButton {
                text: "Go to menu"
                width: 200
                height: 60
                font.pixelSize: 24

                onClicked: {
                    pageChanged("Pages/MainMenu.qml")
                }
            }
        }
    }

    DialogBox {
        id: message
        textToShow: "Stats has been cleared."
        textSecondButton: "Close"
    }

    StatsModel {
        id: statsModel
    }
}
