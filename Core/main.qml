import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
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
        onClicked: value++
    }
}
