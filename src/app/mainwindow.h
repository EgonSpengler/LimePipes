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
#include <QMap>
#include <datatypes/instrument.h>

class QTreeView;
class QDir;
class InstrumentInterface;
class SymbolInterface;
class Instrument;
class MusicModel;
class AddSymbolsDialog;
class NewTuneDialog;
class InstrumentManager;

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
    void on_editAddTuneAction_triggered();
    void on_editAddSymbolsAction_triggered();
    void insertSymbol(const QString &symbolName);

private:
    QDir pluginsDir();
    void createModelAndView();
    void createConnections();
    void createObjectNames();
    InstrumentPtr instrumentFromCurrentIndex();

    Ui::MainWindow *ui;
    QTreeView *m_treeView;
    MusicModel *m_model;
    AddSymbolsDialog *m_addSymbolsDialog;
    InstrumentManager *m_instrumentManager;
};

#endif // MAINWINDOW_H
