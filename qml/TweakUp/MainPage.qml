import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: pgMain
    orientationLock: lockInPortrait

    Flickable {
        id: flckContent
        clip: true
        anchors.top: rtnTitle.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        contentWidth: parent.width
        contentHeight: column.height
        flickableDirection: Flickable.VerticalFlick

        Rectangle {
            width: parent.width
            id: rtnContent
            color: "blue"

            Column {
                width: parent.width
                spacing: 24
                id: column

                Separator {
                    width: parent.width
                    text: qsTr("Configuration")
                }

                LabelledSwitch {
                    width: column.width
                    text: qsTr("Audio transcoding")
                    checked: upnpSettings.lpcmTranscoding
                    onCheckedChanged: {
                        if (checked != upnpSettings.lpcmTranscoding) {
                            upnpSettings.lpcmTranscoding = checked;
                        }
                    }
                }

                LabelledSwitch {
                    width: column.width
                    text: qsTr("Share files without profile")
                    checked: !upnpSettings.strictSharing
                    onCheckedChanged: {
                        if (checked == upnpSettings.strictSharing) {
                            upnpSettings.strictSharing = !checked;
                        }
                    }
                }

                LabelledSwitch {
                    width: column.width
                    text: qsTr("Other UPnP devices may upload media files to the phone")
                    checked: upnpSettings.allowUpload
                    onCheckedChanged: {
                        if (checked != upnpSettings.allowUpload) {
                            upnpSettings.allowUpload = checked;
                            lswAllowRemove.enabled = checked;
                        }
                    }
                }

                LabelledSwitch {
                    id: lswAllowRemove
                    enabled: upnpSettings.allowUpload
                    indent: true
                    width: column.width
                    text: qsTr("UPnP devices may remove files uploaded via UPnP")
                    checked: upnpSettings.allowRemoveUpload
                    onCheckedChanged: {
                        if (checked != upnpSettings.allowRemoveUpload) {
                            upnpSettings.allowRemoveUpload = checked;
                        }
                    }
                }

                Label {
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.pixelSize: 26
                    font.bold: true
                    color: "white"
                    text: qsTr("Name on network")
                }

                TextField {
                    id: tfFriendlyName
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    text: upnpSettings.friendlyName

                    onActiveFocusChanged: {
                        if ((!activeFocus) && (tfFriendlyName.text !== upnpSettings.friendlyName)) {
                            upnpSettings.friendlyName = tfFriendlyName.text;
                        }
                    }

                    Keys.onReturnPressed: {
                        if (tfFriendlyName.text !== upnpSettings.friendlyName) {
                            upnpSettings.friendlyName = tfFriendlyName.text;
                        }
                    }
                }

                PropertyAnimation {
                    id: fade
                    target: button
                    property: "opacity"
                    to: upnpSettings.dirty ? 1.0 : 0
                    duration: 200
                }

                Button {
                    visible: upnpSettings.running
                    id: button
                    opacity: 0
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: qsTr("Restart media-sharing")
                    Connections {
                        target: upnpSettings
                        onDirtyChanged: fade.start()
                    }

                    onClicked: upnpSettings.restart();
                }
            }
        }
    }


    ScrollDecorator {
        flickableItem: flckContent
    }

    Rectangle {
        id: rtnTitle
        width: parent.width
        height: 70
        color: "black"

        Label {
            id: text
            text: qsTr("Tweak media sharing settings")
            elide: Text.ElideRight
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 16
            platformStyle: LabelStyle {
                textColor: "white"
                fontPixelSize: 28
            }
        }

        Image {
            anchors.right: parent.right
            anchors.rightMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            source: "image://theme/icon-m-settings-dlna-server"
        }
    }
}
