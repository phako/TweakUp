#include <QtGui/QApplication>
#include <QtDeclarative>

#include "qmlapplicationviewer.h"

#include "rygelsettings.h"
#include "mediaindexer.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    RygelSettings settings;
    MediaIndexer indexer;
    QDeclarativeContext *root = viewer.rootContext();
    root->setContextProperty(QLatin1String("upnpSettings"), &settings);
    root->setContextProperty(QLatin1String("mediaIndexer"), &indexer);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/TweakUp/main.qml"));
    viewer.showExpanded();


    return app->exec();
}
