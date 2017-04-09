import QtQuick 2.0

Item {
    property string textButton
    signal buttonClicked

    id: root
    width: 200
    height: 60

    Rectangle {
        id: buttonRect
        width: root.width
        height: root.height
        radius: 5
        color: "white"
        border.color: "black"
        border.width: 2

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onClicked:  {
                buttonClicked();
            }

            onEntered: {
                parent.color = "black"
                text.color = "white"
            }
            onExited: {
                parent.color = "white"
                text.color = "black"
            }
        }

        Text {
            id: text
            text: textButton
            color: "black"
            font.pixelSize: 24
            anchors.centerIn: parent
        }
    }
}
