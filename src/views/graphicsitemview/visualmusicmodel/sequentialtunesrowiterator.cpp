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
    const QAbstractItemModel *itemModel = scoreIndex.model();
    if (!visualScore || !itemModel)
        return;

    QList<InteractingGraphicsItem*> scoreItems = visualScore->rowGraphics();

    InteractingGraphicsItem *scoreHeaderItem = 0;
    if (scoreItems.count())
        scoreHeaderItem = visualScore->rowGraphics().at(0);

    InteractingGraphicsItem *scoreFooterItem = 0;
    if (scoreItems.count() > 1)
        scoreFooterItem = visualScore->rowGraphics().at(1);

    if (scoreHeaderItem)
        m_rowItems.append(static_cast<QGraphicsWidget*>(scoreHeaderItem));

    for (int i = 0; i < itemModel->rowCount(scoreIndex); i++) {
        QModelIndex tuneIndex = itemModel->index(i, 0, scoreIndex);
        if (!tuneIndex.isValid())
            continue;

        appendTune(tuneIndex);
    }

    if (scoreFooterItem)
        m_rowItems.append(static_cast<QGraphicsWidget*>(scoreFooterItem));
}

void SequentialTunesRowIterator::appendTune(const QModelIndex &tuneIndex)
{
    const QAbstractItemModel *model = tuneIndex.model();
    if (!model)
        return;

    for (int i = 0; i < model->rowCount(tuneIndex); ++i) {
        QModelIndex partIndex = model->index(i, 0, tuneIndex);
        if (!partIndex.isValid())
            continue;

        appendPart(partIndex);
    }
}

void SequentialTunesRowIterator::appendPart(const QModelIndex &partIndex)
{
    const QAbstractItemModel *model = partIndex.model();
    if (!model)
        return;

    VisualItem *visualPart = visualItemFromIndex(partIndex);
    if (!visualPart)
        return;

    QList<InteractingGraphicsItem*> staffItems(visualPart->rowGraphics());
    for (int j = 0; j < staffItems.count(); ++j) {
        InteractingGraphicsItem *staffItem = staffItems.at(j);
        if (!staffItem)
            return;

        m_rowItems.append(static_cast<QGraphicsWidget*>(staffItem));
    }
}
