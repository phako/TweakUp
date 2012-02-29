import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow

    ToolBarLayout {
        id: commonTools
        visible: false
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: (myMenu.status === DialogStatus.Closed) ? myMenu.open() : myMenu.close()
        }
    }

    Menu {
        id: myMenu
        visualParent: pageStack
        MenuLayout {
            MenuItem { text: qsTr("Sample menu item") }
        }
    }
    Component.onCompleted: {
        theme.inverted = true;
        var component;
        if (upnpSettings.available()) {
            commonTools.visible = true;
            component = Qt.createComponent("MainPage.qml");
            if (component.status === Component.Ready) {
                pageStack.push(component.createObject(appWindow));
            }
        } else {
            component = Qt.createComponent("NotAvailable.qml");
            if (component.status === Component.Ready) {
                pageStack.push(component.createObject(appWindow));
            }
        }
    }
}
