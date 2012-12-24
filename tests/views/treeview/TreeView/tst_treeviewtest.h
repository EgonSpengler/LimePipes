/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TREEVIEWTEST_H
#define TREEVIEWTEST_H

#include <views/treeview/treeview.h>

class TreeViewTest : public QObject
{
    Q_OBJECT
    
public:
    TreeViewTest();
    
private Q_SLOTS:
    void testCreateTreeView();
};

#endif
