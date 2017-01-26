import QtQuick 2.0
import QtQuick.Controls 2.0
import Qt.labs.platform 1.0
import "../NEOControls" as NEOControls

Flickable {
    ScrollBar.vertical: ScrollBar { }
    focus: true
    anchors.fill: parent

    height: parent.height
    contentHeight: userScrollContent.height

    Item {
        id: userScrollContent

        anchors.margins: base.margin
        anchors.fill: parent

        Image {
            id: powerchargeLogo
            source: "../Assets/Power.png"
            fillMode: Image.PreserveAspectFit

            anchors.left: parent.left
            anchors.leftMargin: base.margin
            anchors.right: parent.right
            anchors.rightMargin: base.margin
            anchors.top: parent.top
            //anchors.topMargin: base.margin

            MouseArea {
                anchors.fill: parent
                onPressedChanged: {
                    if (pressed) {
                        powerchargeLogoLongClickTimer.running = true
                    } else {
                        powerchargeLogoLongClickTimer.running = false
                    }
                }

                Timer {
                    id: powerchargeLogoLongClickTimer
                    interval: 3000
                    repeat: false
                    running: false
                    onTriggered: {
                        viewUser.visible = false
                        viewService.visible = true
                    }
                }
            }
        }

        AnimatedSprite {
            id: batteryIcon
            source: "../Assets/BatterySheet.png"
            frameCount: 1
            frameRate: 1

            width: powerchargeLogo.width
            height: powerchargeLogo.width / 2

            anchors.top: powerchargeLogo.bottom
            anchors.topMargin: base.margin
            anchors.horizontalCenter: powerchargeLogo.horizontalCenter
        }

        Row {
            id: ledRow

            anchors.top: batteryIcon.bottom
            anchors.topMargin: base.margin
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: base.margin

            Column {
                spacing: base.margin

                Image {
                    id: ledGreen
                    source: "../Assets/led_blue.png"
                    fillMode: Image.PreserveAspectFit
                    width: 32
                    height: width
                    x: width / 2
                }

                Image {
                    id: iconPower
                    source: "../Assets/icon_connectivity.png"
                    fillMode: Image.PreserveAspectFit
                    width: 64
                    height: width
                }
            }

            Column {
                spacing: base.margin

                Image {
                    id: ledYellow
                    source: "../Assets/led_blue.png"
                    fillMode: Image.PreserveAspectFit
                    width: 32
                    height: width
                    x: width / 2
                }

                Image {
                    id: iconBattery
                    source: "../Assets/icon_connectivity.png"
                    fillMode: Image.PreserveAspectFit
                    width: 64
                    height: width
                }
            }

            Column {
                spacing: base.margin

                Image {
                    id: ledRed
                    source: "../Assets/led_blue.png"
                    fillMode: Image.PreserveAspectFit
                    width: 32
                    height: width
                    x: width / 2
                }

                Image {
                    id: iconError
                    source: "../Assets/icon_connectivity.png"
                    fillMode: Image.PreserveAspectFit
                    width: 64
                    height: width
                }
            }

            Column {
                spacing: base.margin

                Image {
                    id: ledBlue
                    source: "../Assets/led_blue.png"
                    fillMode: Image.PreserveAspectFit
                    width: 32
                    height: width
                    x: width / 2
                }

                Image {
                    id: iconBtConnected
                    source: "../Assets/icon_connectivity.png"
                    fillMode: Image.PreserveAspectFit
                    width: 64
                    height: width
                }
            }
        }

        NEOControls.InfoButton {
            anchors.top: ledRow.bottom
            anchors.topMargin: base.margin
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: {
                //chargerModel.updateChargeVoltage()
                //chargerModel.fileDialogTest()
                folderDialog.open()

            }

            FileDialog {
                id: folderDialog
                folder: shortcuts.home
            }
        }
    }
}
