/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtGui/QApplication>
#include <QIcon>
#include "qmlapplicationviewer.h"

/* Tests */
#include <QDebug>
/* End Test */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/build/main.qml"));
    viewer.showExpanded();
    viewer.setWindowIcon(QIcon(":/application/resources/img/application.svg"));

    return app.exec();
}
