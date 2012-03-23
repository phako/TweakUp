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
    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: {
                pageStack.pop();
            }
        }
    }

    Flickable {
        anchors.top: rtnTitle.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        contentWidth: parent.width
        contentHeight: txtAbout.height
        Text {
            width: parent.width
            color: "white"
            font.pixelSize: 24
            id: txtAbout
            textFormat: Text.RichText
            wrapMode: Text.WordWrap
            text: "Tweak your media sharing experience" +
                  "<p>Copyright © 2012 Jens Georg &lt;<a href=\"mailto:mail+tweakup@jensge.org\">mail+tweakup@jensge.org</a>&gt;<br>" +
                  "<a href=\"https://gitorious.org/helium/tweakup\">https://gitorious.org/helium/tweakup</a><br>" +
                  "Translators:" +
                  "<ul>" +
                  "  <li>ar: Med Touhami MAHDI</li>" +
                  "  <li>fr: Corentin Julé</li>" +
                  "  <li>gl, gl_ES, es, es_ES: Miguel García Núñez, Adolfo Jayme Barrientos</li>" +
                  "  <li>it: Fabio Rosciano</li>" +
                  "</ul>" +
                  "<a href=\"https://www.transifex.net/projects/p/TweakUp\">https://www.transifex.net/projects/p/TweakUp</a></p>" +

                  "<p>This program is free software: you can redistribute it and/or modify " +
                  "it under the terms of the GNU General Public License as published by " +
                  "the Free Software Foundation, either version 3 of the License, or " +
                  "(at your option) any later version.</p>" +

                  "<p>This program is distributed in the hope that it will be useful, " +
                  "but WITHOUT ANY WARRANTY; without even the implied warranty of " +
                  "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the " +
                  "GNU General Public License for more details.</p>" +

                  "<p>You should have received a copy of the GNU General Public License " +
                  "along with this program.  If not, see <a href=\"http://www.gnu.org/licenses/\">http://www.gnu.org/licenses/</a>."
            onLinkActivated : Qt.openUrlExternally(link);
        }
    }

    Rectangle {
        id: rtnTitle
        width: parent.width
        height: 70
        color: "black"

        Label {
            id: text
            text: "About TweakUp"
            elide: Text.ElideRight
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.right: parent.right
            anchors.rightMargin: 16
            platformStyle: LabelStyle {
                textColor: "white"
                fontPixelSize: 28
            }
        }
    }
}
