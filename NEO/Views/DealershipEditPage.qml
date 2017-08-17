import QtQuick 2.0
import "../NEOControls" as NEOControls

BasePage {
    text: "Dealership Information"

    function goToPreviousPage() {
        base.hidePages()
        pageDealership.show()
    }

    Connections {
        target: Qt.inputMethod
        onVisibleChanged: {
            if (!Qt.inputMethod.visible) {
                backpressedHandler.focus = true
            }
        }
    }

    onVisibleChanged: {
        if (visible) {
            base.backPressedCallback = goToPreviousPage
        }
    }

    contents: Item {
        anchors.fill: parent

        Rectangle {
            id: splitter1

            color: base.colorSecondary
            height: 1
            anchors.top: parent.top
            anchors.topMargin: 25
            anchors.left: parent.left
            anchors.right: parent.right
        }

        NEOControls.TextField {
            id: inputName

            anchors.top: splitter1.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 40

            placeholderText: "Enter Dealership Name:"
            font.pixelSize: 20

            color: base.colorSecondary
        }

        Rectangle {
            id: splitter2

            color: base.colorSecondary
            height: 1
            anchors.top: inputName.bottom
            anchors.left: parent.left
            anchors.right: parent.right
        }

        NEOControls.TextField {
            id: inputPhone

            anchors.top: splitter2.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 40

            placeholderText: "Enter Dealership Phone:"
            font.pixelSize: 20
        }

        Rectangle {
            id: splitter3

            color: base.colorSecondary
            height: 1
            anchors.top: inputPhone.bottom
            anchors.left: parent.left
            anchors.right: parent.right
        }

        NEOControls.TextField {
            id: inputWebsite

            anchors.top: splitter3.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 40

            placeholderText: "Enter Dealership Website:"
            font.pixelSize: 20
        }

        Rectangle {
            id: splitter4

            color: base.colorSecondary
            height: 1
            anchors.top: inputWebsite.bottom
            anchors.left: parent.left
            anchors.right: parent.right
        }

        NEOControls.Button {
            id: btnSave
            anchors.bottom: btnBack.top
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            text: "Save Information"

            onClicked: {
                if (inputName.text != "") {
                    storageModel.dealershipName = inputName.text
                }

                if (inputPhone.text != "") {
                    storageModel.dealershipPhone = inputPhone.text
                }

                if (inputWebsite.text != "") {
                    storageModel.dealershipWebsite = inputWebsite.text
                }

                base.hidePages()
                pageDealership.show()
            }
        }

        NEOControls.Button {
            id: btnBack
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            text: "Back"
            leftImg.source: "../Assets/arrow_left.png"

            onClicked: {
                goToPreviousPage()
            }
        }
    }
}
