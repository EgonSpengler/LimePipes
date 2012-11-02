/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class MainWindow mainwindow.h
  *
  * @fn void createObjectNames()
  * @brief Members derived from QObject, which are declared in the ui file get automatically
  *     assigned an object name. Here the other members can get an object name.
  *     The object name is used in the testclass for getting a pointer to child objects with
  *     QObject->findChild function.
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QMessageBox>
#include <musicmodel.h>
#include <itemdatatypes.h>
#include <musicproxymodel.h>
#include <app/newtunedialog.h>
#include <app/addsymbolsdialog.h>
#include <views/treeview/treeview.h>

Q_IMPORT_PLUGIN(lp_greathighlandbagpipe)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_addSymbolsDialog = new AddSymbolsDialog(this);

    createModelAndView();
    createConnections();
    createObjectNames();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createModelAndView()
{
    m_treeView = new TreeView(this);

    MusicModel *musicModel = new MusicModel(this);
    MusicProxyModel *proxyModel = new MusicProxyModel(this);
    proxyModel->setSourceModel(musicModel);
    m_model = proxyModel;

    m_treeView->setModel(m_model);
    setCentralWidget(m_treeView);
}

void MainWindow::createConnections()
{
    connect(m_addSymbolsDialog, SIGNAL(insertSymbol(QString)),
            this, SLOT(insertSymbol(QString)));
}

void MainWindow::createObjectNames()
{
    m_treeView->setObjectName("treeView");
    m_model->setObjectName("musicModel");
}

QString MainWindow::instrumentFromCurrentIndex()
{
    QModelIndex currentIndex = m_treeView->currentIndex();
    if (currentIndex.isValid()) {
        QVariant currentInstrument = m_model->data(currentIndex, LP::tuneInstrument);
        if (currentInstrument.isValid()) {
            return currentInstrument.value<InstrumentPtr>()->name();
        }
    }
    return QString();
}

MusicModelInterface *MainWindow::musicModelFromItemModel(QAbstractItemModel *model)
{
    return dynamic_cast<MusicModelInterface*>(model);
}

void MainWindow::on_fileNewAction_triggered()
{
    MusicModelInterface *musicModel;
    if ((musicModel = musicModelFromItemModel(m_model)))
        musicModel->clear();
}

void MainWindow::on_editAddTuneAction_triggered()
{
    MusicModelInterface *musicModel;
    musicModel = musicModelFromItemModel(m_model);

    if (!musicModel)
        return;

    NewTuneDialog dialog(musicModel->instrumentNames(), this);
    if (dialog.exec() == QDialog::Accepted) {

        QModelIndex score = musicModel->appendScore(dialog.scoreTitle());
        QModelIndex tune = musicModel->appendTuneToScore(score, dialog.instrumentTitle());
        m_treeView->setCurrentIndex(tune);
    }
}

void MainWindow::on_editAddSymbolsAction_triggered()
{
    MusicModelInterface *musicModel;
    musicModel = musicModelFromItemModel(m_model);

    if (!musicModel)
        return;

    QString instrumentName = instrumentFromCurrentIndex();
    if (!instrumentName.isEmpty()) {
        m_addSymbolsDialog->setSymbolNames(
                    musicModel->symbolNamesForInstrument(instrumentName));
        m_addSymbolsDialog->show();
    } else {
        QMessageBox message;
        message.setText(tr("Please select a tune"));
        message.exec();
    }
}

void MainWindow::insertSymbol(const QString &symbolName)
{
    QString instrumentName = instrumentFromCurrentIndex();
    if (!instrumentName.isEmpty()) {

        MusicModelInterface *musicModel;
        musicModel = musicModelFromItemModel(m_model);

        if (!musicModel)
            return;

        musicModel->insertSymbol(0, m_treeView->currentIndex(), symbolName);
        m_treeView->expand(m_treeView->currentIndex());
    }
}
