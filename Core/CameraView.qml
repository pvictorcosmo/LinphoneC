import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtMultimedia 5.12

import SmartfaceController 1.0
import br.com.visica.sfaceapp 1.0
import LinphoneController 1.0

Item {
    id: page

    // settings properties
    property bool tracking: false
    property bool liveness: false
    property bool frameBorder: false
    property int cameraIndex: -1
    property int elapsed: 0
    property real threshold: 0.4
    property int totalUsers: Smartface.totalUsers
    property int maxUsers: Smartface.maxUsers
    property bool showMaxUsers: false

    // control properties
    property alias camera: camera
    property alias video: videooutput
    property alias filters: videooutput.filters
    property alias recognizerManager: recognizerManager
    property alias personShow: recognizerManager.personShow

    // read only properties
    readonly property color labelColor: "#BDBDBD"
    readonly property bool ready: camera.cameraStatus === Camera.ActiveStatus

    function start() {
        if (SmartfaceLicense.hasLicense) {
            camera.start()
        }
    }

    function stop() {
        camera.stop()
    }

    function changeCamera() {
        if (cameraIndex < 0) {
            for (var i = 0; i < QtMultimedia.availableCameras.length; i++) {
                if (camera.deviceId === QtMultimedia.availableCameras[i].deviceId) {
                    cameraIndex = i
                    break
                }
            }
        }

        if (QtMultimedia.availableCameras.length > 0) {
            if (cameraIndex < (QtMultimedia.availableCameras.length - 1))
                cameraIndex += 1
            else
                cameraIndex = 0
            camera.deviceId = QtMultimedia.availableCameras[cameraIndex].deviceId
        }
    }

    function frameRateSelect(frameRate) {
        var bestFrame = 30
        var frameRateList = camera.supportedViewfinderFrameRateRanges("640x480")

        for (var i = 0; i < frameRateList.length; i++) {
            var currFrame = frameRateList[i].maximumFrameRate
            if (frameRate <= currFrame) {
                bestFrame = currFrame
                break
            } else {
                bestFrame = currFrame
            }
        }

        return bestFrame
    }

    Camera {
        id: camera
        position: Camera.FrontFace // for mobile
        captureMode: Camera.CaptureViewfinder
        viewfinder.resolution: "640x480"
        focus {
            focusMode: Camera.FocusMacro
            focusPointMode: Camera.FocusPointCustom
            //            focusMode: CameraFocus.FocusContinuous
            //            focusPointMode: CameraFocus.FocusPointAuto
            //customFocusPoint: Qt.point(0.2,
            //                           0.2) // Focus relative to top-left corner
        }
    }

    VideoOutput {
        id: videooutput
        anchors.fill: parent
        source: camera
        autoOrientation: true
        focus: visible // to receive focus and capture key events when visible

        fillMode: VideoOutput.PreserveAspectCrop

        MouseArea {
            anchors.fill: parent

            onClicked: {
                camera.focus.customFocusPoint = Qt.point(mouse.x / width,
                                                         mouse.y / height)
                camera.focus.focusMode = Camera.FocusMacro
                camera.focus.focusPointMode = Camera.FocusPointCustom
            }
        }
    }


    Row {
        z: 1
        visible: (elapsed)

        anchors {
            top: parent.top
            left: parent.left
            margins: 4
        }

        spacing: 4

        PLabel {
            size: 12
            text: "T: "
            color: "yellow"
        }

        PLabel {
            size: 12
            text: (elapsed / 1000) + "s"
            color: "yellow"
        }
    }

    Column {
        id: column1
        z: 1

        anchors {
            top: parent.top
            right: parent.right
            margins: 4
        }

        Row {
            spacing: 4
            visible: showMaxUsers

            PLabel {
                size: 14
                color: labelColor
                text: page.totalUsers
            }

            PLabel {
                size: 14
                color: labelColor
                text: "of"
            }

            PLabel {
                size: 14
                color: labelColor
                text: page.maxUsers
            }
        }

        RoundButton {
            id: switchCamera
            visible: false // (QtMultimedia.availableCameras.length > 1)
            Material.theme: Material.Dark
            anchors.right: parent.right
            width: 64
            height: 64
            text: "\ue41e"
            font.family: "Material Icons"
            font.weight: Font.DemiBold
            font.pointSize: width * 0.2

            onClicked: {
                changeCamera()
            }
        }
    }


    /**
     * @ATTENTION
     * Quando estamos com as duas câmeras(Color, IR) instaladas no equipamento, precisamos
     * inicializá-las quando sobe a GUI(QML), para que quando ocorrer a troca entre elas
     * durante o processo 'liveness' não dê problemas de não recebermos os frames da IR.
     * Acreditamos que isso esteja ocorrendo por a câmera color estar na posição /dev/video1
     */
    Timer {
        id: camerasInitializesTimer
        interval: 1000
        running: false
        repeat: false
        onTriggered: changeCamera()
    }

    Component.onCompleted: {
        // force camera initializer
        camerasInitializesTimer.running = true
    }
}
