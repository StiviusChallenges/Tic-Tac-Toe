import QtQuick 2.0

Item {
    id: nought
    property color shapeColor: "black"

    Rectangle {
        width: 155 * 3/settings.sideSize * 0.75
        height: 155 * 3/settings.sideSize * 0.75
        radius: width * 0.5
        anchors.centerIn: parent
        border.color: shapeColor
        border.width: 6 * 3/settings.sideSize
    }
}
