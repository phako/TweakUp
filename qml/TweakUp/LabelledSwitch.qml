// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    property alias checked: swInternalSwitch.checked
    property alias text: lblInternalLabel.text

    height: swInternalSwitch.height + 10

    Label {
        elide: Text.ElideRight
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: swInternalSwitch.horizontalCenter
        id: lblInternalLabel
        font.pixelSize: 26
        font.bold: true
        color: enabled ? "white" : "dark grey"
    }

    Switch {
        id: swInternalSwitch
        anchors.rightMargin: 10
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
    }
}
