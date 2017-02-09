import QtQuick 2.0
import QtQuick.Controls 2.1
import "../NEOControls" as NEOControls

BasePage {
    Component.onCompleted: {
        bleController.setupBLE()
    }

    text: "Select NEO Charger"
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
                color: base.colorPrimary
            }

            background: Rectangle {
                anchors.fill: parent

                color: base.colorControlBackground
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

                color: base.colorControlBackground

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        bleController.connect(index)
                        base.hidePages()
                        pageConnecting.visible = true
                        dropdownPopup.close()
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
                    color: base.colorPrimary
                }
            }

            Rectangle {
                id: splitter

                anchors.top: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1

                color: base.colorPrimary
            }

            popup: Popup {
                id: dropdownPopup

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

                            visible: parent.size < 1.0

                            color: base.colorPrimary
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
            anchors.bottom: infoBtn.top

            fillMode: Image.PreserveAspectFit
            source: "../Assets/neo_charger.png"
        }

        NEOControls.Button {
            id: infoBtn

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter

            text: "i"
            pixelSize: 50

            width: 75
            height: 75
            radius: 90
        }
    }
}
