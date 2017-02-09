import QtQuick 2.0
import "../NEOControls" as NEOControls

BasePage {
    onVisibleChanged: {
        if (visible)
        {
            chargerModel.startUpdateTimer()
        }
    }

    text: "Service Menu"

    contents: Item {
        id: container

        anchors.fill: parent

        property int maxTextSize: 20
        property int rowHeight: 40

        Rectangle {
            id: splitter1

            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1

            color: base.colorSecondary
        }

        Item {
            id: txtVoltage

            anchors.top: splitter1.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: anchors.leftMargin
            height: container.rowHeight

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter

                fontSizeMode: Text.Fit
                minimumPixelSize: 10
                font.pixelSize: container.maxTextSize

                text: "Voltage:"
                color: base.colorSecondary
            }

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter

                fontSizeMode: Text.Fit
                minimumPixelSize: 10
                font.pixelSize: container.maxTextSize

                text: {
                    return (chargerModel.chargeVoltage / 1000).toFixed(1) + "V"
                }

                color: base.colorSecondary
            }
        }

        Rectangle {
            id: splitter2

            anchors.top: txtVoltage.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1

            color: base.colorSecondary
        }

        Item {
            id: txtCurrent

            anchors.top: splitter2.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: anchors.leftMargin
            height: container.rowHeight

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter

                fontSizeMode: Text.Fit
                minimumPixelSize: 10
                font.pixelSize: container.maxTextSize

                text: "Current:"
                color: base.colorSecondary
            }

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter

                fontSizeMode: Text.Fit
                minimumPixelSize: 10
                font.pixelSize: container.maxTextSize

                text: {
                    return (chargerModel.chargeCurrent / 1000).toFixed(1) + "A"
                }

                color: base.colorSecondary
            }
        }

        Rectangle {
            id: splitter3

            anchors.top: txtCurrent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1

            color: base.colorSecondary
        }

        Item {
            id: txtProgStep

            anchors.top: splitter3.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: anchors.leftMargin
            height: container.rowHeight

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter

                fontSizeMode: Text.Fit
                minimumPixelSize: 10
                font.pixelSize: container.maxTextSize

                text: "Step:"
                color: base.colorSecondary
            }

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter

                fontSizeMode: Text.Fit
                minimumPixelSize: 10
                font.pixelSize: container.maxTextSize

                text: {
                    return chargerModel.chargeProgramStep
                }

                color: base.colorSecondary
            }
        }

        Rectangle {
            id: splitter4

            anchors.top: txtProgStep.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1

            color: base.colorSecondary
        }

        Item {
            id: txtAh

            anchors.top: splitter4.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: anchors.leftMargin
            height: container.rowHeight

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter

                fontSizeMode: Text.Fit
                minimumPixelSize: 10
                font.pixelSize: container.maxTextSize

                text: "Ah Previous Cycle:"
                color: base.colorSecondary
            }

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter

                fontSizeMode: Text.Fit
                minimumPixelSize: 10
                font.pixelSize: container.maxTextSize

                text: "Ah"

                color: base.colorSecondary
            }
        }

        Rectangle {
            id: splitter5

            anchors.top: txtAh.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1

            color: base.colorSecondary
        }

        Item {
            id: txtError

            anchors.top: splitter5.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: anchors.leftMargin
            height: container.rowHeight

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter

                fontSizeMode: Text.Fit
                minimumPixelSize: 10
                font.pixelSize: container.maxTextSize

                text: "Error Status:"
                color: base.colorSecondary
            }

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter

                fontSizeMode: Text.Fit
                minimumPixelSize: 10
                font.pixelSize: container.maxTextSize

                text: {
                    if (chargerModel.LEDRed === 1) //LED_ON
                        return "Misc error"
                    else if (chargerModel.LEDRed === 500) //LED_SLOW_BLINK
                        return "Reverse polarity"
                    else
                        return "No Error"
                }

                color: base.colorSecondary
            }
        }

        Rectangle {
            id: splitter6

            anchors.top: txtError.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1

            color: base.colorSecondary
        }

        Item {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            NEOControls.Button {
                id: btnLogCounters
                anchors.bottom: btnLog.top
                anchors.bottomMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter

                text: "Log Counters"
                rightImg.source: "../Assets/arrow_right.png"
            }

            NEOControls.Button {
                id: btnLog
                anchors.bottom: btnProgram.top
                anchors.bottomMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter

                text: "Read Log"
                rightImg.source: "../Assets/arrow_right.png"
            }

            NEOControls.Button {
                id: btnProgram
                anchors.bottom: btnBack.top
                anchors.bottomMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter

                text: "Program"
                rightImg.source: "../Assets/arrow_right.png"
            }

            NEOControls.Button {
                id: btnBack
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter

                text: "Back"
                leftImg.source: "../Assets/arrow_left.png"
            }
        }
    }
}
