/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musicmodel.h"

QModelIndex MusicModel::index(int row, int column, const QModelIndex &parent) const
{
}

QModelIndex MusicModel::parent(const QModelIndex &child) const
{
}

int MusicModel::rowCount(const QModelIndex &parent) const
{
}

int MusicModel::columnCount(const QModelIndex &parent) const
{
}

QVariant MusicModel::data(const QModelIndex &index, int role) const
{
}

MusicItem *MusicModel::itemForIndex(const QModelIndex &index)
{
    if (index.isValid()) {
        if (MusicItem *item = static_cast<MusicItem*>(
                    index.internalPointer()))
            return item;
    }
    return m_rootItem;
}
