import QtQuick 2.0

import "../Components"

Column {
    property int sideSize

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Field size")
        font.pixelSize: 20
    }

    CustomComboBox {
        id: fieldSizeBox
        currentIndex: sideSize - 3
        width: parent.width
        font.pixelSize: 18
        model: ["3x3", "4x4", "5x5", "6x6", "7x7", "8x8", "9x9", "10x10"]

        onCurrentIndexChanged: {
            sideSize = currentIndex + 3
        }
    }
}
