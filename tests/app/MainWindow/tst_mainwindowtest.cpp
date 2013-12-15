/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include "model/musicmodel.h"
#include "app/dialogs/newtunedialog.h"
#include "tst_mainwindowtest.h"

void MainWindowTest::initTestCase()
{
    m_mainWindow = new MainWindow();

    m_treeView = m_mainWindow->findChild<QTreeView*>("treeView");
    Q_ASSERT(m_treeView);

    m_fileNewAction = m_mainWindow->findChild<QAction*>("fileNewAction");
    Q_ASSERT(m_fileNewAction);

    m_fileQuitAction = m_mainWindow->findChild<QAction*>("fileQuitAction");
    Q_ASSERT(m_fileQuitAction);

    m_editAddTuneAction = m_mainWindow->findChild<QAction*>("editAddTuneAction");
    Q_ASSERT(m_editAddTuneAction);

    m_editAddSymbolsAction = m_mainWindow->findChild<QAction*>("editAddSymbolsAction");
    Q_ASSERT(m_editAddSymbolsAction);

    m_model = m_mainWindow->findChild<QAbstractItemModel*>("musicModel");
    Q_ASSERT(m_model);
}

void MainWindowTest::cleanupTestCase()
{
    delete m_mainWindow;
}

QTEST_MAIN(MainWindowTest)
