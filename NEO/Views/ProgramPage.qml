import QtQuick 2.0
import "../NEOControls" as NEOControls

BasePage {
    text: "Charging Program"

    onVisibleChanged: {
        if (visible) {
            chargerModel.stopUpdateTimer()

            chargerModel.enterProgMode()
            chargerModel.updateProgramName()
        }
    }

    contents: Item {
        anchors.fill: parent

        NEOControls.DataRow {
            id: dataRowProgramName

            anchors.top: parent.top
            anchors.topMargin: 20

            showTopSplitter: true
            showBottomSplitter: true
            splitterColor: base.colorSecondary
            textColor: base.colorSecondary

            textCenter: chargerModel.programName
        }

        NEOControls.Button {
            id: btnWrite
            anchors.bottom: btnBack.top
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            text: "Write Program"

            onClicked: {
                console.log("Click!")
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
