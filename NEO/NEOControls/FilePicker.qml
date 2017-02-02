import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

Popup {
    id: fileBrowserBase

    modal: true

    width: 300
    height: 500

    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2

    property bool writeMode: false

    signal filePicked(var fileName)

    background: Rectangle {
        color: "red"
    }

    contentItem: Item {
        ListView {
            id: fbFileList

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            height: {
                if (fileBrowserBase.writeMode)
                    return parent.height - 70
                else
                    return parent.height
            }

            focus: true
            clip: true
            model: fileHelper.getFiles()

            delegate: MouseArea {
                height: 60
                width: parent.width

                onClicked: {
                    if (fileBrowserBase.writeMode)
                    {
                        filenameInput.text = model.modelData.fileName
                    }
                    else
                    {
                        fileBrowserBase.filePicked(model.modelData.fileName)
                        fileBrowserBase.close()
                    }
                }

                Control {
                    anchors.fill: parent

                    bottomPadding: 5

                    contentItem: Rectangle {
                        color: {
                            if (index % 2 == 0)
                            {
                                return "#A8FFCA"
                            }
                            else
                            {
                                return "#B7C9FF"
                            }
                        }

                        Text {
                            text: model.modelData.fileName

                            fontSizeMode: Text.Fit
                            minimumPixelSize: 10
                            font.pixelSize: 50
                        }
                    }
                }
            }
        }

        Item {
            enabled: fileBrowserBase.writeMode

            anchors.top: fbFileList.bottom
            anchors.topMargin: 5
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left

            TextField {
                id: filenameInput

                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.rightMargin: 5

                width: parent.width - 55

                wrapMode: TextInput.Wrap
                font.pixelSize: 35

                placeholderText: "Filename..."
            }

            Button {
                id: btnSave

                anchors.left: filenameInput.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                onClicked: {
                    if (filenameInput.text == "")
                    {
                        return
                    }

                    fileBrowserBase.filePicked(filenameInput.text)
                    fileBrowserBase.close()
                }

                Image {
                    anchors.fill: parent
                    source: "../Assets/floppy.png"
                }
            }
        }
    }
}
