import QtQuick 2.0

Item {
    signal pageChanged(string pageName)

    Column {
        spacing: 30
        anchors.centerIn: parent

        Button {
            textButton: "New game"
            onButtonClicked:  {
                pageChanged("Field.qml");
            }
        }

        Button {
            textButton: "Stats"
            onButtonClicked:  {
                pageChanged("Stats.qml");
            }
        }

        Button {
            textButton: "Exit"
            onButtonClicked:  {
                Qt.quit();
            }
        }
    }
}
