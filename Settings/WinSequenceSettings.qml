import QtQuick 2.0

import "../Components"

Column {
    signal modelUpdated(int currentSideSize)
    property int winSequence

    Text {
        id: winSequenceLabel
        text: qsTr("Win sequence")
        font.pixelSize: 18
    }

    ListModel {
        id: winSequenceModel
    }

    CustomComboBox {
        id: winSequenceBox
        currentIndex: 0
        anchors.horizontalCenter: winSequenceLabel.horizontalCenter
        width: 100
        model: winSequenceModel

        onCurrentIndexChanged: {
            if(currentIndex != -1)
            {
                winSequence = winSequenceModel.get(winSequenceBox.currentIndex).value
            }
        }
    }

    onModelUpdated: {
        winSequenceModel.clear();
        for(var i = 3; i <= currentSideSize; ++i)
        {
            winSequenceModel.append({"value": i});
        }
        winSequenceBox.currentIndex = 0
    }
}
