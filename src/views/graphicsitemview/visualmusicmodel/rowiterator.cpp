/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualmusicmodel.h"
#include "rowiterator.h"

RowIterator::RowIterator()
    : visualMusicModel(0)
{
}

RowIterator::RowIterator(const VisualMusicModel *model)
    : visualMusicModel(model)
{
}

QGraphicsWidget *RowIterator::rowAt(int index) const
{
    return m_rowItems.at(index);
}

int RowIterator::rowCount() const
{
    return m_rowItems.count();
}

VisualItem *RowIterator::visualItemFromIndex(const QModelIndex &itemIndex)
{
    if (visualMusicModel == 0)
        return 0;

    return visualMusicModel->visualItemFromIndex(itemIndex);
}
