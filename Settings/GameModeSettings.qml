import QtQuick 2.0
import QtQuick.Controls 2.1
import org.settings.model 1.0

import "../Components"

CustomGroupBox {
    property int mode: SettingsModel.Computer
    property alias computerModeEnabled: computerModeBtn.enabled

    title: qsTr("Game Mode")
    font.pixelSize: 24

    Column {
        anchors.centerIn: parent
        spacing: 20

        RadioButton {
            id: computerModeBtn
            text: "Computer mode"
            font.pixelSize: 20
            checked: (mode == SettingsModel.Computer) ? true : false

            indicator.width: 35
            indicator.height: 35

            onClicked: {
                mode = SettingsModel.Computer
            }
        }

        RadioButton {
            text: "2-players mode"
            font.pixelSize: 20
            checked: (mode == SettingsModel.TwoPlayers) ? true : false

            indicator.width: 35
            indicator.height: 35

            onClicked: {
                mode = SettingsModel.TwoPlayers
            }
        }
    }
}
