import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    property string textToShow
    property string textFirstButton
    property string textSecondButton

    signal firstButtonChosen
    signal secondButtonChosen
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
            id: rect
            width: 400
            height: 175
            anchors.centerIn: parent
            radius: 5
            border.color: "black"

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 50

                text: textToShow
                font.pixelSize: 28
            }

            RowLayout {
                spacing: 25
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10

                CustomButton {
                    id: firstButton
                    visible: (textFirstButton != "") ? true : false
                    width: rect.width/2.5
                    height: rect.height/4.25

                    text: textFirstButton
                    font.pixelSize: 22
                    onClicked:  {
                        dialog.visible = false;
                        firstButtonChosen();
                    }
                }

                CustomButton {
                    id: secondButton
                    visible: (textSecondButton != "") ? true : false
                    width: rect.width/2.5
                    height: rect.height/4.25

                    text: textSecondButton
                    font.pixelSize: 22
                    onClicked:  {
                        dialog.visible = false;
                        secondButtonChosen();
                    }
                }
            }


        }
    }

    onShowDialog: {
        visible = true
    }
}
