import QtQuick 2.0
import QtQuick.Controls 2.1

import "../Components"

CustomGroupBox {
    title: qsTr("Difficulty")

    Column {
        RadioButton {
            text: "Easy"
            font.pixelSize: 16
            checked: true
        }

        RadioButton {
            text: "Normal"
            font.pixelSize: 16
        }

        RadioButton {
            text: "Hard"
            font.pixelSize: 16
        }
    }
}

