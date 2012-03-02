import QtQuick 1.0
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow

    MainPage {
        id: mainPage
    }

    NotAvailable {
        id: notAvailablePage
    }

    Component.onCompleted: {
        theme.inverted = true;
        if (upnpSettings.available()) {
            pageStack.push(mainPage);
        } else {
            pageStack.push(notAvailablePage);
        }
    }
}
