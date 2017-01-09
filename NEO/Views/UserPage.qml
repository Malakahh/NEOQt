import QtQuick 2.0
import "../NEOControls" as NEOControls

Item {
    id: test

    Image {
        id: powerchargeLogo
        source: "../Assets/Power.png"
        fillMode: Image.PreserveAspectFit

        anchors.left: parent.left
        anchors.leftMargin: base.margin
        anchors.right: parent.right
        anchors.rightMargin: base.margin
        anchors.top: parent.top
        anchors.topMargin: base.margin
    }

    AnimatedSprite {
        id: batteryIcon
        source: "../Assets/BatterySheet.png"
        frameCount: 1
        frameRate: 1

        width: 512
        height: 256

        anchors.top: powerchargeLogo.bottom
        anchors.topMargin: base.margin
        anchors.horizontalCenter: powerchargeLogo.horizontalCenter
    }

    Row {
        id: ledRow

        anchors.top: batteryIcon.bottom
        anchors.topMargin: base.margin
        anchors.left: parent.left
        anchors.leftMargin: base.margin
        anchors.right: parent.right
        anchors.rightMargin: base.margin

        spacing: base.margin

        Column {
            spacing: base.margin

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
            spacing: base.margin

            Image {
                id: ledYellow
                source: "file"
            }

            Image {
                id: iconBattery
                source: "file"
            }
        }

        Column {
            spacing: base.margin

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
            spacing: base.margin

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
        anchors.top: ledRow.bottom
        anchors.topMargin: base.margin
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
