import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4

Item {
    transformOrigin: Item.Center
    Label {
        id: ctrlLbl
        text: qsTr("Test Label")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 8
    }

    Button {
        id: ctrlBtn
        height: 100
        text: qsTr("I am a button")
        anchors.top: ctrlLbl.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: ctrlLbl.horizontalCenter
        onClicked: {
            ctrlPopup.open()
        }
    }

    ProgressBar {
        id: ctrlProgress
        value: 0.35

        anchors.top: ctrlBtn.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: ctrlBtn.horizontalCenter
    }

    BusyIndicator {
        id: ctrlBusy
        running: image.status === Image.Loading

        anchors.top: ctrlProgress.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: ctrlProgress.horizontalCenter
    }

    Popup {
        id: ctrlPopup
        x: 100
        y: 100
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        padding: 0

        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 300
        }

        contentItem: Item {
            TreeView {
                anchors.fill: parent
                TableViewColumn {
                    title: "Name"
                    role: "fileName"
                    width: 200
                }

                rowDelegate: Rectangle { height: 50 }

                model: fsModel
            }
        }
    }
}
