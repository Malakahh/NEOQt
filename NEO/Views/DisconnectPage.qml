import QtQuick 2.0

BasePage {
    text: "Connection lost"
    contents: Item {
        anchors.fill: parent

        Text {
            id: connectionLostText

            anchors.top: parent.top
            anchors.topMargin: 200
            anchors.left: parent.left
            anchors.right: parent.right

            color: base.colorPrimary
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pixelSize: 25

            text: "Connection to charger lost"
        }

        Text {
            anchors.top: connectionLostText.bottom
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

            text: "Please restart the charger and/or app"
        }
    }
}
