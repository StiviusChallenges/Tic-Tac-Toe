import QtQuick 2.0
import QtQuick.Controls 2.1

import "../Components"

CustomGroupBox {
    property int mode: 1

    title: qsTr("Game Mode")

    Column {
        anchors.centerIn: parent
        spacing: 20

        RadioButton {
            text: "2-players mode"
            font.pixelSize: 16
            checked: (mode == 1) ? true : false

            onClicked: {
                mode = 1
            }
        }

        RadioButton {
            text: "Computer mode"
            font.pixelSize: 16
            checked: (mode == 2) ? true : false

            onClicked: {
                mode = 2
            }
        }
    }
}
