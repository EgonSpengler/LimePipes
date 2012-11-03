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
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <utilities/error.h>
#include <musicmodel.h>
#include <itemdatatypes.h>
#include <musicproxymodel.h>
#include <app/newtunedialog.h>
#include <app/addsymbolsdialog.h>
#include <views/treeview/treeview.h>

Q_IMPORT_PLUGIN(lp_greathighlandbagpipe)

namespace {

const int StatusTimeout =   10 /* seconds */
                            * 1000 /* milli seconds */;

}

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

void MainWindow::on_fileOpenAction_triggered()
{
    QString filename;
    QString dir(".");

    filename = QFileDialog::getOpenFileName(this,
            tr("%1 - Open").arg(QApplication::applicationName()),
            dir, tr("LimePipes (*.lime)"));

    if (!filename.isEmpty())
        loadFile(filename);
}

void MainWindow::loadFile(const QString &fileName)
{
    Q_UNUSED(fileName)
}

void MainWindow::on_fileSaveAction_triggered()
{
    MusicModelInterface *model = musicModelFromItemModel(m_model);
    if (model->filename().isEmpty()) {
        on_fileSaveAsAction_triggered();
    } else {
        try {
            model->save();
            setWindowTitle(tr("%1 - %2[*]")
                    .arg(QApplication::applicationName())
                    .arg(QFileInfo(model->filename()).fileName()));
            statusBar()->showMessage(tr("Saved %1")
                    .arg(model->filename()), StatusTimeout);
        } catch (LP::Error &error) {
            qWarning() << tr("Failed to save %1: %2").arg(model->filename())
                          .arg(QString::fromUtf8(error.what()));
        }
    }
}

void MainWindow::on_fileSaveAsAction_triggered()
{
    MusicModelInterface *model = musicModelFromItemModel(m_model);
    QString filename = model->filename();
    QString dir = filename.isEmpty() ? "." : QFileInfo(filename).path();
    filename = QFileDialog::getSaveFileName(this,
            tr("%1 - Save As").arg(QApplication::applicationName()),
            dir,
            tr("%1 (*.lime)").arg(QApplication::applicationName()));

    if (filename.isEmpty())
        return;

    if (!filename.toLower().endsWith(".lime"))
        filename += ".lime";

    model->setFilename(filename);
    on_fileSaveAction_triggered();
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
