import QtQuick 2.0

Item {
    id: cross
    property color clr: "black"

    Rectangle {
        width: 80
        height: 4
        rotation: 45
        color: clr
        anchors.centerIn: parent
    }

    Rectangle {
        width: 80
        height: 4
        rotation: 135
        color: clr
        anchors.centerIn: parent
    }
}
