/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "treeview.h"

TreeView::TreeView(QWidget *parent) :
    QTreeView(parent)
{
    m_pitchDelegate = new PitchDelegate();
    setItemDelegateForColumn(1, m_pitchDelegate);

    m_lengthDelegate = new LengthDelegate();
    setItemDelegateForColumn(2, m_lengthDelegate);
}

TreeView::~TreeView()
{
    delete m_pitchDelegate;
    delete m_lengthDelegate;
}
