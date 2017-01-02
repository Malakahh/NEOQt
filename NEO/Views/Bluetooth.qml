import QtQuick 2.0
import QtQuick.Controls 2.0
import "../NEOControls" as NEOControls
//import com.neo 1.0

Item {
    Component.onCompleted: bleController.setupBLE();

    NEOControls.InfoButton {
        id: btnInfoBLE
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 25
    }

    Text {
        id: txtBLEHeadline
        text: qsTr("Select NEO charger:")
        anchors.horizontalCenter: btnInfoBLE.horizontalCenter
        anchors.top: btnInfoBLE.bottom
        anchors.topMargin: 25
    }

    ListView {
        id: listViewBLE
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: txtBLEHeadline.bottom
        anchors.topMargin: 25
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
                }
            }
        }

    }
}
