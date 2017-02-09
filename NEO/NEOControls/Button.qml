import QtQuick 2.0
import QtQuick.Controls 2.1

Button {
    id: btn

    property int radius: 15
    property alias leftImg: imgLeft
    property alias rightImg: imgRight

    implicitWidth: 200
    implicitHeight: 60

    contentItem: Item {
        anchors.fill: parent

        Image {
            id: imgLeft

            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter

            width: 16
            height: 32

            source: btn.leftImageSrc
        }

        Text {
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            anchors.left: {
                if (btn.leftImageSrc == "")
                    return parent.left
                else
                    return imgLeft.right
            }

            anchors.right: {
                if (btn.rightImageSrc == "")
                    return parent.right
                else
                    return imgRight.left
            }

            text: btn.text
            color: base.colorPrimary

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pixelSize: 25
        }

        Image {
            id: imgRight

            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.verticalCenter: parent.verticalCenter

            width: 16
            height: 32

            source: btn.rightImageSrc
        }
    }

    background: Rectangle {
            anchors.fill: parent
            radius: parent.radius

            color: base.colorControlBackground
            border.color: base.colorPrimary
            border.width: 3
        }
}
