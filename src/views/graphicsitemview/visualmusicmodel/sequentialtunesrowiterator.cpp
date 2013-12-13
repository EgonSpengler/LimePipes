/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualitem.h"
#include "interactinggraphicsitems/interactinggraphicsitem.h"
#include "sequentialtunesrowiterator.h"

SequentialTunesRowIterator::SequentialTunesRowIterator(const VisualMusicModel *model,
                                                       const QModelIndex &scoreIndex)
    : RowIterator(model)
{
    VisualItem *visualScore = visualItemFromIndex(scoreIndex);
    if (!visualScore)
        return;

    InteractingGraphicsItem *scoreHeaderItem = visualScore->rowGraphics().at(0);
    InteractingGraphicsItem *scoreFooterItem = visualScore->rowGraphics().at(1);
    m_rowItems.append(static_cast<QGraphicsWidget*>(scoreHeaderItem));
    m_rowItems.append(static_cast<QGraphicsWidget*>(scoreFooterItem));
}
