/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setOrganizationName(QStringLiteral("limepipes.org"));
    QApplication::setApplicationName(QStringLiteral("LimePipes"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
