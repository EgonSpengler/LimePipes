/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QAbstractItemModel>
#include <musicitem.h>
#include <common/itemdataroles.h>
#include "visualmusicmodel.h"
#include "sequentialtunesrowiterator.h"

VisualMusicModel::VisualMusicModel(AbstractVisualItemFactory *itemFactory, QObject *parent)
    : QObject(parent),
      m_model(0),
      m_itemFactory(itemFactory)
{
}

VisualMusicModel::~VisualMusicModel()
{
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

void VisualMusicModel::itemRowSequenceChanged(VisualItem *visualItem)
{
    if (!(visualItem->graphicalType() == VisualItem::GraphicalRowType))
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

void VisualMusicModel::setModel(QAbstractItemModel *model)
{
    m_model = model;

    connect(m_model, &QAbstractItemModel::rowsInserted,
            this, &VisualMusicModel::rowsInserted);
    connect(m_model, &QAbstractItemModel::dataChanged,
            this, &VisualMusicModel::dataChanged);
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

void VisualMusicModel::insertNewVisualItems(const QModelIndex &parent, int start, int end,
                                            VisualItem::ItemType itemType)
{
    if (!model())
        return;

    for (int i=start; i<=end; i++) {
        QPersistentModelIndex itemIndex(m_model->index(i, 0, parent));
        if (itemIndex.isValid()) {
            VisualItem *visualItem = m_itemFactory->createVisualItem(itemType);
            if (visualItem == 0)
                continue;

            insertVisualItem(itemIndex, visualItem);
            initVisualItemData(visualItem, itemIndex);

            if (visualItem->graphicalType() == VisualItem::GraphicalRowType) {
                itemRowSequenceChanged(visualItem);
            }

            // Insert into parent Item
            if (!parent.isValid())
                continue;

            VisualItem *parentItem = visualItemFromIndex(parent);
            if (parentItem == 0)
                continue;

            parentItem->insertChildItem(i, visualItem);
        }
    }
}

void VisualMusicModel::initVisualItemData(VisualItem *visualItem, const QPersistentModelIndex& itemIndex)
{
    switch (visualItem->itemType()) {
    case VisualItem::VisualScoreItem:
        setVisualItemDataFromModel(visualItem, itemIndex, LP::ScoreTitle);
        setVisualItemDataFromModel(visualItem, itemIndex, LP::ScoreType);
        setVisualItemDataFromModel(visualItem, itemIndex, LP::ScoreComposer);
        setVisualItemDataFromModel(visualItem, itemIndex, LP::ScoreArranger);
        setVisualItemDataFromModel(visualItem, itemIndex, LP::ScoreCopyright);
        setVisualItemDataFromModel(visualItem, itemIndex, LP::ScoreYear);
        break;
    case VisualItem::VisualTuneItem:
        break;
    case VisualItem::VisualPartItem:
        setVisualItemDataFromModel(visualItem, itemIndex, LP::PartStaffType);
        setVisualItemDataFromModel(visualItem, itemIndex, LP::PartRepeat);
        break;
    case VisualItem::VisualMeasureItem:
        setVisualItemDataFromModel(visualItem, itemIndex, LP::MeasureIsUpbeat);
        break;
    case VisualItem::VisualSymbolItem:
        setVisualItemDataFromModel(visualItem, itemIndex, LP::SymbolCategory);
        setVisualItemDataFromModel(visualItem, itemIndex, LP::SymbolType);
        setVisualItemDataFromModel(visualItem, itemIndex, LP::SymbolName);
        setVisualItemDataFromModel(visualItem, itemIndex, LP::SymbolLength);
        setVisualItemDataFromModel(visualItem, itemIndex, LP::SymbolPitch);
        break;
    case VisualItem::NoVisualItem:
        break;
    }
}

void VisualMusicModel::setVisualItemDataFromModel(VisualItem *visualItem, const QPersistentModelIndex& itemIndex, int role)
{
    QVariant data = m_model->data(itemIndex, role);
    if (data.isValid()) {
        visualItem->setData(data, role);
    }
}

void VisualMusicModel::insertVisualItem(QPersistentModelIndex itemIndex, VisualItem *item)
{
    connect(item, &VisualItem::dataChanged,
            this, &VisualMusicModel::visualItemDataChanged);
    connect(item, &VisualItem::rowSequenceChanged,
            [this, item] { itemRowSequenceChanged(item); });

    item->setParent(this);
    m_visualItemIndexes.insert(itemIndex, item);
}

void VisualMusicModel::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &dataRoles)
{
    for (int i = topLeft.row(); i <= bottomRight.row(); i++) {
        QModelIndex index = topLeft.sibling(i, 0);
        VisualItem *item = visualItemFromIndex(index);
        if (!item)
            continue;

        foreach (int role, dataRoles) {
            item->setData(m_model->data(topLeft, role), role);
        }
    }
}

QAbstractItemModel *VisualMusicModel::model() const
{
    return m_model;
}

VisualItem *VisualMusicModel::visualItemFromIndex(const QModelIndex &itemIndex) const
{
    if (!m_visualItemIndexes.contains(itemIndex))
        return 0;

    return m_visualItemIndexes.value(itemIndex);
}

RowIterator VisualMusicModel::rowIteratorForScore(int index)
{
    if (m_model == 0)
        return RowIterator();

    QModelIndex scoreIndex = m_model->index(index, 0);
    if (!scoreIndex.isValid())
        return RowIterator();

    SequentialTunesRowIterator iterator(this, scoreIndex);
    return iterator;
}
