/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtGui/QApplication>
#include <QIcon>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}
