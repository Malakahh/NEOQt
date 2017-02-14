import QtQuick 2.0
import "../NEOControls" as NEOControls

BasePage {
    onVisibleChanged: {
        if (visible) {
            chargerModel.startUpdateTimer()
        }
    }

    text: "Service Menu"

    contents: Item {
        id: container

        anchors.fill: parent

        NEOControls.DataRow {
            id: dataRowVoltage

            anchors.top: parent.top
            anchors.topMargin: 20

            showTopSplitter: true
            splitterColor: base.colorSecondary
            textColor: base.colorSecondary

            textLeft: "Voltage:"
            textRight: {
                return (chargerModel.chargeVoltage / 1000).toFixed(1) + "V"
            }
        }

        NEOControls.DataRow {
            id: dataRowCurrent

            anchors.top: dataRowVoltage.bottom
            anchors.topMargin: -1

            showTopSplitter: true
            splitterColor: base.colorSecondary
            textColor: base.colorSecondary

            textLeft: "Current:"
            textRight: {
                return (chargerModel.chargeCurrent / 1000).toFixed(1) + "A"
            }
        }

        NEOControls.DataRow {
            id: dataRowProgStep

            anchors.top: dataRowCurrent.bottom
            anchors.topMargin: -1

            showTopSplitter: true
            splitterColor: base.colorSecondary
            textColor: base.colorSecondary

            textLeft: "Step:"
            textRight: {
                return chargerModel.chargeProgramStep
            }
        }

        NEOControls.DataRow {
            id: dataRowAh

            anchors.top: dataRowProgStep.bottom
            anchors.topMargin: -1

            showTopSplitter: true
            splitterColor: base.colorSecondary
            textColor: base.colorSecondary

            textLeft: "Ah Previous Cycle:"
            textRight: storageModel.AhPrev + "Ah"
        }

        NEOControls.DataRow {
            id: dataRowError

            anchors.top: dataRowAh.bottom
            anchors.topMargin: -1

            showTopSplitter: true
            showBottomSplitter: true
            splitterColor: base.colorSecondary
            textColor: base.colorSecondary

            textLeft: "Error Status:"
            textRight: {
                if (chargerModel.LEDRed === 1) //LED_ON
                    return "Misc error"
                else if (chargerModel.LEDRed === 500) //LED_SLOW_BLINK
                    return "Reverse polarity"
                else
                    return "No Error"
            }
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

                onClicked: {
                    base.hidePages()
                    pageLogCounters.show()
                }
            }

            NEOControls.Button {
                id: btnLog
                anchors.bottom: btnProgram.top
                anchors.bottomMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter

                text: "Read Log"
                rightImg.source: "../Assets/arrow_right.png"

                onClicked: {
                    pageSelectLog.returnTo = pageService
                    base.hidePages()
                    pageSelectLog.show()
                }
            }

            NEOControls.Button {
                id: btnProgram
                anchors.bottom: btnBack.top
                anchors.bottomMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter

                text: "Program"
                rightImg.source: "../Assets/arrow_right.png"

                onClicked: {
                    base.hidePages()
                    pageProgram.show()
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
                    base.hidePages()
                    pageMain.show()
                }
            }
        }
    }
}
