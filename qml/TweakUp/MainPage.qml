import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: pgMain
    tools: commonTools
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
                    text: qsTr("Allow uploading")
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
                    text: qsTr("Allow removing")
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
                    onTextChanged: {
                        if (tfFriendlyName.text !== upnpSettings.friendlyName) {
                            upnpSettings.friendlyName = tfFriendlyName.text;
                        }
                    }
                }

                Separator {
                    width: parent.width
                    text: qsTr("Media profiles")
                }

                LabelledSwitch {
                    width: column.width
                    text: qsTr("Extended media profiles")
                    checked: upnpSettings.extendedMediaProfiles
                    onCheckedChanged: {
                        if (checked != upnpSettings.extendedMediaProfiles) {
                            upnpSettings.extendedMediaProfiles = checked;
                        }
                    }
                }

                ProgressBar {
                    id: pbIndexing
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    width: parent.width
                    Connections {
                        target: mediaIndexer
                        onProgress: pbIndexing.value = currentProgress
                    }
                }

                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Rescan media files")
                    onClicked: mediaIndexer.run()
                }

                Button{
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Click here!")
                    onClicked: upnpSettings.sync()
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
        color: "dark cyan"

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
    }
}
