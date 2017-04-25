import QtQuick 2.0
import QtQuick.Controls 1.4

BasePage {
    Connections {
        target: bleController
        onConnectionEstablished: {
            base.hidePages()
            pageMain.show()
        }
    }

    text: "Connecting"
    contents: Item {
        anchors.fill: parent

        BusyIndicator {
            id: busyIndicatorConnecting

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 50

            width: 100
            height: 100

            running: true
        }

        Text {
            id: waitText

            anchors.top: busyIndicatorConnecting.bottom
            anchors.topMargin: 15
            anchors.left: parent.left
            anchors.right: parent.right

            color: base.colorPrimary
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pixelSize: 25

            text: "Please Wait"
        }

        Text {
            anchors.top: waitText.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.right: parent.right

            color: base.colorPrimary
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pixelSize: 15

            text: "Connecting to your NEO charger..."
        }
    }
}
