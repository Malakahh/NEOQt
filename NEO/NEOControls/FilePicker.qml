import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQml.Models 2.2

Dialog {
    contentItem: Item {

        implicitWidth: 300
        implicitHeight: 500

        TreeView {
            anchors.fill: parent

            TableViewColumn {
                title: "Name"
                role: "fileName"
                width: parent.width
            }

            model: fbModel
        }
    }
}
