import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 7200
    height: 12800
    title: qsTr("Hello World")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            Label {
                id: lbl
                text: qsTr("First page")
                anchors.centerIn: parent
            }

            Button {
                id: testBtn
                text: "testBtn"
                height: 100
                anchors.top: lbl.bottom
                anchors.horizontalCenter: lbl.horizontalCenter
                onClicked: {
                    console.log("Button pressed");
                    btController.setupBluetooth();
                }
            }
        }

        Page {
            Label {
                text: "Third page"
                anchors.centerIn: parent
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Bluetooth")
        }
        TabButton {
            text: qsTr("Second")
        }
        TabButton {
            text: "Third"
        }
    }
}
