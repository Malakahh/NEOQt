import QtQuick 2.0
import QtQuick.Controls 2.0
import "../NEOControls" as NEOControls

Item {
    Component.onCompleted: bleController.setupBLE();

    NEOControls.InfoButton {
        id: btnInfo
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 25
    }

    Text {
        id: txtBLEHeadline
        text: qsTr("Select NEO charger:")
        anchors.horizontalCenter: btnInfo.horizontalCenter
        anchors.top: btnInfo.bottom
        anchors.topMargin: 25
    }

    ListView {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: txtBLEHeadline.bottom
        anchors.topMargin: 25
        anchors.bottom: parent.bottom
        model: bleController.devices

        delegate: Text {
            text: model.modelData.deviceName
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
