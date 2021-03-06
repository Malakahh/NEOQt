import QtQuick 2.0
import "../NEOControls" as NEOControls

BasePage {
    id: dealership

    text: "Dealership Information"

    property var returnTo

    function goToPreviousPage() {
        base.hidePages()
        returnTo.show()
    }

    onVisibleChanged: {
        if (visible) {
            base.backPressedCallback = goToPreviousPage
        }
    }

    contents: Item {
        anchors.fill: parent

        NEOControls.DataRow {
            id: dataRowName

            anchors.top: parent.top
            anchors.topMargin: 25

            showTopSplitter: true
            splitterColor: base.colorSecondary
            textColor: base.colorSecondary

            textLeft: storageModel.dealershipName
        }

        NEOControls.DataRow {
            id: dataRowPhone

            anchors.top: dataRowName.bottom
            anchors.topMargin: -1

            showTopSplitter: true
            splitterColor: base.colorSecondary
            textColor: base.colorSecondary

            textLeft: storageModel.dealershipPhone
        }

        NEOControls.DataRow {
            id: dataRowWebsite

            anchors.top: dataRowPhone.bottom
            anchors.topMargin: -1

            showTopSplitter: true
            showBottomSplitter: true
            splitterColor: base.colorSecondary
            textColor: base.colorSecondary

            textLeft: storageModel.dealershipWebsite
        }

        NEOControls.Button {
            id: btnEdit
            anchors.bottom: btnBack.top
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            text: "Edit Information"

            onClicked: {
                base.hidePages()
                pageDealershipEdit.show()
            }
        }

        NEOControls.Button {
            id: btnBack
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            text: "Back"
            leftImg.source: "../Assets/arrow_left.png"

            onClicked: {
                goToPreviousPage()
            }
        }
    }
}
