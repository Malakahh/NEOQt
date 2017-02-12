import QtQuick 2.0
import QtQuick.Controls 2.1
import "../NEOControls" as NEOControls

BasePage {    
    text: "Select File"

    property bool writeMode: false
    property string selectedFile: ""
    property var returnTo

    signal filePicked(var fileName)

    contents: Item {
        anchors.fill: parent

        ListView {
            id: list

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: {
                if (writeMode)
                    return fileInput.top
                else
                    return btnOk.top
            }

            anchors.bottomMargin:  {
                if (writeMode)
                    return 1
                else
                    return 25
            }

            focus: true
            clip: true
            model: fileHelper.getFiles()

            delegate: Rectangle {
                height: 75
                width: parent.width

                color: base.colorControlBackground

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        if (fileExplorer.writeMode) {
                            fileInput.text = model.modelData.fileName
                        }
                        else {
                            selectedFile = model.modelData.fileName
                        }
                    }
                }

                Text {
                    anchors.fill: parent
                    anchors.leftMargin: 30
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter

                    text: model.modelData.fileName
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

        NEOControls.TextField {
            id: fileInput

            visible: fileExplorer.writeMode

            anchors.bottom: btnOk.top
            anchors.bottomMargin: 25
            anchors.left: parent.left
            anchors.right: parent.right
            height: 75

            placeholderText: "Enter Filename:"
            font.pixelSize: 25
        }

        NEOControls.Button {
            id: btnOk

            anchors.bottom: btnCancel.top
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            text: "OK"

            onClicked: {
                if (selectedFile != "") {
                    fileExplorer.filePicked(selectedFile)
                    selectedFile = ""
                }
                else if (fileInput.text != "") {
                    fileExplorer.filePicked(fileInput.text)
                    fileInput.text = ""
                }
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
                selectedFile = ""
                fileInput.text = ""

                base.hidePages()
                returnTo.show()
            }
        }
    }
}