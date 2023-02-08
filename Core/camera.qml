import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtMultimedia 5.12
import "qrc:/CameraView.qml"
import LinphoneController 1.0

Item {
    id: cameraLinphone
    visible: isRunning

    //! Linphone camera is running
    readonly property bool running: cameraViewer.ready && LinphoneController.i


    CameraView {
        id: cameraViewer
        anchors.fill: parent
        enabled: running

        PLabel {
            id: counterLabel
            visible: false
            anchors.centerIn: parent
            property int counter: internal.counter
            bold: false
            size: 120
            text: counter
            color: internal.plabelColors
            FadeBehavior on text {}

            Timer {
                id: enrollCounter
                interval: 1000
                running: false
                repeat: true
                onTriggered: {
                    if (counterLabel.counter == 0) {
                        running = false
                        counterLabel.visible = false
                        counterLabel.counter = internal.counter
                        enrollEnable() // enroll starts
                    } else
                        --counterLabel.counter
                }
            }
        }

        PLabel {
            id: messageLabel
            visible: false
            anchors.centerIn: parent
            color: internal.plabelColors
            text: pageJson['faceMessageSmall'] // "Aproxime seu rosto ..."
            size: 28
            padding: 4
            opacity: 0.8
            background: Rectangle {
                color: "#80000000"
            }
        }
    }
}
