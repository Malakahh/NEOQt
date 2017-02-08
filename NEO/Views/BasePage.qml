import QtQuick 2.0
import QtQuick.Controls 2.0

Flickable {
    property alias contents: placeholder.children
    property alias header: placeholderHeader

    ScrollBar.vertical: ScrollBar { }
    focus: true
    anchors.fill: parent

    Rectangle {
        id: top

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 70

        color: "#00A37D"

        Text {
            id: placeholderHeader
            anchors.fill: parent

            color: "#FFFFFF"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pixelSize: 25
        }
    }

    Item {
        id: placeholder

        anchors.top: top.bottom
        anchors.bottom: bottom.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Image {
        anchors.bottom: bottom.top
        anchors.left: parent.left
        anchors.right: parent.right
        z: -100

        fillMode: Image.PreserveAspectFit
        source: "../Assets/wave.png"
    }

    Rectangle {
        id: bottom

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 35

        color: "#00A37D"
    }
}
