import QtQuick 2.0
import QtQuick.Controls 2.1

GroupBox {
    id: group
    font.pixelSize: 18

    label: Label {
        anchors.horizontalCenter: parent.horizontalCenter
        text: title
        color: "black"
    }

    background: Rectangle {
        y: group.topPadding - group.padding
        height: group.height - group.topPadding + group.padding
        border.color: "black"
        border.width: 2
        radius: 5
    }
}
