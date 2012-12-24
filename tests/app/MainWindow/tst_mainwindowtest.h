/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QObject>
#include <QTreeView>
#include <QAction>
#include "app/mainwindow.h"

class MainWindowTest : public QObject
{
    Q_OBJECT
    
public:
    MainWindowTest()
        : m_mainWindow(0),
          m_treeView(0),
          m_model(0),
          m_fileNewAction(0),
          m_fileQuitAction(0),
          m_editAddTuneAction(0),
          m_editAddSymbolsAction(0)
    {}
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

private:
    MainWindow *m_mainWindow;
    QTreeView *m_treeView;
    QAbstractItemModel *m_model;
    QAction *m_fileNewAction;
    QAction *m_fileQuitAction;
    QAction *m_editAddTuneAction;
    QAction *m_editAddSymbolsAction;
};

#endif
