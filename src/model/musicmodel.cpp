/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musicmodel.h"
#include <musicitemfactory.h>

/*! @class MusicModel
  * @brief The implementation of the QAbstractItemModel.
  */

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

bool MusicModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (!m_rootItem)
        m_rootItem = MusicItemFactory::getMusicItem(MusicItem::RootItemType);
    MusicItem *parentItem = parent.isValid() ? itemForIndex(parent)
                                            : m_rootItem;

    // Childs itemType is NoType => No insertion
    if (parentItem->childType() == MusicItem::NoItemType)
        return false;

    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++) {
        MusicItem *item = MusicItemFactory::getMusicItem(parentItem->childType());
        parentItem->insertChild(row, item);
    }
    endInsertRows();
    return true;
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
