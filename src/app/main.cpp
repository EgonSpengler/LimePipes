/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QApplication>
#include <QIcon>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(integratedsymbols);

    QApplication app(argc, argv);
    QApplication::setApplicationName("LimePipes");
    QApplication::setOrganizationName("limepipes.org");
    app.setWindowIcon(QIcon(":/application/application_icon"));

    MainWindow w;
    w.show();

    return app.exec();
}
