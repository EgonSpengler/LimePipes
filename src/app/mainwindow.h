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

class InstrumentInterface;
class SymbolInterface;
class Instrument;
class MusicModel;
class QTreeView;
class AddSymbolsDialog;

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
    void fileNew();
    void editAddTune();
    void editAddSymbols();
    void insertSymbol(const QString &symbolName);

private:
    void createModelAndView();
    void createActions();
    void createMenusAndToolBar();
    void createConnections();
    void loadInstrument(QObject *plugin);
    void loadStaticPlugins();
    Instrument *instrumentForName(const QString &name);
    Instrument *instrumentFromCurrentIndex();

    QAction *fileNewAction;
    QAction *fileCloseAction;
    QAction *editAddTuneAction;
    QAction *editAddSymbolsAction;
    Ui::MainWindow *ui;
    QTreeView *m_treeView;
    MusicModel *m_model;
    QMap<QString, InstrumentInterface*> m_instruments;
    QMap<QString, SymbolInterface*> m_symbols;
    AddSymbolsDialog *m_addSymbolsDialog;
};

#endif // MAINWINDOW_H
