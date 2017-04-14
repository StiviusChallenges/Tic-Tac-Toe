import QtQuick 2.0

Item {
    id: nought
    property color shapeColor: "black"

    Rectangle {
        width: 70
        height: 70
        radius: width * 0.5
        anchors.centerIn: parent
        border.color: shapeColor
        border.width: 4
    }
}
