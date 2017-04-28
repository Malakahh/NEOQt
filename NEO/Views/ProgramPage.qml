import QtQuick 2.0
import "../NEOControls" as NEOControls

BasePage {
    text: "Charging Program"

    Connections {
        target: fileExplorer
        onFilePicked: {
            if (fileExplorer.returnTo === pageProgram) {
                programParser.parse(fileName)

                pageProgress.fileName = fileName
                pageProgress.messageText = "Writing program..."
                pageProgress.fileSize = programParser.wordCount * 2
                pageProgress.value = 0
                pageProgress.btnCancelVisible = false
                pageProgress.onCancel = false

                base.hidePages()
                pageProgress.show()

                chargerModel.writeProgramName(programParser.programName)
                chargerModel.writeProgramSizeInWords(programParser.wordCount)
                chargerModel.writeProgram(programParser.programData)
            }
        }
    }

    Connections {
        target: chargerModel
        onProgramByteWritten: {
            if (fileExplorer.returnTo === pageProgram) {
                pageProgress.value = pageProgress.value + 1

                console.log("Program Write tick")

                if (pageProgress.value == programParser.wordCount * 2) {
                    base.hidePages()
                    pageProgram.show()
                }
            }
        }

        onProgramNameChanged: {
            waitText.visible = false
        }
    }

    onVisibleChanged: {
        if (visible) {
            chargerModel.stopUpdateTimer()

            waitText.visible = true

            chargerModel.enterProgMode()
            chargerModel.updateProgramName()

            base.backPressedCallback = goToPreviousPage
        }
    }

    function goToPreviousPage() {
        chargerModel.enterNormalMode()
        base.hidePages()
        pageService.show()
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

        Text {
            id: waitText

            anchors.top: dataRowProgramName.bottom
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.right: parent.right

            color: base.colorPrimary
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pixelSize: 25

            text: "Please Wait"
        }

        Text {
            visible: waitText.visible

            anchors.top: waitText.bottom
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

            text: "Reading program name..."
        }

        NEOControls.Button {
            id: btnWrite
            anchors.bottom: btnBack.top
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            text: "Write Program"

            onClicked: {
                fileExplorer.writeMode = false
                fileExplorer.returnTo = pageProgram

                base.hidePages()
                fileExplorer.show()
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
