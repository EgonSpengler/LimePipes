/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ROWITERATOR_H
#define ROWITERATOR_H

#include <QList>

class QGraphicsWidget;
class VisualItem;
class QModelIndex;
class VisualMusicModel;

class RowIterator
{
    friend class RowIteratorTest;

public:
    explicit RowIterator();
    explicit RowIterator(const VisualMusicModel *model);

    QGraphicsWidget *rowAt(int index) const;
    int rowCount() const;

protected:
    VisualItem *visualItemFromIndex(const QModelIndex& itemIndex);
    QList<QGraphicsWidget*> m_rowItems;

private:
    const VisualMusicModel *visualMusicModel;
};

#endif // ROWITERATOR_H
