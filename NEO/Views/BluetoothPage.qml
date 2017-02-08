import QtQuick 2.0
import QtQuick.Controls 2.1
import "../NEOControls" as NEOControls

BasePage {
    Connections {
        target: bleController
        onConnectionEstablished: {
            base.hidePages()
        }
    }

    Component.onCompleted: {
        bleController.setupBLE()
    }

    header.text: "Select NEO Charger"
    contents: Item {
        id: content

        anchors.fill: parent

        ComboBox {
            id: selectDevice

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 75

            model: bleController.devices

            contentItem: Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                fontSizeMode: Text.Fit
                minimumPixelSize: 10
                font.pixelSize: 25

                text: "Tab to select"
                color: "#00A37D"
            }

            background: Rectangle {
                anchors.fill: parent

                color: "#E6000000"
            }

            indicator: Image {
                id: indicator

                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 16

                width: 32
                height: 16
                source: "../Assets/arrow_down.png"
            }

            delegate: Rectangle {
                parent: listview
                anchors.left: parent.left
                anchors.right: parent.right

                height: 75

                color: "#E6000000"

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        bleController.connect(index)
                    }
                }

                Text {
                    anchors.fill: parent
                    anchors.leftMargin: 30
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter

                    fontSizeMode: Text.Fit
                    minimumPixelSize: 10
                    font.pixelSize: 25

                    text: model.modelData.deviceName
                    color: "#00A37D"
                }
            }

            Rectangle {
                id: splitter

                anchors.top: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1

                color: "#00A37D"
            }

            popup: Popup {
                y: selectDevice.height + splitter.height
                width: selectDevice.width
                implicitHeight: content.height - infoBtn.height - infoBtn.anchors.bottomMargin * 2 - parent.height - splitter.height

                margins: 0
                padding: 0

                contentItem: ListView {
                    id: listview
                    clip: true
                    implicitHeight: parent.implicitHeight
                    model: selectDevice.popup.visible ? selectDevice.delegateModel : null
                    currentIndex: selectDevice.highlightedIndex

                    ScrollIndicator.vertical: ScrollIndicator {
                        contentItem: Rectangle {
                            implicitWidth: 10

                            color: "#00A37D"
                        }
                    }
                }

                background: Rectangle
                {
                    color: "transparent"
                    border.width: 0
                }
            }
        }

        Image {
            anchors.top: selectDevice.bottom
            anchors.horizontalCenter: selectDevice.horizontalCenter

            width: 250
            height: 375

            source: "../Assets/neo_charger.png"
        }

        NEOControls.Button {
            id: infoBtn

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter

            text: "i"
            font.pixelSize: 50

            width: 75
            height: 75
            radius: 90
        }
    }
}
