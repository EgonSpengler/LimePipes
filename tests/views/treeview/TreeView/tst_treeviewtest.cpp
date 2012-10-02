/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>

#include <views/treeview/treeview.h>

class TreeViewTest : public QObject
{
    Q_OBJECT
    
public:
    TreeViewTest();
    
private Q_SLOTS:
    void testCreateTreeView();
};

TreeViewTest::TreeViewTest()
{
}

void TreeViewTest::testCreateTreeView()
{
    TreeView();
}

QTEST_MAIN(TreeViewTest)

#include "tst_treeviewtest.moc"
