import QtQuick 2.0
import QtQuick.Controls 2.1
import org.settings.model 1.0

import "../Components"

CustomGroupBox {
    signal hide
    signal show
    property int difficulty: SettingsModel.Easy

    title: qsTr("Difficulty")
    font.pixelSize: 24

    Column {
        anchors.centerIn: parent

        RadioButton {
            text: "Easy"
            font.pixelSize: 30
            checked: (difficulty == SettingsModel.Easy) ? true : false

            indicator.width: 35
            indicator.height: 35

            onCheckedChanged:  {
                if(checked) {
                    difficulty = SettingsModel.Easy
                }
            }
        }

        RadioButton {
            text: "Normal"
            font.pixelSize: 30
            checked: (difficulty == SettingsModel.Medium) ? true : false

            indicator.width: 35
            indicator.height: 35

            onCheckedChanged:  {
                if(checked) {
                    difficulty = SettingsModel.Medium
                }
            }
        }

        RadioButton {
            text: "Hard"
            font.pixelSize: 30
            checked: (difficulty == SettingsModel.Hard) ? true : false

            indicator.width: 35
            indicator.height: 35

            onCheckedChanged:  {
                if(checked) {
                    difficulty = SettingsModel.Hard
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

