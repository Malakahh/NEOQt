import QtQuick 2.0
import QtQuick.Controls 2.0

Flickable {
    id: basePage

    property alias contents: placeholder.children
    property alias header: placeholderHeader.children
    property alias text: placeholderHeader.text

    function show() {
        basePage.visible = true
        //basePage.enabled = true
    }

    function hide() {
        basePage.visible = false
        //basePage.enabled = false
    }

    ScrollBar.vertical: ScrollBar { }
    focus: true
    anchors.fill: parent

    Rectangle {
        id: topRect

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 70

        color: base.colorPrimary

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

        anchors.top: topRect.bottom
        anchors.bottom: bottomRect.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Image {
        anchors.bottom: bottomRect.top
        anchors.left: parent.left
        anchors.right: parent.right
        z: -100

        fillMode: Image.PreserveAspectFit
        source: "../Assets/wave.png"
    }

    Rectangle {
        id: bottomRect

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 35

        color: base.colorPrimary
    }
}
