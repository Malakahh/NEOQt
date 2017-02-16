import QtQuick 2.0
import QtQuick.Controls 2.1
import "../NEOControls" as NEOControls

BasePage {
    text: "Select Log File"

    property int selectedIndex: -1
    property var selectedHeader
    property var returnTo
    property string file: ""

    Connections {
        target: fileExplorer
        onFilePicked: {
            if (fileExplorer.returnTo === pageSelectLog) {
                file = fileName
                pageProgress.fileName = "Log " + selectedIndex
                pageProgress.messageText = "Reading log file..."
                pageProgress.fileSize = selectedHeader.size * 2
                pageProgress.value = 0

                base.hidePages()
                pageProgress.show()

                chargerModel.updateLog(selectedIndex)
            }
        }
    }

    Connections {
        target: chargerModel

        onProgramSizeChanged: {
            chargerModel.updateLogSize()
        }

        onLogSizeChanged: {
            chargerModel.updateLogHeaders()
        }

        onLogByteRead: {
            if (fileExplorer.returnTo === pageSelectLog) {
                pageProgress.value = pageProgress.value + 1

                if (pageProgress.value == selectedHeader.size * 2) {
                    fileHelper.saveLog(file)
                    chargerModel.enterNormalMode()

                    base.hidePages()
                    returnTo.show()
                }
            }
        }
    }

    onVisibleChanged: {
        if (visible) {
            chargerModel.stopUpdateTimer()

            chargerModel.enterProgMode()
            chargerModel.updateProgramSize()
        }
    }

    contents: Item {
        anchors.fill: parent

        ListView {
            id: list

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: btnOk.top
            anchors.bottomMargin: 25

            focus: true
            clip: true
            model: chargerModel.logHeaders

            delegate: Rectangle {
                height: 75
                width: parent.width

                color: base.colorControlBackground

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        selectedIndex = index
                        selectedHeader = model.modelData
                    }
                }

                Text {
                    anchors.fill: parent
                    anchors.leftMargin: 30
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter

                    text: "Log " + index
                    color: base.colorPrimary

                    fontSizeMode: Text.Fit
                    minimumPixelSize: 10
                    font.pixelSize: 25
                }

                Text {
                    anchors.fill: parent
                    anchors.rightMargin: 30
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter

                    text: (model.modelData.size * 2) + "b"
                    color: base.colorPrimary

                    fontSizeMode: Text.Fit
                    minimumPixelSize: 10
                    font.pixelSize: 25
                }
            }

            ScrollIndicator.vertical: ScrollIndicator {
                contentItem: Rectangle {
                    implicitWidth: 10

                    visible: parent.size < 1.0

                    color: base.colorPrimary
                }
            }
        }

        Rectangle {
            id: splitter

            anchors.top: list.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1

            color: base.colorPrimary
        }

        NEOControls.Button {
            id: btnOk

            anchors.bottom: btnCancel.top
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            text: "OK"

            onClicked: {
                if (selectedIndex === -1) {
                    return
                }

                fileExplorer.writeMode = true
                fileExplorer.returnTo = pageSelectLog

                base.hidePages()
                fileExplorer.show()
            }
        }

        NEOControls.Button {
            id: btnCancel

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5

            leftImg.source: "../Assets/arrow_left.png"
            text: "Cancel"

            onClicked: {
                chargerModel.enterNormalMode()
                base.hidePages()
                returnTo.show()
            }
        }
    }
}
