import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import "Views" as Views

ApplicationWindow {
    id: base
    visible: true
    width: 720
    height: 1280
    title: qsTr("NEO")

    property var margin: 25

    Views.Bluetooth {
        id: viewBLE
        anchors.fill: parent
        visible: true
    }

    Views.UserPage {
        id: viewUser
        anchors.fill: parent
        visible: false
    }
}
