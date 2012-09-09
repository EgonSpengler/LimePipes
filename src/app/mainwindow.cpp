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
#include <QTreeView>
#include <QMenu>
#include <QMenuBar>
#include <instrumentinterface.h>
#include <musicmodel.h>

#include <QDebug>

Q_IMPORT_PLUGIN(lp_greathighlandbagpipe)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadStaticPlugins();
    createModelAndView();
    createActions();
    createMenusAndToolBar();
    createConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createModelAndView()
{
    m_treeView = new QTreeView();
    m_model = new MusicModel();
    m_treeView->setModel(m_model);
    setCentralWidget(m_treeView);
}

void MainWindow::createActions()
{
    fileNewAction = new QAction(tr("&New"), this);
    fileCloseAction = new QAction(tr("&Quit"), this);
    editAddTuneAction = new QAction(tr("&Add Tune"), this);
}

void MainWindow::createMenusAndToolBar()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(fileNewAction);
    fileMenu->addAction(fileCloseAction);

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(editAddTuneAction);
}

void MainWindow::createConnections()
{
    connect(fileNewAction, SIGNAL(triggered()),
            this, SLOT(fileNew()));
    connect(fileCloseAction, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(editAddTuneAction, SIGNAL(triggered()),
            this, SLOT(editAddTune()));
}

void MainWindow::loadStaticPlugins()
{
    foreach (QObject *plugin, QPluginLoader::staticInstances()) {
        loadInstrument(plugin);
    }
}

void MainWindow::loadInstrument(QObject *plugin)
{
    InstrumentInterface *iInstrument = qobject_cast<InstrumentInterface *> (plugin);
    if (iInstrument) {
        m_instruments.insert(iInstrument->name(), iInstrument);
    }
}

void MainWindow::fileNew()
{
    m_model->clear();
}

void MainWindow::editAddTune()
{
}
