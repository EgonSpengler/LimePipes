/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>
#include <pitchdelegate.h>
#include <lengthdelegate.h>

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit TreeView(QWidget *parent = 0);
    ~TreeView();
    
private:
    PitchDelegate *m_pitchDelegate;
    LengthDelegate *m_lengthDelegate;
};

#endif // TREEVIEW_H
