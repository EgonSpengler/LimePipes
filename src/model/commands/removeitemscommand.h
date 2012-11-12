/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef REMOVEITEMSCOMMAND_H
#define REMOVEITEMSCOMMAND_H

#include <QAbstractItemModel>
#include <QList>
#include <QModelIndex>
#include <QUndoCommand>
#include <musicitem.h>
#include <musicmodel.h>

class RemoveItemsCommand : public QUndoCommand
{
public:
    RemoveItemsCommand(MusicModel *model, const QString &text, const QModelIndex &parentIndex, int row, int count, QUndoCommand *parent = 0)
        : QUndoCommand(text, parent), m_model(model), m_parentIndex(parentIndex), m_row(row), m_removedItemCount(count), isFirstRemove(true)
    {
        m_parentItem = m_model->itemForIndex(parentIndex);
        Q_ASSERT(m_removedItemCount > 0);
    }

    void redo() {
        m_model->beginRemoveRows(m_parentIndex, m_row, m_row + m_removedItemCount - 1);
        for (int i = 0; i < m_removedItemCount; ++i) {
            MusicItem *takenChild = m_parentItem->takeChild(m_row);

            if (isFirstRemove)
                m_removedItems.append(takenChild);
        }
        m_model->endRemoveRows();
        isFirstRemove = false;
    }

    void undo() {
        Q_ASSERT(m_removedItemCount > 0);
        m_model->beginInsertRows(m_parentIndex, m_row, m_row + m_removedItemCount - 1);

        QListIterator<MusicItem*> i(m_removedItems);
        i.toBack();
        while (i.hasPrevious()) {
            MusicItem *undoItem = i.previous();
            m_parentItem->insertChild(m_row, undoItem);
        }

        m_model->endInsertRows();
    }

private:
    MusicModel *m_model;
    QPersistentModelIndex m_parentIndex;
    MusicItem *m_parentItem;
    int m_row;
    int m_removedItemCount;
    QList<MusicItem*> m_removedItems;
    bool isFirstRemove;
};

#endif // REMOVEITEMSCOMMAND_H
