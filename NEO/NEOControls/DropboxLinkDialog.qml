import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.2

Dialog {
    title: "Link with Dropbox"

    contentItem: Rectangle {
        color: "#FFFFFF"
        implicitWidth: 300
        implicitHeight: 200

        Text {
            id: txtLinkDropbox

            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            height: 60
            width: 300

            text: "Press Link Dropbox below to allow the app access to dropbox. Copy the resulting URL to the text field below."
            wrapMode: Text.Wrap
        }

        Button {
            id: btnLinkDropbox

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: txtLinkDropbox.bottom
            height: 60

            text: "Link Dropbox"
        }

        TextField {
            id: txtFieldLink

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: btnLinkDropbox.bottom
            height: 60

            placeholderText: "Dropbox access link here"
        }
    }
}
