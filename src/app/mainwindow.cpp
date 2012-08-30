/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPluginLoader>
#include <instrumentinterface.h>
#include <QDebug>

Q_IMPORT_PLUGIN(lp_greathighlandbagpipe)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadStaticPlugins();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadStaticPlugins()
{
    foreach (QObject *plugin, QPluginLoader::staticInstances()) {
        printInstrumentNames(plugin);
    }
}

void MainWindow::printInstrumentNames(QObject *plugin)
{
    InstrumentInterface *iInstrument = qobject_cast<InstrumentInterface *> (plugin);
    if (iInstrument) {
        qDebug() << "Instrument " << iInstrument->name() << " loaded.";
    }
}
