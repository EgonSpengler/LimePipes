/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "tst_treeviewtest.h"

TreeViewTest::TreeViewTest()
{
}

void TreeViewTest::testCreateTreeView()
{
    TreeView();
}

QTEST_MAIN(TreeViewTest)
