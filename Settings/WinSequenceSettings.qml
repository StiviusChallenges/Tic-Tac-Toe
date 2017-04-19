import QtQuick 2.0

import "../Components"

Column {
    signal modelUpdated(int currentSideSize)
    property int sequence

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
        currentIndex: sequence - 3
        anchors.horizontalCenter: winSequenceLabel.horizontalCenter
        width: 100
        model: winSequenceModel

        onCurrentIndexChanged: {
            if(currentIndex != -1)
            {
                sequence = currentIndex + 3
            }
        }
    }

    onModelUpdated: {
        winSequenceModel.clear();
        for(var i = 3; i <= currentSideSize; ++i)
        {
            winSequenceModel.append({"value": i});
        }
        if(winSequenceBox.currentIndex == -1)
        {
            winSequenceBox.currentIndex = 0;
        }
    }
}
