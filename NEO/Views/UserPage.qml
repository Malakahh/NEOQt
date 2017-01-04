import QtQuick 2.0
import "../NEOControls" as NEOControls

Item {
    id: test

    Image {
        id: powerchargeLogo
        source: "file"

        anchors.left: parent.left
        anchors.leftMargin: base.MARGIN
        anchors.right: parent.right
        anchors.rightMargin: base.MARGIN
        anchors.top: parent.top
        anchors.topMargin: base.MARGIN
    }

    AnimatedSprite {
        id: batteryIcon
        source: "file"

        anchors.top: powerchargeLogo.top
        anchors.topMargin: base.MARGIN
        anchors.horizontalCenter: powerchargeLogo.horizontalCenter
    }

    Row {
        id: ledRow

        anchors.top: batteryIcon
        anchors.topMargin: base.MARGIN
        anchors.left: parent.left
        anchors.leftMargin: base.MARGIN
        anchors.right: parent.right
        anchors.rightMargin: base.MARGIN

        spacing: base.MARGIN

        Column {
            spacing: base.MARGIN

            Image {
                id: ledGreen
                source: "file"
            }

            Image {
                id: iconPower
                source: "file"
            }
        }

        Column {
            spacing: base.MARGIN

            Image {
                id: ledYellow
                source: "file"
            }

            Image {
                id: iconBattery
            }
        }

        Column {
            spacing: base.MARGIN

            Image {
                id: ledRed
                source: "file"
            }

            Image {
                id: iconError
                source: "file"
            }
        }

        Column {
            spacing: base.MARGIN

            Image {
                id: ledBlue
                source: "file"
            }

            Image {
                id: iconBtConnected
                source: "file"
            }
        }
    }

    NEOControls.InfoButton {
        anchors.top: ledRow
        anchors.topMargin: base.MARGIN
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
