/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
 * @class MusicModel
 * @brief The implementation of the QAbstractItemModel.
 */

#include "musicmodel.h"
#include <rootitem.h>
#include <score.h>
#include <tune.h>

namespace {
const int ColumnCount = 1;
}

QModelIndex MusicModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!m_rootItem || row < 0 || column < 0 || column >= ColumnCount
            || (parent.isValid() && parent.column() != 0))
        return QModelIndex();
    MusicItem *parentItem = itemForIndex(parent);
    Q_ASSERT(parentItem);
    if (MusicItem *item = parentItem->childAt(row))
        return createIndex(row, column, item);
    return QModelIndex();
}

QModelIndex MusicModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();
    if (MusicItem *childItem = itemForIndex(index)) {
        if (MusicItem *parentItem = childItem->parent()) {
            if (parentItem == m_rootItem)
                return QModelIndex();
            if (MusicItem *grandParentItem = parentItem->parent()) {
                int row = grandParentItem->rowOfChild(parentItem);
                return createIndex(row, 0, parentItem);
            }
        }
    }
    return QModelIndex();
}

int MusicModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    MusicItem *parentItem = itemForIndex(parent);
    return parentItem ? parentItem->childCount() : 0;
}

int MusicModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() && parent.column() != 0 ? 0 : ColumnCount;
}

QVariant MusicModel::data(const QModelIndex &index, int role) const
{
    if (!m_rootItem || !index.isValid() || index.column() < 0 ||
            index.column() >= ColumnCount)
        return QVariant();
    if (MusicItem *item = itemForIndex(index))
        return item->data(role);
    return QVariant();
}

QModelIndex MusicModel::insertScore(int row, const QString &title)
{
    createRootItemIfNotPresent();
    Q_ASSERT(m_rootItem->childType() == MusicItem::ScoreType);

    return insertItem(row, QModelIndex(), new Score(title));
}

QModelIndex MusicModel::insertTuneIntoScore(int row, const QModelIndex &score, Instrument *instrument)
{
    return insertItem(row, score, new Tune(instrument));
}

QModelIndex MusicModel::insertTuneWithScore(int rowOfScore, const QString &scoreTitle, Instrument *instrument)
{
    QModelIndex score = insertScore(rowOfScore, scoreTitle);
    return insertTuneIntoScore(0, score, instrument);
}

QModelIndex MusicModel::insertSymbol(int row, const QModelIndex &tune, Symbol *symbol)
{
    return insertItem(row, tune, symbol);
}

bool MusicModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.column() != 0)
        return false;
    if (MusicItem *item = itemForIndex(index)) {
        item->setData(value, role);
        return true;
    }
    return false;
}

MusicItem *MusicModel::itemForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (MusicItem *item = static_cast<MusicItem*>(
                    index.internalPointer()))
            return item;
    }
    return m_rootItem;
}

void MusicModel::createRootItemIfNotPresent()
{
    if (!m_rootItem)
        m_rootItem = new RootItem();
}

bool MusicModel::isRowValid(MusicItem *item, int row) const
{
    if (row >= 0 &&
        row <= item->childCount()) {
        return true;
    }
    return false;
}

QModelIndex MusicModel::insertItem(int row, const QModelIndex &parent, MusicItem *item)
{
    if (MusicItem *parentItem = itemForIndex(parent)) {
        if (isRowValid(parentItem, row)) {
            beginInsertRows(parent, row, row);
            parentItem->insertChild(row, item);
            endInsertRows();
            return index(row, 0, parent);
        }
    }
    return QModelIndex();
}
