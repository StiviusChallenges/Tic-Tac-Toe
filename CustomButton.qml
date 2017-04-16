import QtQuick 2.0
import QtQuick.Controls 2.1

Button {
    id: button
    font.pixelSize: 16

    contentItem: Text {
        text: button.text
        font: button.font
        color: button.hovered ? "white" : "black"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        implicitWidth: parent.width
        implicitHeight: parent.height
        border.color: "black"
        color: button.hovered ? "black" : "white"
        border.width: 2
        radius: 5
    }
}
