#include <QtGui/QApplication>
#include <QtDeclarative>

#include "qmlapplicationviewer.h"

#include "rygelsettings.h"
#include "focuseventfilter.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    RygelSettings settings;
    FocusEventFilter focusEventFilter(&settings);
    QDeclarativeContext *root = viewer.rootContext();
    root->setContextProperty(QLatin1String("upnpSettings"), &settings);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/TweakUp/main.qml"));
    viewer.installEventFilter(&focusEventFilter);
    viewer.showExpanded();

    return app->exec();
}
