import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "../NEOControls" as NEOControls

Item {
    Component.onCompleted: {
        bleController.setupBLE()
    }

    Connections {
        target: bleController
        onConnectionEstablished: {
            viewBLE.visible = false;
            popupBLEConnecting.close()
            viewUser.visible = true;
        }
    }

    NEOControls.InfoButton {
        id: btnInfoBLE
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: base.margin

        onClicked: {
            console.log(fbModel.getData())
            diag.open()
        }

        NEOControls.FilePicker {
            id: diag
        }
    }

    Text {
        id: txtBLEHeadline
        text: qsTr("Select NEO charger:")
        anchors.horizontalCenter: btnInfoBLE.horizontalCenter
        anchors.top: btnInfoBLE.bottom
        anchors.topMargin: base.margin
    }

    ListView {
        id: listViewBLE
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: txtBLEHeadline.bottom
        anchors.topMargin: base.margin
        anchors.bottom: parent.bottom
        model: bleController.devices

        delegate: Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 50
            color: "palegreen"

            Text {
                text: model.modelData.deviceName
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    bleController.connect(index)
                    popupBLEConnecting.open()
                }
            }
        }
    }

    Popup {
        id: popupBLEConnecting
        modal: true
        focus: true
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2

        background: Rectangle {
        }

        contentItem: RowLayout {
            anchors.fill: parent

            BusyIndicator {
                id: busyIndicatorConnecting
                running: image.status === Image.Loading
            }

            Text {
                text: qsTr("Connecting...")
            }
        }
    }
}
