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
#include <QScopedPointer>
#include <QSplitter>
#include <QUndoStack>
#include <utilities/error.h>
#include <musicmodel.h>
#include <itemdatatypes.h>
#include <treeview/musicproxymodel.h>
#include <views/treeview/treeview.h>
#include <views/graphicsitemview/graphicsitemview.h>
#include "newtunedialog.h"
#include "addsymbolsdialog.h"
#include "aboutdialog.h"


Q_IMPORT_PLUGIN(lp_greathighlandbagpipe)

namespace {

const int StatusTimeout =
        10      /* seconds */
        * 1000  /* milli seconds */;

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_addSymbolsDialog = new AddSymbolsDialog(this);
    m_aboutDialog = new AboutDialog(this);

    createModelAndView();
    createMenusAndToolBars();
    createConnections();
    createObjectNames();

    setWindowTitle(tr("%1 [*]")
                   .arg(QApplication::applicationName()));
    updateUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createModelAndView()
{
    m_treeView = new TreeView(this);
    m_graphicsItemView = new GraphicsItemView(this);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(m_treeView);
    splitter->addWidget(m_graphicsItemView);
    splitter->setStretchFactor(0, 2);
    splitter->setStretchFactor(1, 5);

    MusicModel *musicModel = new MusicModel(this);
    MusicProxyModel *proxyModel = new MusicProxyModel(this);
    proxyModel->setSourceModel(musicModel);
    m_model = proxyModel;

    m_treeView->setModel(m_model);
    m_graphicsItemView->setModel(m_model);
    setCentralWidget(splitter);
}

void MainWindow::createMenusAndToolBars()
{
    MusicModelInterface *musicModel = musicModelFromItemModel(m_model);
    ui->editUndoAction->setEnabled(musicModel->undoStack()->canUndo());
    ui->editRedoAction->setEnabled(musicModel->undoStack()->canRedo());
}

void MainWindow::createConnections()
{
    connect(m_addSymbolsDialog, SIGNAL(insertSymbol(QString)),
            this, SLOT(insertSymbol(QString)));

    MusicModelInterface *musicModel = musicModelFromItemModel(m_model);
    connect(musicModel->undoStack(), SIGNAL(canUndoChanged(bool)),
            ui->editUndoAction, SLOT(setEnabled(bool)));
    connect(musicModel->undoStack(), SIGNAL(canRedoChanged(bool)),
            ui->editRedoAction, SLOT(setEnabled(bool)));

    connect(musicModel->undoStack(), SIGNAL(cleanChanged(bool)),
            this, SLOT(setWindowModifiedForUndoStackCleanState(bool)));
}

void MainWindow::createObjectNames()
{
    m_treeView->setObjectName("treeView");
    m_model->setObjectName("musicModel");
}

QString MainWindow::instrumentFromParentOfCurrentIndex()
{
    QModelIndex currentIndex = m_treeView->currentIndex();
    MusicModelInterface *musicModel = musicModelFromItemModel(m_model);
    if (!musicModel) return QString();

    while (!musicModel->isIndexTune(currentIndex)) {
        currentIndex = currentIndex.parent();

        if (!currentIndex.isValid())
            break;
    }

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
    if (!okToClearData())
        return;

    if (MusicModelInterface *musicModel = musicModelFromItemModel(m_model)) {
        musicModel->clear();
        musicModel->setFilename(QString());
        musicModel->undoStack()->clear();
    }
    updateUi();
}

bool MainWindow::okToClearData()
{
    if (MusicModelInterface *musicModel = musicModelFromItemModel(m_model)) {
        if (!musicModel->undoStack()->isClean()) {
            QScopedPointer<QMessageBox> messageBox(new QMessageBox(this));
            messageBox->setWindowModality(Qt::WindowModal);
            messageBox->setIcon(QMessageBox::Question);
            messageBox->setWindowTitle(QString("%1 - %2")
                    .arg(QApplication::applicationName()).arg(tr("Unsaved changes")));
            messageBox->setText(tr("Save unsaved changes?"));
            messageBox->addButton(QMessageBox::Save);
            messageBox->addButton(QMessageBox::Discard);
            messageBox->addButton(QMessageBox::Cancel);
            messageBox->setDefaultButton(QMessageBox::Save);
            messageBox->exec();
            if (messageBox->clickedButton() ==
                messageBox->button(QMessageBox::Cancel))
                return false;
            if (messageBox->clickedButton() ==
                messageBox->button(QMessageBox::Save))
                return saveFile();
        }
    }
    return true;
}

void MainWindow::updateUi()
{
    ui->fileSaveAction->setEnabled(isWindowModified());
    int rows = m_model->rowCount();
    ui->fileSaveAsAction->setEnabled(isWindowModified() || rows);
    ui->editAddSymbolsAction->setEnabled(rows);
    ui->editAddTunePartAction->setEnabled(rows);
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
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    MusicModelInterface *model = musicModelFromItemModel(m_model);
    try {
        model->load(fileName);

        setWindowTitle(tr("%1 - %2[*]")
                       .arg(QApplication::applicationName())
                       .arg(QFileInfo(fileName).fileName()));
        statusBar()->showMessage(tr("Loaded %1").arg(fileName),
                                 StatusTimeout);
    } catch (LP::Error &error) {
        qWarning() << tr("Error") << tr("Failed to load %1: %2")
                      .arg(fileName).arg(QString::fromUtf8(error.what()));
    }

    QApplication::restoreOverrideCursor();
    updateUi();
}

void MainWindow::on_fileSaveAction_triggered()
{
    saveFile();
}

void MainWindow::on_fileSaveAsAction_triggered()
{
    saveFileAs();
}

bool MainWindow::saveFile()
{
    bool saved = false;
    MusicModelInterface *model = musicModelFromItemModel(m_model);
    if (model->filename().isEmpty()) {
        return saveFileAs();
    } else {
        try {
            model->save();
            setWindowTitle(tr("%1 - %2[*]")
                           .arg(QApplication::applicationName())
                           .arg(QFileInfo(model->filename()).fileName()));
            statusBar()->showMessage(tr("Saved %1")
                                     .arg(model->filename()), StatusTimeout);
            saved = true;
            model->undoStack()->setClean();
        } catch (LP::Error &error) {
            qWarning() << tr("Failed to save %1: %2").arg(model->filename())
                          .arg(QString::fromUtf8(error.what()));
        }
    }
    updateUi();
    return saved;
}

bool MainWindow::saveFileAs()
{
    MusicModelInterface *model = musicModelFromItemModel(m_model);
    QString filename = model->filename();
    QString dir = filename.isEmpty() ? "." : QFileInfo(filename).path();
    filename = QFileDialog::getSaveFileName(this,
                                            tr("%1 - Save As").arg(QApplication::applicationName()),
                                            dir,
                                            tr("%1 (*.lime)").arg(QApplication::applicationName()));

    if (filename.isEmpty())
        return false;

    if (!filename.toLower().endsWith(".lime"))
        filename += ".lime";

    model->setFilename(filename);
    return saveFile();
}

void MainWindow::on_editAddTuneAction_triggered()
{
    MusicModelInterface *musicModel;
    musicModel = musicModelFromItemModel(m_model);

    if (!musicModel)
        return;

    NewTuneDialog dialog(musicModel->instrumentNames(), this);
    if (dialog.exec() == QDialog::Accepted) {
        musicModel->undoStack()->beginMacro(tr("Add Tune"));

        QModelIndex score = musicModel->appendScore(dialog.scoreTitle());
        QModelIndex tune = musicModel->appendTuneToScore(score, dialog.instrumentTitle());
        m_treeView->setCurrentIndex(tune);

        musicModel->undoStack()->endMacro();
    }
    updateUi();
}

void MainWindow::on_editAddTunePartAction_triggered()
{
    MusicModelInterface *musicModel;
    musicModel = musicModelFromItemModel(m_model);

    if (!musicModel)
        return;

    if (musicModel->isIndexTune(m_treeView->currentIndex())) {
        musicModel->insertPartIntoTune(0, m_treeView->currentIndex(), 9, true);
        m_treeView->expand(m_treeView->currentIndex());
    }
    else {
        QMessageBox message;
        message.setText(tr("Please select a tune to add part"));
        message.exec();
    }
}

void MainWindow::on_editAddSymbolsAction_triggered()
{
    MusicModelInterface *musicModel;
    musicModel = musicModelFromItemModel(m_model);

    if (!musicModel)
        return;

    QString instrumentName = instrumentFromParentOfCurrentIndex();
    if (!instrumentName.isEmpty()) {
        m_addSymbolsDialog->setSymbolNames(
                    musicModel->symbolNamesForInstrument(instrumentName));
        m_addSymbolsDialog->show();
    } else {
        QMessageBox message;
        message.setText(tr("Please select a symbol as position to insert a new symbol"));
        message.exec();
    }
    updateUi();
}

void MainWindow::on_editUndoAction_triggered()
{
    MusicModelInterface *musicModel;
    musicModel = musicModelFromItemModel(m_model);

    musicModel->undoStack()->undo();
    updateUi();
}

void MainWindow::on_editRedoAction_triggered()
{
    MusicModelInterface *musicModel;
    musicModel = musicModelFromItemModel(m_model);

    musicModel->undoStack()->redo();
    m_treeView->expandAll();
    updateUi();
}

void MainWindow::on_helpAboutAction_triggered()
{
    m_aboutDialog->show();
}

void MainWindow::insertSymbol(const QString &symbolName)
{
    QString instrumentName = instrumentFromParentOfCurrentIndex();
    if (!instrumentName.isEmpty()) {

        MusicModelInterface *musicModel;
        musicModel = musicModelFromItemModel(m_model);

        QModelIndex currentIndex = m_treeView->currentIndex();

        if (!musicModel) return;

        if (!(musicModel->isIndexMeasure(currentIndex) ||
              musicModel->isIndexSymbol(currentIndex)))
            return;

        if (musicModel->isIndexMeasure(currentIndex)) {
            musicModel->appendSymbolToMeasure(currentIndex, symbolName);
        }
        if (musicModel->isIndexSymbol(currentIndex)) {
            musicModel->insertSymbolIntoMeasure(currentIndex.row(),
                                     currentIndex.parent(), symbolName);
        }

        m_treeView->expand(m_treeView->currentIndex());
    }
    updateUi();
}

void MainWindow::setWindowModifiedForUndoStackCleanState(bool clean)
{
    setWindowModified(!clean);
    updateUi();
}
