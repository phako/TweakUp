// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.0
import com.nokia.meego 1.0

Page {
    Label {
        width: parent.width
        font.pixelSize: 76
        color: "#333"
        text: qsTr("Network media sharing is not available in this version. Please update to PR1.2 if available")
        anchors.centerIn: parent
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
    }
}
