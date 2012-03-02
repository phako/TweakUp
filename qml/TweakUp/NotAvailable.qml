// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.0
import com.nokia.meego 1.0

Page {
    Label {
        width: parent.width
        font.pixelSize: 76
        color: "#333"
        text: qsTr("Network media sharing is not available on this device")
        anchors.centerIn: parent
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
    }
}
