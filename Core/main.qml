import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import LinphoneController 1.0
import QtMultimedia 5.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Linphone")

    TextArea {
        placeholderText: qsTr("Enter description")
    }

    Button {
        width: parent.width
        height: parent.height

        background: Rectangle{
            color: "lightskyblue"
            anchors.fill:parent

        }
        onClicked: LinphoneController.initThread();

    Button {
        id: b_call
        width: 200
        height: 70
        text: "Clique para ligar"
        anchors.centerIn: parent
            background: Rectangle
            {
                radius: 100
                color: "red"
                anchors.fill:parent
            }
            onClicked: { LinphoneController.linphoneCalling(); LinphoneController.screenLoadingWindow(); }

    }


    Dialog {
        id: call
        width: 320
        height: 240
        anchors.centerIn:parent


        contentItem: Rectangle {
            color: "grey"
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
                anchors.left:parent.left
                anchors.top:parent.top
                anchors.leftMargin: 70
                anchors.topMargin: 150

                background: Rectangle{
                    radius: 100
                    color: "lightgreen"
                    anchors.fill:parent

                }

                onClicked:
                {
                    LinphoneController.accept();
                    LinphoneController.callInitialization();
                }
            }
            Button{
                id: b_decline
                width: 70
                height: 70
                anchors.right:parent.right
                anchors.top:parent.top
                anchors.rightMargin: 70
                anchors.topMargin: 150
                background: Rectangle{
                    radius: 100
                    color: "red"
                    anchors.fill:parent
                }

                onClicked: LinphoneController.decline()
            }
        }
    }
    Dialog {
        id: call_init
        width: 640
        height: 480

        contentItem: Rectangle {
            color: "lightskyblue"
            anchors.fill: parent

            Text {
                anchors.centerIn: parent
                text: "Ligação em andamento"
                color: "navy"
            }

            Button{
                id: decline_call
                width: 70
                height: 70
                anchors.right:parent.right
                anchors.top:parent.top
                anchors.rightMargin: 350
                anchors.topMargin: 270

                anchors.bottomMargin:15

                background: Rectangle{
                    radius: 100
                    color: "red"
                    anchors.fill:parent
                }

                onClicked: LinphoneController.decline_call()
            }
            Button{
                id: mute_call
                width: 70
                height: 70
                anchors.left:parent.left
                anchors.top:parent.top
                anchors.leftMargin: 350
                anchors.topMargin: 270

                anchors.bottomMargin:15

                background: Rectangle{
                    radius: 100
                    color: "black"
                    anchors.fill:parent
                }

                onClicked: LinphoneController.video_on()
            }
        }
    }

    Dialog {

        id: loading_call
        width: 640
        height: 480


        contentItem: Rectangle {
            color: "lightskyblue"
            anchors.fill: parent

            Text {
                anchors.centerIn: parent
                text: "Carregando"
                color: "navy"

            }
        }
    }
 }



    Connections {
        target: LinphoneController

        function onOpenCall()
        {
            call.open()
        }
        function onWaitingCall()
        {
            console.log("Iniciou a Thread")
        }

        function onAcceptCall()
        {
            console.log("Call aceita");
            call.closed()
        }
        function onDeclineCall()
        {
            console.log("Call declined")

        }
        function onCallingOk()
        {
            console.log("Call iniciada")

        }
        function onWaitingActionInCall()
        {
            loading_call.open()
        }

        function onCallInProgress()
        {
            call_init.open()
        }
        function onCallAccepted(){

            loading_call.close()
            call_init.open()
        }
        function onDeclineInCall()
        {
            console.log("Ligação encerrada")
            call_init.close()
        }



    }
}


