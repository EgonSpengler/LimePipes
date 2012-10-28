/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "treeview.h"
#include <QKeyEvent>
#include <pitchdelegate.h>
#include <lengthdelegate.h>
#include <model/itemdatatypes.h>
#include <model/symbols/melodynote.h>

TreeView::TreeView(QWidget *parent)
    : QTreeView(parent)
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

void TreeView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() != Qt::Key_Period) {
        QTreeView::keyPressEvent(event);
    } else {
        QModelIndex index = currentIndex();
        QVariant dotsVariant = index.data(LP::melodyNoteDots);
        if (!dotsVariant.isValid())
            return;

        if (dotsVariant.canConvert<int>()) {
            int dots = dotsVariant.value<int>();

            dots++;

            if (dots > MelodyNote::MaxDots)
                dots = 0;

            model()->setData(index, QVariant(dots), LP::melodyNoteDots);
            update(index);
        }
    }
}

