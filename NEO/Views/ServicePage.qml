import QtQuick 2.0
import "../NEOControls" as NEOControls

BasePage {
    text: "Service Menu"

    contents: Item {
        anchors.fill: parent

        Rectangle {
            id: splitter1

            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1

            color: base.colorSecondary
        }

        Row {
            id: txtVoltage

            anchors.top: splitter1.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: anchors.leftMargin
            height: 40

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft

                text: "Voltage:"
                color: base.colorSecondary
            }

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight

                text: {
                    return (chargerModel.chargeVoltage / 1000).toPrecision(2) + "V"
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

        Row {
            id: txtCurrent

            anchors.top: splitter2.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: anchors.leftMargin
            height: 40

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft

                text: "Current:"
                color: base.colorSecondary
            }

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight

                text: {
                    return (chargerModel.chargeCurrent / 1000).toPrecision(2) + "A"
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

        Row {
            id: txtProgStep

            anchors.top: splitter3.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: anchors.leftMargin
            height: 40

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft

                text: "Step:"
                color: base.colorSecondary
            }

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight

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

        Row {
            id: txtAh

            anchors.top: splitter4.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: anchors.leftMargin
            height: 40

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft

                text: "Ah Previous Cycle:"
                color: base.colorSecondary
            }

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight

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

        Row {
            id: txtError

            anchors.top: splitter5.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: anchors.leftMargin
            height: 40

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignLeft

                text: "Error Status:"
                color: base.colorSecondary
            }

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight

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
