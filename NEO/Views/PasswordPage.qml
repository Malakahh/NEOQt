import QtQuick 2.7
import QtQuick.Controls 2.1
import "../NEOControls" as NEOControls

BasePage {
    text: "Authorization Required"

    contents: Item {
        anchors.fill: parent

        Rectangle {
            color: base.colorPrimary
            height: 1
            anchors.bottom: pwInput.top
            anchors.left: parent.left
            anchors.right: parent.right
        }

        NEOControls.TextField {
            id: pwInput

            anchors.top: parent.top
            anchors.topMargin: 25
            anchors.left: parent.left
            anchors.right: parent.right
            height: 75

            placeholderText: "Enter Service Menu Password:"
            font.pixelSize: 25

            echoMode: TextInput.Password
        }

        Rectangle {
            color: base.colorPrimary
            height: 1
            anchors.top: pwInput.bottom
            anchors.left: parent.left
            anchors.right: parent.right
        }

        NEOControls.Button {
            anchors.bottom: btnCancel.top
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            text: "OK"

            onClicked: {
                if (pwInput.text == "1234")
                {
                    base.hidePages()
                }
            }
        }

        NEOControls.Button {
            id: btnCancel

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5

            leftImg.source: "../Assets/arrow_left.png"
            text: "Cancel"
        }
    }
}
