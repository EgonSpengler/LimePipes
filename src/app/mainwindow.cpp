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
#include <QMessageBox>
#include <instrumentinterface.h>
#include <symbolinterface.h>
#include <musicmodel.h>
#include <newtunedialog.h>
#include <addsymbolsdialog.h>

#include <QDebug>

Q_IMPORT_PLUGIN(lp_greathighlandbagpipe)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_addSymbolsDialog = new AddSymbolsDialog(this);

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
    editAddSymbolsAction = new QAction(tr("&Add Symbols"), this);
}

void MainWindow::createMenusAndToolBar()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(fileNewAction);
    fileMenu->addAction(fileCloseAction);

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(editAddTuneAction);
    editMenu->addAction(editAddSymbolsAction);
}

void MainWindow::createConnections()
{
    connect(fileNewAction, SIGNAL(triggered()),
            this, SLOT(fileNew()));
    connect(fileCloseAction, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(editAddTuneAction, SIGNAL(triggered()),
            this, SLOT(editAddTune()));
    connect(editAddSymbolsAction, SIGNAL(triggered()),
            this, SLOT(editAddSymbols()));
    connect(m_addSymbolsDialog, SIGNAL(insertSymbol(QString)),
            this, SLOT(insertSymbol(QString)));
}

void MainWindow::loadStaticPlugins()
{
    foreach (QObject *plugin, QPluginLoader::staticInstances()) {
        loadInstrument(plugin);
    }
}

Instrument *MainWindow::instrumentForName(const QString &name)
{
    InstrumentInterface *instrumentPlugin = m_instruments.value(name);
    if (instrumentPlugin) {
        return instrumentPlugin->instrument();
    }
    return 0;
}

Instrument *MainWindow::instrumentFromCurrentIndex()
{
    QModelIndex currentIndex = m_treeView->currentIndex();
    if (currentIndex.isValid()) {
        QVariant currentInstrument = m_model->data(currentIndex, LP::tuneInstrument);
        if (currentInstrument.isValid()) {
            return currentInstrument.value<Instrument *>();
        }
    }
    return 0;
}

void MainWindow::loadInstrument(QObject *plugin)
{
    InstrumentInterface *iInstrument = qobject_cast<InstrumentInterface *> (plugin);
    if (iInstrument) {
        m_instruments.insert(iInstrument->name(), iInstrument);

        SymbolInterface *iSymbols = qobject_cast<SymbolInterface *> (plugin);
        if (iSymbols) {
            m_symbols.insert(iInstrument->name(), iSymbols);
        }
    }
}

void MainWindow::fileNew()
{
    m_model->clear();
}

void MainWindow::editAddTune()
{
    NewTuneDialog *dialog = new NewTuneDialog(m_instruments.keys(), this);
    if (dialog->exec() == QDialog::Accepted) {
        if (Instrument *instrument = instrumentForName(dialog->instrumentTitle()) ) {
            QModelIndex score = m_model->appendScore(dialog->scoreTitle());
            QModelIndex tune = m_model->appendTuneToScore(score, instrument);
            m_treeView->setCurrentIndex(tune);
        }
    }
}

void MainWindow::editAddSymbols()
{
    if (Instrument *instrument = instrumentFromCurrentIndex()) {
        m_addSymbolsDialog->setSymbolNames(m_symbols.value(instrument->name())->symbols());
        m_addSymbolsDialog->show();
    } else {
        QMessageBox message;
        message.setText(tr("Please select a tune"));
        message.exec();
    }
}

void MainWindow::insertSymbol(const QString &symbolName)
{
    if (Instrument *instrument = instrumentFromCurrentIndex()) {
        Symbol *symbol = m_symbols.value(instrument->name())->getSymbol(symbolName);
        m_model->insertSymbol(0, m_treeView->currentIndex(), symbol);
        m_treeView->expand(m_treeView->currentIndex());
    }
}
