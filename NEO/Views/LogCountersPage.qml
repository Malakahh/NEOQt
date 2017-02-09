import QtQuick 2.0
import "../NEOControls" as NEOControls

BasePage {
    text: "Log Counters"

    onVisibleChanged: {
        if (visible) {
            chargerModel.stopUpdateTimer()

            chargerModel.enterProgMode()
            chargerModel.updateLogCounterCharges()
            chargerModel.updateLogCounterErrors()
            chargerModel.updateLogCounterDepthDischarges()
        }
    }

    contents: Item {
        anchors.fill: parent

        NEOControls.DataRow {
            id: dataRowCharges

            anchors.top: parent.top
            anchors.topMargin: 20

            showTopSplitter: true
            splitterColor: base.colorSecondary
            textColor: base.colorSecondary

            textLeft: "Charges:"
            textRight: chargerModel.logCounterCharges
        }

        NEOControls.DataRow {
            id: dataRowErrors

            anchors.top: dataRowCharges.bottom
            anchors.topMargin: -1

            showTopSplitter: true
            splitterColor: base.colorSecondary
            textColor: base.colorSecondary

            textLeft: "Errors:"
            textRight: chargerModel.logCounterErrors
        }

        NEOControls.DataRow {
            id: dataRowDepthDischarges

            anchors.top: dataRowErrors.bottom
            anchors.topMargin: -1

            showTopSplitter: true
            showBottomSplitter: true
            splitterColor: base.colorSecondary
            textColor: base.colorSecondary

            textLeft: "Depth Discharges:"
            textRight: chargerModel.logCounterDepthDischarges
        }

        NEOControls.Button {
            id: btnReset
            anchors.bottom: btnBack.top
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            text: "Reset Counters"

            onClicked: {
                chargerModel.clearLogCounters()
                chargerModel.updateLogCounterCharges()
                chargerModel.updateLogCounterErrors()
                chargerModel.updateLogCounterDepthDischarges()
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
                chargerModel.enterNormalMode()
                base.hidePages()
                pageService.show()
            }
        }
    }
}
