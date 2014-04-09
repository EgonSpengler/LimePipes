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
#include <QtPlugin>
#include <utilities/error.h>
#include <model/musicmodel.h>
#include <common/itemdataroles.h>
#include <treeview/musicproxymodel.h>
#include <views/treeview/treeview.h>
#include <views/graphicsitemview/graphicsitemview.h>
#include "commonpluginmanager.h"
#include "SMuFL/smuflloader.h"
#include "dialogs/newtunedialog.h"
#include "dialogs/addsymbolsdialog.h"
#include "dialogs/aboutdialog.h"
#include "dialogs/settingsdialog.h"

Q_IMPORT_PLUGIN(GreatHighlandBagpipe)
Q_IMPORT_PLUGIN(IntegratedSymbols)

namespace {

const int StatusTimeout =
        10      /* seconds */
        * 1000  /* milli seconds */;
}

const QString pluginsDirName("plugins");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_treeView(0),
    m_graphicsItemView(0),
    m_graphicsScene(0),
    m_proxyModel(0),
    m_model(0),
    m_addSymbolsDialog(0),
    m_aboutDialog(0),
    m_settingsDialog(0)
{
    ui->setupUi(this);

    QDir pluginsDir(QCoreApplication::applicationDirPath());
    if (!pluginsDir.exists(pluginsDirName)) {
        pluginsDir.mkdir(pluginsDirName);
    }
    pluginsDir.cd(pluginsDirName);

    CommonPluginManager *pluginManager = new CommonPluginManager(pluginsDir);
    m_pluginManager = PluginManager(pluginManager);

    m_addSymbolsDialog = new AddSymbolsDialog(this);
    m_aboutDialog = new AboutDialog(this);
    m_settingsDialog = new SettingsDialog(this);

    initSmufl();
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

void MainWindow::initSmufl()
{
    int staffLineHeight = 20;
    int oneEm = 4 * staffLineHeight;
    SMuFLLoader *smuflLoader = new SMuFLLoader();

    smuflLoader->setFontFromPath(QStringLiteral(":/SMuFL/fonts/Bravura/Bravura.otf"));
    smuflLoader->setFontPixelSize(oneEm);
    smuflLoader->loadGlyphnamesFromFile(QStringLiteral(":/SMuFL/glyphnames.json"));
    smuflLoader->loadFontMetadataFromFile(QStringLiteral(":/SMuFL/fonts/Bravura/metadata.json"));
    m_smufl = SMuFLPtr(smuflLoader);
}

void MainWindow::createModelAndView()
{
    m_treeView = new TreeView(this);
    m_graphicsItemView = new GraphicsItemView(this);
    m_graphicsItemView->setPluginManager(m_pluginManager);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(m_treeView);
    splitter->addWidget(m_graphicsItemView);
    splitter->setStretchFactor(0, 2);
    splitter->setStretchFactor(1, 5);

    MusicModel *musicModel = new MusicModel(this);
    musicModel->setPluginManager(m_pluginManager);

    m_model = musicModel;

    MusicProxyModel *proxyModel = new MusicProxyModel(this);
    proxyModel->setSourceModel(m_model);
    m_proxyModel = proxyModel;

    m_treeView->setModel(m_proxyModel);

    m_graphicsItemView->setModel(m_model);
    setCentralWidget(splitter);
}

void MainWindow::createMenusAndToolBars()
{
    MusicModelInterface *musicModel = musicModelFromItemModel(m_proxyModel);
    ui->editUndoAction->setEnabled(musicModel->undoStack()->canUndo());
    ui->editRedoAction->setEnabled(musicModel->undoStack()->canRedo());
}

void MainWindow::createConnections()
{
    connect(m_addSymbolsDialog, SIGNAL(insertSymbol(QString)),
            this, SLOT(insertSymbol(QString)));

    MusicModelInterface *musicModel = musicModelFromItemModel(m_proxyModel);
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
    m_proxyModel->setObjectName("musicModel");
}

QString MainWindow::instrumentFromParentOfCurrentIndex()
{
    QModelIndex currentIndex = m_treeView->currentIndex();
    MusicModelInterface *musicModel = musicModelFromItemModel(m_proxyModel);
    if (!musicModel) return QString();

    while (!musicModel->isIndexTune(currentIndex)) {
        currentIndex = currentIndex.parent();

        if (!currentIndex.isValid())
            break;
    }

    if (currentIndex.isValid()) {
        QVariant currentInstrument = m_proxyModel->data(currentIndex, LP::TuneInstrument);
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

    if (MusicModelInterface *musicModel = musicModelFromItemModel(m_proxyModel)) {
        musicModel->clear();
        musicModel->setFilename(QString());
        musicModel->undoStack()->clear();
    }
    updateUi();
}

bool MainWindow::okToClearData()
{
    if (MusicModelInterface *musicModel = musicModelFromItemModel(m_proxyModel)) {
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
    int rows = m_proxyModel->rowCount();
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

    MusicModelInterface *model = musicModelFromItemModel(m_proxyModel);
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
    MusicModelInterface *model = musicModelFromItemModel(m_proxyModel);
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
    MusicModelInterface *model = musicModelFromItemModel(m_proxyModel);
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
    musicModel = musicModelFromItemModel(m_proxyModel);

    if (!musicModel)
        return;

    NewTuneDialog dialog(m_pluginManager->instrumentNames(), this);
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
    musicModel = musicModelFromItemModel(m_proxyModel);

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
    musicModel = musicModelFromItemModel(m_proxyModel);

    if (!musicModel)
        return;

    QString instrumentName = instrumentFromParentOfCurrentIndex();
    if (!instrumentName.isEmpty()) {
        m_addSymbolsDialog->setSymbolNames(
                    m_pluginManager->symbolNamesForInstrument(instrumentName));
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
    musicModel = musicModelFromItemModel(m_proxyModel);

    musicModel->undoStack()->undo();
    updateUi();
}

void MainWindow::on_editRedoAction_triggered()
{
    MusicModelInterface *musicModel;
    musicModel = musicModelFromItemModel(m_proxyModel);

    musicModel->undoStack()->redo();
    m_treeView->expandAll();
    updateUi();
}

void MainWindow::on_helpAboutAction_triggered()
{
    m_aboutDialog->show();
}

void MainWindow::on_editSettingsAction_triggered()
{
    m_settingsDialog->show();
}

void MainWindow::insertSymbol(const QString &symbolName)
{
    QString instrumentName = instrumentFromParentOfCurrentIndex();
    if (!instrumentName.isEmpty()) {

        MusicModelInterface *musicModel;
        musicModel = musicModelFromItemModel(m_proxyModel);

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
