/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef INSERTITEMSCOMMAND_H
#define INSERTITEMSCOMMAND_H

#include <QAbstractItemModel>
#include <QList>
#include <QModelIndex>
#include <QUndoCommand>
#include <musicitem.h>
#include <musicmodel.h>

class InsertItemsCommand : public QUndoCommand
{
public:
    InsertItemsCommand(MusicModel *model, const QString &text, const QModelIndex &parentIndex, int row, const QList<MusicItem*> &items, QUndoCommand *parent = 0)
        : QUndoCommand(text, parent), m_model(model), m_parentIndex(parentIndex), m_row(row), m_items(items)
    {
        Q_ASSERT(m_row >= 0);
        Q_ASSERT(m_items.count());
        m_parentItem = m_model->itemForIndex(parentIndex);
    }

    void redo() {
        Q_ASSERT(m_items.count());
        Q_ASSERT(m_parentItem->childType() == m_items.at(0)->type());

        QListIterator<MusicItem*> i(m_items);
        i.toBack();

        m_model->beginInsertRows(m_parentIndex, m_row, m_row + m_items.count() - 1);
        while (i.hasPrevious()) {
            MusicItem *newItem = i.previous();
            m_parentItem->insertChild(m_row, newItem);
        }
        m_model->endInsertRows();
    }

    void undo() {
        Q_ASSERT(m_parentItem->childCount() >= m_row + m_items.count());
        m_model->beginRemoveRows(m_parentIndex, m_row, m_row + m_items.count() - 1);
        for (int i = 0; i < m_items.count(); ++i) {
            MusicItem *takenChild = m_parentItem->takeChild(m_row);
            Q_ASSERT(m_items.at(i) == takenChild);
        }
        m_model->endRemoveRows();
    }

private:
    MusicModel *m_model;
    QPersistentModelIndex m_parentIndex;
    int m_row;
    MusicItem *m_parentItem;
    QList<MusicItem*> m_items;
};

#endif // INSERTITEMSCOMMAND_H
