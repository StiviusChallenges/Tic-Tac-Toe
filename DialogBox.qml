import QtQuick 2.0

Item {
    property string textToShow
    signal dialogClosed
    signal showDialog

    id: dialog
    visible: false
    width: parent.width
    height: parent.height

    Rectangle {
        width: parent.width
        height: parent.height
        color: Qt.rgba(0, 0, 0, 0.75)

        Rectangle {
            width: 225
            height: 125
            anchors.centerIn: parent
            radius: 5
            border.color: "black"

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 30

                text: textToShow
                font.pixelSize: 18
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10

                width: parent.width/2.5
                height: parent.height/3.5

                textButton: "Close"
                textFontSize: 16
                onButtonClicked:  {
                    dialog.visible = false;
                    dialogClosed();
                }
            }
        }
    }

    onShowDialog: {
        visible = true
    }
}
