/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QAbstractItemModel>
#include <musicitem.h>
#include "visualmusicmodel.h"

VisualMusicModel::VisualMusicModel(AbstractVisualItemFactory *itemFactory, QObject *parent)
    : QObject(parent),
      m_model(0),
      m_itemFactory(itemFactory)
{
}

VisualMusicModel::~VisualMusicModel()
{
}

void VisualMusicModel::rowsInserted(const QModelIndex &parent, int start, int end)
{
    if (!parent.isValid()) {
        insertNewVisualItems(parent, start, end, VisualItem::VisualScoreItem);
    }
    MusicItem *item = static_cast<MusicItem*>(parent.internalPointer());
    if (!item)
        return;

    if (item->type() == MusicItem::ScoreType) {
        insertNewVisualItems(parent, start, end, VisualItem::VisualTuneItem);
    }
    if (item->type() == MusicItem::TuneType) {
        insertNewVisualItems(parent, start, end, VisualItem::VisualPartItem);
    }
    if (item->type() == MusicItem::PartType) {
        insertNewVisualItems(parent, start, end, VisualItem::VisualMeasureItem);
    }
    if (item->type() == MusicItem::MeasureType) {
        insertNewVisualItems(parent, start, end, VisualItem::VisualSymbolItem);
    }
}

void VisualMusicModel::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    for (int i = topLeft.row(); i <= bottomRight.row(); i++) {
        QModelIndex index = topLeft.sibling(i, 0);
        VisualItem *item = visualItemFromIndex(index);
        if (!item)
            return;

        foreach (int role, roles) {
            item->setData(m_model->data(topLeft, role), role);
        }
    }
}

void VisualMusicModel::visualItemDataChanged(const QVariant &value, int dataRole)
{
    QObject *senderObject = sender();
    if (!senderObject)
        return;

    VisualItem *visualItem = dynamic_cast<VisualItem*>(senderObject);
    if (!visualItem)
        return;

    if (!m_visualItemIndexes.values().contains(visualItem))
        return;

    QModelIndex itemIndex = m_visualItemIndexes.key(visualItem);
    if (!itemIndex.isValid()) return;

    m_model->setData(itemIndex, value, dataRole);
}

void VisualMusicModel::itemRowSequenceChanged()
{
    QObject *senderItem = sender();
    if (!senderItem)
        return;

    VisualItem *visualItem = qobject_cast<VisualItem*>(senderItem);
    if (visualItem == 0)
        return;

    if (!visualItem->graphicalType() == VisualItem::GraphicalRowType)
        return;

    if (!m_visualItemIndexes.values().contains(visualItem))
        return;

    int scoreRow = 0;
    QPersistentModelIndex index = m_visualItemIndexes.key(visualItem);
    switch (visualItem->itemType()) {
    case VisualItem::NoVisualItem:
        break;
    case VisualItem::VisualScoreItem: {
        scoreRow = index.row();
        break;
    }
    case VisualItem::VisualTuneItem: {
        scoreRow = index.parent().row();
        break;
    }
    case VisualItem::VisualPartItem: {
        scoreRow = index.parent().parent().row();
        break;
    }
    case VisualItem::VisualMeasureItem: {
        scoreRow = index.parent().parent().parent().row();
        break;
    }
    case VisualItem::VisualSymbolItem: {
        scoreRow = index.parent().parent().parent().parent().row();
        break;
    }
    }

    emit scoreRowSequenceChanged(scoreRow);
}

void VisualMusicModel::insertNewVisualItems(const QModelIndex &index, int start, int end,
                                            VisualItem::ItemType itemType)
{
    if (!model())
        return;

    for (int i=start; i<=end; i++) {
        QPersistentModelIndex itemIndex(m_model->index(i, 0, index));
        if (itemIndex.isValid()) {
            VisualItem *visualItem = m_itemFactory->createVisualItem(itemType);
            if (visualItem == 0)
                continue;

            insertVisualItem(itemIndex, visualItem);
        }
    }
}

void VisualMusicModel::insertVisualItem(QPersistentModelIndex itemIndex, VisualItem *item)
{
    connect(item, &VisualItem::dataChanged,
            this, &VisualMusicModel::visualItemDataChanged);
    connect(item, &VisualItem::rowSequenceChanged,
            this, &VisualMusicModel::itemRowSequenceChanged);

    item->setParent(this);
    m_visualItemIndexes.insert(itemIndex, item);
}

void VisualMusicModel::setModel(QAbstractItemModel *model)
{
    m_model = model;

    connect(m_model, &QAbstractItemModel::rowsInserted,
            this, &VisualMusicModel::rowsInserted);
    connect(m_model, &QAbstractItemModel::dataChanged,
            this, &VisualMusicModel::dataChanged);
}

QAbstractItemModel *VisualMusicModel::model() const
{
    return m_model;
}

VisualItem *VisualMusicModel::visualItemFromIndex(const QModelIndex &itemIndex)
{
    if (!m_visualItemIndexes.contains(itemIndex))
        return 0;

    return m_visualItemIndexes.value(itemIndex);
}
