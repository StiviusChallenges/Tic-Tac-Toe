import QtQuick 2.0
import QtQuick.Controls 2.1

Item {
    signal pageChanged(string pageName)

    Column {
        spacing: 10
        anchors.centerIn: parent

        Text {
            id: title
            text: qsTr("Settings")
            font.pixelSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            spacing: 10

            GroupBox {
                id: gamemodeGroup
                font.pixelSize: 18
                height: diffucultyGroup.height

                label: Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Game Mode")
                    color: "black"
                }

                background: Rectangle {
                    y: gamemodeGroup.topPadding - gamemodeGroup.padding
                    height: gamemodeGroup.height - gamemodeGroup.topPadding + gamemodeGroup.padding
                    border.color: "black"
                    border.width: 2
                    radius: 5
                }

                Column {
                    anchors.centerIn: parent
                    spacing: 20

                    RadioButton {
                        text: "2-players mode"
                        font.pixelSize: 16
                        checked: true

                        onClicked: {
                            diffucultyGroup.visible = false
                        }
                    }

                    RadioButton {
                        text: "Computer mode"
                        font.pixelSize: 16

                        onClicked: {
                            diffucultyGroup.visible = true
                        }
                    }
                }
            }

            GroupBox {
                id: diffucultyGroup
                font.pixelSize: 18
                visible: false

                label: Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Difficulty")
                    color: "black"
                }

                background: Rectangle {
                    y: diffucultyGroup.topPadding - diffucultyGroup.padding
                    height: diffucultyGroup.height - diffucultyGroup.topPadding + diffucultyGroup.padding
                    border.color: "black"
                    border.width: 2
                    radius: 5
                }

                Column {
                    RadioButton {
                        text: "Easy"
                        font.pixelSize: 16
                        checked: true
                    }

                    RadioButton {
                        text: "Normal"
                        font.pixelSize: 16
                    }

                    RadioButton {
                        text: "Hard"
                        font.pixelSize: 16
                    }
                }
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            Column {
                Text {
                    id: firstLabel
                    text: qsTr("Field size")
                    font.pixelSize: 18
                }

                ComboBox {
                    id: combobox
                    anchors.horizontalCenter: firstLabel.horizontalCenter
                    width: 100
                    background: Rectangle {
                        border.color: "black"
                        border.width: 2
                        radius: 5
                    }
                    delegate: ItemDelegate {
                        width: combobox.width
                        contentItem: Text {
                            text: modelData
                            color: combobox.highlightedIndex == index ? "white" : "black"
                            font: combobox.font
                            verticalAlignment: Text.AlignVCenter
                        }
                        background: Rectangle {
                            color: combobox.highlightedIndex == index ? "black" : "transparent"
                            border.width: 0
                        }
                        highlighted: combobox.highlightedIndex == index
                    }
                    popup: Popup {
                        y: combobox.height - 1
                        width: combobox.width
                        implicitHeight: listview.contentHeight
                        padding: 1

                        contentItem: ListView {
                            id: listview
                            clip: true
                            model: combobox.popup.visible ? combobox.delegateModel : null
                            currentIndex: combobox.highlightedIndex

                            ScrollIndicator.vertical: ScrollIndicator { }
                        }

                        background: Rectangle {
                            border.color: "black"
                            border.width: 2
                            radius: 5
                        }
                    }
                    model: ["3x3", "4x4", "5x5", "6x6", "7x7", "8x8", "9x9", "10x10"]
                }
            }

            Column {
                Text {
                    id: secondLabel
                    text: qsTr("Win sequence")
                    font.pixelSize: 18
                }

                ComboBox {
                    id: combobox2
                    anchors.horizontalCenter: secondLabel.horizontalCenter
                    width: 100
                    background: Rectangle {
                        border.color: "black"
                        border.width: 2
                        radius: 5
                    }
                    delegate: ItemDelegate {
                        width: combobox2.width
                        contentItem: Text {
                            text: modelData
                            color: combobox2.highlightedIndex == index ? "white" : "black"
                            font: combobox2.font
                            verticalAlignment: Text.AlignVCenter
                        }
                        background: Rectangle {
                            color: combobox2.highlightedIndex == index ? "black" : "transparent"
                            border.width: 0
                        }
                        highlighted: combobox2.highlightedIndex == index
                    }

                    popup: Popup {
                        y: combobox2.height - 1
                        width: combobox2.width
                        implicitHeight: listview2.contentHeight
                        padding: 1

                        contentItem: ListView {
                            id: listview2
                            clip: true
                            model: combobox2.popup.visible ? combobox2.delegateModel : null
                            currentIndex: combobox2.highlightedIndex

                            ScrollIndicator.vertical: ScrollIndicator { }
                        }

                        background: Rectangle {
                            border.color: "black"
                            border.width: 2
                            radius: 5
                        }
                    }
                    model: ["3", "4", "5", "6", "7", "8", "9", "10"]
                }
            }
        }



        CustomButton {
            anchors.horizontalCenter: parent.horizontalCenter

            width: 125
            height: 35

            text: "Save"
            font.pixelSize: 16
            onClicked:  {
                gameModel.sideSize = 4
                //gameModel.winSequence = 4
                pageChanged("MainMenu.qml")
            }
        }

    }
}
