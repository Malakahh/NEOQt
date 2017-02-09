import QtQuick 2.0

Item {
    property string splitterColor: "FF000000"
    property string textColor: "FF000000"
    property string textLeft: ""
    property string textRight: ""
    property int textHMargin: 20
    property int textMaxSize: 20
    property int textMinSize: 10
    property bool showTopSplitter: false
    property bool showBottomSplitter: false

    anchors.left: parent.left
    anchors.right: parent.right
    height: 42

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: l.top
        height: 1

        color: parent.splitterColor
        visible: parent.showTopSplitter
    }

    Text {
        id: l

        anchors.fill: parent
        anchors.topMargin: 1
        anchors.bottomMargin: 1
        anchors.leftMargin: parent.textHMargin
        anchors.rightMargin: parent.textHMargin

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        fontSizeMode: Text.Fit
        minimumPixelSize: parent.textMinSize
        font.pixelSize: parent.textMaxSize

        text: parent.textLeft
        color: parent.textColor
    }

    Text {
        id: r

        anchors.fill: parent
        anchors.topMargin: 1
        anchors.bottomMargin: 1
        anchors.leftMargin: parent.textHMargin
        anchors.rightMargin: parent.textHMargin

        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        fontSizeMode: Text.Fit
        minimumPixelSize: parent.textMinSize
        font.pixelSize: parent.textMaxSize

        text: parent.textRight
        color: parent.textColor
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: l.bottom
        height: 1

        color: parent.splitterColor
        visible: parent.showBottomSplitter
    }
}
