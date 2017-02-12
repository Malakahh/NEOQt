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
    }

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
