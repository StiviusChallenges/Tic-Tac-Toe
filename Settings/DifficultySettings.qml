import QtQuick 2.0
import QtQuick.Controls 2.1

import "../Components"

CustomGroupBox {
    signal hide
    signal show
    property int difficulty: 1

    title: qsTr("Difficulty")

    Column {
        RadioButton {
            text: "Easy"
            font.pixelSize: 16
            checked: (difficulty == 1) ? true : false

            onCheckedChanged:  {
                if(checked) {
                    difficulty = 1
                }
            }
        }

        RadioButton {
            text: "Normal"
            font.pixelSize: 16
            checked: (difficulty == 2) ? true : false

            onCheckedChanged:  {
                if(checked) {
                    difficulty = 2
                }
            }
        }

        RadioButton {
            text: "Hard"
            font.pixelSize: 16
            checked: (difficulty == 3) ? true : false

            onCheckedChanged:  {
                if(checked) {
                    difficulty = 3
                }
            }
        }
    }

    onShow: {
        visible = true
    }

    onHide: {
        visible = false
    }
}

