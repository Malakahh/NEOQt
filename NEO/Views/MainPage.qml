import QtQuick 2.0
import QtQuick.Controls 2.1
import "../NEOControls" as NEOControls

BasePage {
    onVisibleChanged: {
        if (visible) {
            chargerModel.startUpdateTimer()
            firstDataPoll.start()
            ledGreen.start()
            ledYellow.start()
            ledRed.start()
            batteryIcon.start()
        }
    }

    Timer {
        id: firstDataPoll
        repeat: false
        onTriggered: {
            chargerModel.updateLEDStatus()
        }
    }

    header: Button {
        anchors.fill: parent

        onPressed: {
            powerchargeLogoLongClickTimer.start()
        }

        onReleased: {
            powerchargeLogoLongClickTimer.stop()
        }

        Timer {
            id: powerchargeLogoLongClickTimer
            interval: 3000
            repeat: false
            running: false
            onTriggered: {
                base.hidePages()
                pagePassword.show()
            }
        }

        background: Image {
            anchors.fill: parent
            source: "../Assets/logo.png"
            fillMode: Image.PreserveAspectFit
        }
    }

    contents: Item {
        anchors.fill: parent

        Text {
            color: base.colorPrimary

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            height: 20

            text: "Version 0.3.3b"
        }

        AnimatedSprite {
            id: batteryIcon
            source: "../Assets/battery.png"
            frameRate: 1000 / 750
            frameCount: {
                if (chargerModel.LEDYellow === 0 || chargerModel.LEDYellow === 1)
                    return 1
                else if (chargerModel.LEDYellow === 250)
                    return 4
                else if (chargerModel.LEDYellow === 500)
                    return 7
            }

            frameX: {
                if (chargerModel.LEDYellow === 1)
                    return 2496 //Last frame
                else if (chargerModel.LEDYellow === 250)
                    return 1248 //Frame with 3 bars
                else if (chargerModel.LEDYellow === 500 || chargerModel.LEDYellow === 0)
                    return 0
            }

            interpolate: false

            frameWidth: 416
            frameHeight: 200

            height: width * frameHeight / frameWidth

            anchors.top: parent.top
            anchors.topMargin: 75
            anchors.left: parent.left
            anchors.leftMargin: 75
            anchors.right: parent.right
            anchors.rightMargin: anchors.leftMargin

        }

        Row {
            id: ledRow

            anchors.top: batteryIcon.bottom
            anchors.topMargin: 40
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: anchors.leftMargin

            spacing: (ledRow.width - iconPower.width * 4) / 3

            Column {
                spacing: 20

                AnimatedSprite {
                    id: ledGreen

                    source: "../Assets/diode_green.png"
                    frameCount: {
                        if (chargerModel.LEDGreen === 0 || chargerModel.LEDGreen === 1)
                            return 1
                        else
                            return 2
                    }

                    frameX: {
                        if (chargerModel.LEDGreen === 0)
                            return frameWidth
                        else
                            return 0
                    }

                    frameRate: {
                        if (chargerModel.LEDGreen === 0 || chargerModel.LEDGreen === 1)
                            return 0
                        else
                            return 1000 / chargerModel.LEDGreen
                    }

                    frameWidth: 60
                    frameHeight: 60

                    interpolate: false

                    width: 32
                    height: 32

                    x: width / 2
                }

                Image {
                    id: iconPower
                    source: "../Assets/icon_sine.png"
                    fillMode: Image.PreserveAspectFit
                    width: 64
                    height: width
                }
            }

            Column {
                spacing: 20

                AnimatedSprite {
                    id: ledYellow

                    source: "../Assets/diode_yellow.png"
                    frameCount: {
                        if (chargerModel.LEDYellow === 0 || chargerModel.LEDYellow === 1)
                            return 1
                        else
                            return 2
                    }

                    frameX: {
                        if (chargerModel.LEDYellow === 0)
                            return frameWidth
                        else
                            return 0
                    }

                    frameRate: {
                        if (chargerModel.LEDYellow === 0 || chargerModel.LEDYellow === 1)
                            return 0
                        else
                            return 1000 / chargerModel.LEDYellow
                    }

                    interpolate: false

                    frameWidth: 60
                    frameHeight: 60

                    width: 32
                    height: 32

                    x: width / 2
                }

                Image {
                    id: iconBattery
                    source: "../Assets/icon_battery.png"
                    fillMode: Image.PreserveAspectFit
                    width: 64
                    height: width
                }
            }

            Column {
                spacing: 20

                AnimatedSprite {
                    id: ledRed

                    source: "../Assets/diode_red.png"
                    frameCount: {
                        if (chargerModel.LEDRed === 0 || chargerModel.LEDRed === 1)
                            return 1
                        else
                            return 2
                    }

                    frameX: {
                        if (chargerModel.LEDRed === 0)
                            return frameWidth
                        else
                            return 0
                    }

                    frameRate: {
                        if (chargerModel.LEDRed === 0 || chargerModel.LEDRed === 1)
                            return 0
                        else
                            return 1000 / chargerModel.LEDRed
                    }

                    frameWidth: 60
                    frameHeight: 60

                    interpolate: false

                    width: 32
                    height: 32

                    x: width / 2
                }

                Image {
                    id: iconError
                    source: "../Assets/icon_warning.png"
                    fillMode: Image.PreserveAspectFit
                    width: 64
                    height: width
                }
            }

            Column {
                spacing: 20

                AnimatedSprite {
                    id: ledBlue

                    source: "../Assets/diode_blue.png"
                    frameCount: 1
                    frameRate: 1

                    frameWidth: 60
                    frameHeight: 60

                    interpolate: false

                    width: 32
                    height: 32

                    x: width / 2
                }

                Image {
                    id: iconBtConnected
                    source: "../Assets/icon_bluetooth.png"
                    fillMode: Image.PreserveAspectFit
                    width: 64
                    height: width
                }
            }
        }

        NEOControls.Button {
            id: infoBtn

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter

            text: "i"
            pixelSize: 50

            width: 75
            height: 75
            radius: 90

            onClicked: {
                pageDealership.returnTo = pageMain
                base.hidePages()
                pageDealership.show()
            }
        }
    }
}
