import QtQuick 2.0
import QtQuick.Controls 2.1

ComboBox {
    id: combobox

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
}
