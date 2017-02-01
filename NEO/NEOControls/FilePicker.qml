import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

Popup {
    modal: true


    width: 200
    height: 200

    x: base.width / 2 - width / 2
    y: base.height / 2 - height / 2

    background: Rectangle {
        color: "white"
    }



    ListView {
        anchors.fill: parent
        focus: true

        model: fbModel.getData()

        delegate: Rectangle {

            height: 25
            width: 100

            Text {
                text: model.modelData.fileName + "content"
            }
        }


    }
}
