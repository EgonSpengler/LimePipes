/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QAbstractItemModel>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QDebug>
#include <musicitem.h>
#include <common/itemdataroles.h>
#include "interactinggraphicsitems/interactinggraphicsitem.h"
#include "visualmusicmodel.h"
#include "sequentialtunesrowiterator.h"

#include <QDebug>

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
    connect(m_model, &QAbstractItemModel::rowsAboutToBeRemoved,
            this, &VisualMusicModel::rowsAboutToBeRemoved);
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

void VisualMusicModel::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
    for (int i=start; i<=end; i++) {
        QModelIndex itemIndex = m_model->index(i, 0, parent);
        if (!itemIndex.isValid())
            continue;

        VisualItem *item = m_visualItemIndexes.value(itemIndex);
        if (!item)
            continue;

        // If no valid parent index => Score was removed
        if (!parent.isValid()) {
            item->removeAllRows();
        } else {
            VisualItem *parentItem = m_visualItemIndexes.value(parent);

            if (item->graphicalType() == VisualItem::GraphicalRowType) {
                for (int i = 0; i < item->rowCount(); ++i) {
                    item->removeLastRow();
                }
            } else {
                if (!parentItem)
                    continue;

                parentItem->removeChildItem(item);
                item->removeInlineGraphic();
            }
        }

        m_visualItemIndexes.remove(itemIndex);
        item->deleteLater();
    }
}

void VisualMusicModel::insertNewVisualItems(const QModelIndex &parentIndex, int start, int end,
                                            VisualItem::ItemType itemType)
{
    if (!model())
        return;

    for (int i=start; i<=end; i++) {
        QPersistentModelIndex itemIndex(m_model->index(i, 0, parentIndex));
        if (itemIndex.isValid()) {
            VisualItem *visualItem = 0;
            if (itemType == VisualItem::VisualSymbolItem) {
                QVariant data = m_model->data(itemIndex, LP::SymbolType);
                int symbolType = data.toInt();
                visualItem = m_itemFactory->createVisualSymbol(symbolType);

            } else {
                visualItem = m_itemFactory->createVisualItem(itemType);
            }
            if (visualItem == 0)
                continue;

            insertVisualItem(itemIndex, visualItem);
            initVisualItemData(visualItem, itemIndex);

            if (visualItem->graphicalType() == VisualItem::GraphicalRowType) {
                itemRowSequenceChanged(visualItem);
            }

            // Insert into parent Item
            if (!parentIndex.isValid())
                continue;

            VisualItem *parentItem = visualItemFromIndex(parentIndex);
            if (parentItem == 0)
                continue;

            parentItem->insertChildItem(i, visualItem);

//            debugInsertion(parentIndex, i, parentItem, visualItem);
        }
    }
}

QString VisualMusicModel::visualItemTypeToString(const VisualItem::ItemType itemType) const
{
    QString itemTypeName;
    switch (itemType) {
    case VisualItem::NoVisualItem:
        break;
    case VisualItem::VisualScoreItem:
        itemTypeName = QStringLiteral("Score");
        break;
    case VisualItem::VisualTuneItem:
        itemTypeName = QStringLiteral("Tune");
        break;
    case VisualItem::VisualPartItem:
        itemTypeName = QStringLiteral("Part");
        break;
    case VisualItem::VisualMeasureItem:
        itemTypeName = QStringLiteral("Measure");
        break;
    case VisualItem::VisualSymbolItem:
        itemTypeName = QStringLiteral("Symbol");
        break;
    }

    return itemTypeName;
}

QRectF VisualMusicModel::sceneBoundingRectForIndex(const QModelIndex &index) const
{
    VisualItem *item = visualItemFromIndex(index);
    if (item == 0)
        return QRectF();

    if (item->itemType() == VisualItem::VisualMeasureItem ||
            item->graphicalType() == VisualItem::GraphicalRowType)
        return QRectF();

    if (item->graphicalType() == VisualItem::GraphicalInlineType) {
        InteractingGraphicsItem *graphicsItem = item->inlineGraphic();
        if (!graphicsItem)
            return QRect();

        return graphicsItem->mapToScene(graphicsItem->boundingRect()).boundingRect();
    }
//    if (item->graphicalType() == VisualItem::GraphicalRowType) {
//        QList<InteractingGraphicsItem*> interactingGraphicsItems(item->rowGraphics());
//        if (interactingGraphicsItems.isEmpty())
//            return QRectF();

//        QGraphicsScene *scene = interactingGraphicsItems.at(0)->scene();
//        if (scene == 0)
//            return QRectF();

//        QList<QGraphicsItem*> items;
//        foreach (InteractingGraphicsItem *interactingItem, interactingGraphicsItems) {
//            QGraphicsItem *item = static_cast<QGraphicsItem*>(interactingItem);
//            if (item) {
//                items << item;
//            }
//        }

//        QGraphicsItemGroup *itemGroup = scene->createItemGroup(items);
//        QRectF boundingRect = itemGroup->boundingRect();
//        scene->destroyItemGroup(itemGroup);

//        return boundingRect;
//    }

    return QRectF();
}

