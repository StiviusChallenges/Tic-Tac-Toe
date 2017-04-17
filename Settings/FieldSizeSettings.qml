import QtQuick 2.0

import "../Components"

Column {
    property int currentSideSize: fieldSizeBox.currentIndex + 3

    Text {
        id: fieldSizeLabel
        text: qsTr("Field size")
        font.pixelSize: 18
    }

    CustomComboBox {
        id: fieldSizeBox
        anchors.horizontalCenter: fieldSizeLabel.horizontalCenter
        width: 100
        model: ["3x3", "4x4", "5x5", "6x6", "7x7", "8x8", "9x9", "10x10"]
    }
}
