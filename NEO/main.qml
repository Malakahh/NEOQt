import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import "Views" as Views
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

ApplicationWindow {
    id: base
    visible: true
    width: 720
    height: 1280
    title: qsTr("NEO")

    property string colorControlBackground: "#E6000000"
    property string colorPrimary: "#FF00A37D"
    property string colorSecondary: "#FF258267"

    function hidePages() {
        pageBT.visible = false
        pageConnecting.visible = false
        pageMain.visible = false
    }

    style: ApplicationWindowStyle {
        background: Rectangle {
            color: "#FFFFFF"
        }
    }

    Views.BluetoothPage {
        id: pageBT
        visible: false
    }

    Views.ConnectingPage {
        id: pageConnecting
        visible: false
    }

    Views.MainPage {
        id: pageMain
        visible: false
    }

    Views.PasswordPage {
        id: pagePassword
        visible: false
    }

    Views.ServicePage {
        id: pageService
    }


//    Views.BBluetooth {
//        id: viewBLE
//        anchors.fill: parent
//        visible: true
//    }

//    Views.BUserPage {
//        id: viewUser
//        anchors.fill: parent
//        visible: false
//    }

//    Views.BServicePage {
//        id: viewService
//        anchors.fill: parent
//        visible: false
//    }
}
