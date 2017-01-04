import QtQuick 2.0

Item {
    id: test

    Image {
        id: powerchargeLogo
        source: "file"

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: base.MARGIN
    }
}
