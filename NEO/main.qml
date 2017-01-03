import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import "Views" as Views

ApplicationWindow {
    visible: true
    width: 720
    height: 1280
    title: qsTr("NEO")

    Views.Bluetooth {
        anchors.fill: parent
    }

}
