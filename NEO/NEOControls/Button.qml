import QtQuick 2.0
import QtQuick.Controls 2.1

Button {
    id: btn

    property int radius: 15
    property string leftImageSrc: ""
    property string rightImageSrc: ""

    implicitWidth: 250
    implicitHeight: 75

    contentItem: Item {
        anchors.fill: parent

        Image {
            id: imgLeft

            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter

            width: 64
            height: 64

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
            color: "#FF00A37D"

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pixelSize: 50
        }

        Image {
            id: imgRight

            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.verticalCenter: parent.verticalCenter

            width: 64
            height: 64

            source: btn.rightImageSrc
        }
    }

    background: Rectangle {
            anchors.fill: parent
            radius: parent.radius

            //color: "transparent"
            color: "#BF000000"
            border.color: "#00A37D"
            border.width: 3
        }
}
