#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QQmlContext>
#include <QList>
#include "scoreinfo.h"
#include "myhttpengine.h"



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    QtQuick2ApplicationViewer viewer;
    QQmlContext * myContext = viewer.rootContext();

    MyHttpEngine * engine = new MyHttpEngine(myContext);

    myContext->setContextProperty("listModelC",QVariant::fromValue(engine->scoreList));
    viewer.setMainQmlFile(QStringLiteral("qml/ShowList/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
