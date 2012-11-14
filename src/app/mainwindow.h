/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTreeView;
class QDir;
class InstrumentInterface;
class SymbolInterface;
class Instrument;
class MusicModel;
class AddSymbolsDialog;
class NewTuneDialog;
class QAbstractItemModel;
class MusicModelInterface;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_fileNewAction_triggered();
    void on_fileOpenAction_triggered();
    void on_fileSaveAction_triggered();
    void on_fileSaveAsAction_triggered();
    void on_editAddTuneAction_triggered();
    void on_editAddTunePartAction_triggered();
    void on_editAddSymbolsAction_triggered();
    void on_editUndoAction_triggered();
    void on_editRedoAction_triggered();
    void insertSymbol(const QString &symbolName);
    void setWindowModifiedForUndoStackCleanState(bool clean);

private:
    void createModelAndView();
    void createMenusAndToolBars();
    void createConnections();
    void createObjectNames();
    void loadFile(const QString &fileName);
    bool saveFile();
    bool saveFileAs();
    bool okToClearData();
    void updateUi();
    QString instrumentFromCurrentIndex();
    MusicModelInterface *musicModelFromItemModel(QAbstractItemModel *model);

    Ui::MainWindow *ui;
    QTreeView *m_treeView;
    QAbstractItemModel *m_model;
    AddSymbolsDialog *m_addSymbolsDialog;
};

#endif // MAINWINDOW_H
