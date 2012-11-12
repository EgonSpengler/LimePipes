/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QTreeView>
#include <QAction>
#include <QSignalSpy>
#include "app/mainwindow.h"
#include "model/musicmodel.h"
#include "app/newtunedialog.h"

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

#include "tst_mainwindowtest.moc"
