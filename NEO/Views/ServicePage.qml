import QtQuick 2.0
import QtQuick.Controls 2.0

Flickable {
    ScrollBar.vertical: ScrollBar { }
    focus: true
    anchors.fill: parent

    height: parent.height
    contentHeight: serviceScrollContent.height

    Item {
        id: serviceScrollContent

        anchors.margins: base.margin
        anchors.fill: parent

        Text {
            id: servicePageHeadline

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top

            text: qsTr("Service Menu")
            font.bold: true
            font.pointSize: 32
        }

        Row {
            id: onlineMetrics

            anchors.top: servicePageHeadline.bottom
            anchors.topMargin: base.margin
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: base.margin

            Column {
                spacing: base.margin

                Text {
                    text: qsTr("Voltage:")
                    font.pointSize: 20

                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    text: qsTr("30.6V")
                    font.pointSize: 28

                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Column {
                spacing: base.margin

                Text {
                    text: qsTr("Current:")
                    font.pointSize: 20

                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    text: qsTr("0.0A")
                    font.pointSize: 28

                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Column {
                spacing: base.margin

                Text {
                    text: qsTr("Step:")
                    font.pointSize: 20

                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    text: qsTr("3")
                    font.pointSize: 28

                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        Column {
            id: ahPreviousCycle

            anchors.top: onlineMetrics.bottom
            anchors.topMargin: base.margin
            anchors.horizontalCenter: onlineMetrics.horizontalCenter

            spacing: base.margin

            Text {
                text: qsTr("Ah Previous Cycle:")
                font.pointSize: 20

                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: qsTr("37 Ah")
                font.pointSize: 28

                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Column {
            id: errorStatus

            anchors.top: ahPreviousCycle.bottom
            anchors.topMargin: base.margin
            anchors.horizontalCenter: ahPreviousCycle.horizontalCenter

            spacing: base.margin

            Text {
                text: qsTr("Error status")
                font.pointSize: 20

                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: qsTr("No errors")
                font.pointSize: 28

                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Row {
            spacing: 5

            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                width: 100
                height: 100
                text: qsTr("Log\nCounters")
            }

            Button {
                width: 100
                height: 100
                text: qsTr("Read Log")
            }

            Button {
                width: 100
                height: 100
                text: qsTr("Program")
            }
        }
    }
}
