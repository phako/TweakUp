// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    property alias text: txtInternal.text
    property string color: "dark grey"

    height: txtInternal.height
    anchors.bottomMargin: 3
    anchors.topMargin: 3

    Rectangle {
        color: parent.color
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        anchors.left: parent.left
        width: parent.width - (txtInternal.visible ? (txtInternal.width + 30) : 0)
        height: 2
        anchors.verticalCenter: txtInternal.verticalCenter
    }

    Text {
        visible: text !== ""
        anchors.right: parent.right
        id: txtInternal
        color: parent.color
        font {
            pixelSize: 20
            //italic: true
        }
    }
}
