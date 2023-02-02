import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import LinphoneController 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Button {
        property int value: 0
        width: parent.width/2
        height: parent.height/2
        anchors.centerIn: parent

        text: "value" + value
        background: Rectangle{
            color: "red"
            anchors.fill:parent

        }
        onClicked: LinphoneController.initThread()
    }


    Dialog {
        id: call
        width: 320
        height: 240

        contentItem: Rectangle {
            color: "lightskyblue"
            anchors.fill: parent
            Text {
                text: "Ligação"
                color: "navy"
                anchors.centerIn: parent
            }
        }
    }

    Connections {
        target: LinphoneController

        function onOpenCall() {
            call.open()
        }

        function onOperate() {
            console.log("Iniciou a Thread")
        }
    }
}
