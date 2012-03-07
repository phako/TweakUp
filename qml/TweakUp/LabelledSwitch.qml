// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    property alias checked: swInternalSwitch.checked
    property alias text: lblInternalLabel.text
    property bool indent: false

    height: Math.max(swInternalSwitch.height, lblInternalLabel.height)
    onWidthChanged: lblInternalLabel.width = width - swInternalSwitch.width - lblInternalLabel.anchors.leftMargin - 10

    Label {
        wrapMode: Text.WordWrap
        anchors.left: parent.left
        anchors.leftMargin: indent ? 40 : 10;
        id: lblInternalLabel
        font.pixelSize: 26
        font.bold: true
        color: enabled ? "white" : "dark grey"
    }

    Switch {
        id: swInternalSwitch
        anchors.rightMargin: 10
        anchors.right: parent.right
        anchors.verticalCenter: lblInternalLabel.verticalCenter
    }
}
