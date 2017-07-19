import QtQuick 2.0
import QtQuick.Controls 2.1
import "../NEOControls" as NEOControls

BasePage {
    text: "Transferring"

    property string fileName: ""
    property string messageText: ""
    property alias fileSize: progressBar.to
    property alias value: progressBar.value
    property alias btnCancelVisible: btnCancel.visible
    property var onCancel

    function goToPreviousPage() {
        if (onCancel)
            onCancel();
    }

    onVisibleChanged: {
        if (visible) {
            base.backPressedCallback = goToPreviousPage
        }
    }

    contents: Item {
        anchors.fill: parent

        ProgressBar {
            id: progressBar

            from: 0

            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: 60

            background: Rectangle {
                radius: 15
                implicitWidth: parent.width
                implicitHeight: parent.height

                color: base.colorControlBackground
                border.color: base.colorPrimary
                border.width: 3
            }

            contentItem: Item {
                implicitWidth: parent.width
                implicitHeight: parent.height

                Rectangle {
                    radius: 15
                    width: progressBar.visualPosition * parent.width
                    height: parent.height

                    color: base.colorPrimary
                }
            }

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                fontSizeMode: Text.Fit
                minimumPixelSize: 10
                font.pixelSize: 25

                text: pageProgress.value + "/" + pageProgress.fileSize
                color: "#FFFFFFFF"
            }
        }

        NEOControls.DataRow {
            id: dataRowInfo

            anchors.top: progressBar.bottom
            anchors.topMargin: 30

            showTopSplitter: true
            showBottomSplitter: true
            splitterColor: base.colorSecondary
            textColor: base.colorSecondary

            textLeft: pageProgress.fileName
            textRight: pageProgress.fileSize
        }

        Text {
            id: waitText

            anchors.top: dataRowInfo.bottom
            anchors.topMargin: 15
            anchors.left: parent.left
            anchors.right: parent.right

            color: base.colorPrimary
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pixelSize: 25

            text: "Please Wait"
        }

        Text {
            anchors.top: waitText.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.right: parent.right

            color: base.colorPrimary
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pixelSize: 15

            text: pageProgress.messageText
        }

        NEOControls.Button {
            id: btnCancel

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5

            leftImg.source: "../Assets/arrow_left.png"
            text: "Cancel"

            visible: false

            onClicked: {
                goToPreviousPage()
            }
        }
    }
}
