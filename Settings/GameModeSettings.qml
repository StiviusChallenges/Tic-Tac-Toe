import QtQuick 2.0
import QtQuick.Controls 2.1

import "../Components"

CustomGroupBox {
    signal gameModeChanged(int mode);

    title: qsTr("Game Mode")

    Column {
        anchors.centerIn: parent
        spacing: 20

        RadioButton {
            text: "2-players mode"
            font.pixelSize: 16
            checked: true

            onClicked: {
                gameModeChanged(1);
            }
        }

        RadioButton {
            text: "Computer mode"
            font.pixelSize: 16

            onClicked: {
                gameModeChanged(2);
            }
        }
    }
}
