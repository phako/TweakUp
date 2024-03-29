/*
    This file is part of TweakUp.

    Copyright (C) 2012 Jens Georg <mail+tweakup@jensge.org>

    TweakUp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TweakUp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TweakUp.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: pgMain
    orientationLock: PageOrientation.LockPortrait

    tools: ToolBarLayout {
        ToolIcon {
            anchors.right: parent.right
            iconId: "toolbar-favorite-mark"
            onClicked: {
                pageStack.push(pgAbout)
            }
        }
    }

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
                    visible: button.visible
                }

                Button {
                    visible: button.opacity != 0
                    id: button
                    opacity: 0
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: qsTr("Synchronize settings")
                    Connections {
                        target: upnpSettings
                        onDirtyChanged: paDirtyFade.start()
                    }

                    onClicked: upnpSettings.restart();
                }

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
                    text: qsTr("Share media files that do not have a DLNA profile")
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

                    onTextChanged: {
                        if (!activeFocus && tfFriendlyName.text !== upnpSettings.friendlyName) {
                            upnpSettings.friendlyName = tfFriendlyName.text;
                        }
                    }

                    onActiveFocusChanged: {
                        if (!activeFocus && tfFriendlyName.text !== upnpSettings.friendlyName) {
                            upnpSettings.friendlyName = tfFriendlyName.text;
                        }
                    }

                    Keys.onReturnPressed: {
                        if (tfFriendlyName.text !== upnpSettings.friendlyName) {
                            upnpSettings.friendlyName = tfFriendlyName.text;
                        }
                    }
                }

                Label {
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    font.pixelSize: 26
                    font.bold: true
                    color: "white"
                    text: qsTr("Only share when connected to this access point")
                }

                TextField {
                    id: tfHomeWLAN
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    text: upnpSettings.homeWLAN

                    onTextChanged: {
                        if (!activeFocus && tfHomeWLAN.text !== upnpSettings.homeWLAN) {
                            upnpSettings.homeWLAN = tfHomeWLAN.text;
                        }
                    }

                    onActiveFocusChanged: {
                        if (!activeFocus && tfHomeWLAN.text !== upnpSettings.homeWLAN) {
                            upnpSettings.homeWLAN = tfHomeWLAN.text;
                        }
                    }

                    Keys.onReturnPressed: {
                        if (tfHomeWLAN.text !== upnpSettings.homeWLAN) {
                            upnpSettings.homeWLAN = tfHomeWLAN.text;
                        }
                    }
                }

                PropertyAnimation {
                    id: paDirtyFade
                    target: button
                    property: "opacity"
                    to: upnpSettings.dirty ? 1.0 : 0
                    duration: 200
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
            anchors.right: imgSharing.left
            anchors.rightMargin: 16
            platformStyle: LabelStyle {
                textColor: "white"
                fontPixelSize: 28
            }
        }

        Image {
            id: imgSharing
            anchors.right: parent.right
            anchors.leftMargin: 10
            anchors.rightMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            source: "image://theme/icon-m-settings-dlna-server"
        }
    }
}
