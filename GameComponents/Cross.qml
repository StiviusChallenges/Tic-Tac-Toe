import QtQuick 2.0

Item {
    id: cross
    property color shapeColor: "black"

    Rectangle {
        width: 155 * 3/settings.sideSize * 0.87
        height: 8 * 3/settings.sideSize
        rotation: 45
        color: shapeColor
        anchors.centerIn: parent
    }

    Rectangle {
        width: 155 * 3/settings.sideSize * 0.87
        height: 8 * 3/settings.sideSize
        rotation: 135
        color: shapeColor
        anchors.centerIn: parent
    }
}
