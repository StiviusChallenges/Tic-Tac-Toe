import QtQuick 2.0

import "../Components"

Column {
    Text {
        id: winSequenceLabel
        text: qsTr("Win sequence")
        font.pixelSize: 18
    }

    CustomComboBox {
        id: winSequenceBox
        anchors.horizontalCenter: winSequenceLabel.horizontalCenter
        width: 100
        model: ["3", "4", "5", "6", "7", "8", "9", "10"]
    }
}
