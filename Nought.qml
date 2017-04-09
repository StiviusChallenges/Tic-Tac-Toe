import QtQuick 2.0

Item {
    id: nought
    property color clr: "black"

    Rectangle {
        width: 70
        height: 70
        radius: width * 0.5
        anchors.centerIn: parent
        border.color: clr
        border.width: 4
    }
}
