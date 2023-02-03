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
        //anchors.centerIn: parent

        text: "value" + value
        background: Rectangle{
            color: "lightskyblue"
            anchors.fill:parent

        }
        onClicked: LinphoneController.initThread()

    }
    Button {
        id: b_call
        width: 70
        height: 70
        anchors.centerIn:parent
            background: Rectangle{
                radius: 100
                color: "red"
                anchors.fill:parent
            }
            onClicked: LinphoneController.linphoneCalling();


    }


    Dialog {
        id: call
        width: 320
        height: 240

        contentItem: Rectangle {
            color: "lightskyblue"
            anchors.fill: parent

            Text {
                text: "Deseja atender essa ligação?"
                color: "navy"
                anchors.centerIn: parent
            }
            Button{
                id: b_accept
                width: 70
                height: 70

                background: Rectangle{
                    radius: 100
                    color: "lightgreen"
                    anchors.fill:parent

                }
                onClicked: LinphoneController.accept()
            }
            Button{
                id: b_decline
                width: 70
                height: 70
                anchors.left: b_accept.right
                anchors.leftMargin: 100
                background: Rectangle{
                    radius: 100
                    color: "red"
                    anchors.fill:parent
                }

                onClicked: LinphoneController.decline()
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

        function onAcceptCall(){
            console.log("Call aceita");
        }
        function onDeclineCall(){
            console.log("Call declined")
        }
        function onCallingOk(){
            console.log("Call iniciada")
        }
    }
}