QModelIndex VisualMusicModel::indexForItem(QGraphicsItem *item) const
{
    foreach (VisualItem *visualItem, m_visualItemIndexes) {
        if (visualItem->hasGraphicsItem(item)) {
            qDebug() << "Index for item : " << visualItemTypeToString(visualItem->itemType());

            return m_visualItemIndexes.key(visualItem);
        }
    }

    return QModelIndex();
}

void VisualMusicModel::setCurrent(const QModelIndex &current)
{
    VisualItem *visualItem = m_visualItemIndexes.value(current);
    if (!visualItem)
        return;

    if (visualItem->graphicalType() == VisualItem::GraphicalInlineType) {
        InteractingGraphicsItem *interactingItem = visualItem->inlineGraphic();
        if (!interactingItem)
            return;

        interactingItem->setFocus();
    }
}

void VisualMusicModel::debugInsertion(const QModelIndex &parentIndex, int indexPos,
                                      const VisualItem *parentItem, const VisualItem *childItem)
{
    QString itemType = visualItemTypeToString(childItem->itemType());
    QString parentType = visualItemTypeToString(parentItem->itemType());

    qDebug() << QString("Insertion of new %1 item into %2. row of %3: ")
             .arg(itemType)
             .arg(parentIndex.row())
             .arg(parentType)
             << '\n'
             << parentType << " model index: " << parentIndex << '\n'
             << itemType << " model index: "  << m_model->index(indexPos, 0, parentIndex) << '\n'
             << "Insert position: "    << indexPos << '\n'
             << "Visual parent item: " << parentItem << '\n'
             << "Parent inline graphic: " << parentItem->inlineGraphic() << '\n'
             << "Visual child item:"   << childItem << '\n'
             << "Child inline graphic: " << childItem->inlineGraphic() << '\n'
             << "End of insert" << '\n';
}

void VisualMusicModel::initVisualItemData(VisualItem *visualItem, const QPersistentModelIndex& itemIndex)
{
    switch (visualItem->itemType()) {
    case VisualItem::VisualScoreItem:
        foreach (LP::ScoreDataRole dataRole, LP::allScoreDataRoles) {
            setVisualItemDataFromModel(visualItem, itemIndex, dataRole);
        }
        break;
    case VisualItem::VisualTuneItem:
        foreach (LP::TuneDataRole dataRole, LP::allTuneDataRoles) {
            setVisualItemDataFromModel(visualItem, itemIndex, dataRole);
        }
        break;
    case VisualItem::VisualPartItem:
        foreach (LP::PartDataRole dataRole, LP::allPartDataRoles) {
            setVisualItemDataFromModel(visualItem, itemIndex, dataRole);
        }
        break;
    case VisualItem::VisualMeasureItem:
        foreach (LP::MeasureDataRole dataRole, LP::allMeasureDataRoles) {
            setVisualItemDataFromModel(visualItem, itemIndex, dataRole);
        }
        break;
    case VisualItem::VisualSymbolItem: {
        foreach (LP::SymbolDataRole dataRole, LP::allSymbolDataRoles) {
            setVisualItemDataFromModel(visualItem, itemIndex, dataRole);
        }

        if (!hasValidPluginManager()) {
            qWarning() << "VisualMusicModel: Can't set additional symbol data on new symbol."
                          " No plugin manager was set";
            break;
        }

        int symbolType = m_model->data(itemIndex, LP::SymbolType).toInt();
        if (symbolType == LP::NoSymbolType) {
            qWarning() << "VisualMusicModel: Can't set an empty symbol type";
            break;
        }

        QVector<int> additionalDataRoles;
        additionalDataRoles = m_pluginManager->additionalDataForSymbolType(symbolType);
        for (int i = 0; i < additionalDataRoles.count(); ++i) {
            setVisualItemDataFromModel(visualItem, itemIndex, additionalDataRoles.at(i));
        }

        break;
    }
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

RowIterator *VisualMusicModel::rowIteratorForScore(int index)
{
    if (m_model == 0)
        return new RowIterator();

    QModelIndex scoreIndex = m_model->index(index, 0);
    if (!scoreIndex.isValid())
        return new RowIterator();

    SequentialTunesRowIterator *iterator = new SequentialTunesRowIterator(this, scoreIndex);
    return iterator;
}

void VisualMusicModel::setPluginManager(PluginManager pluginManager)
{
    m_pluginManager = pluginManager;
}

PluginManager VisualMusicModel::pluginManager() const
{
    return m_pluginManager;
}

bool VisualMusicModel::hasValidPluginManager() const
{
    return !m_pluginManager.isNull();
}
