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
        : QUndoCommand(text, parent), m_model(model), m_parentIndex(parentIndex), m_row(row), m_count(count)
    { }

    void redo() {
        MusicItem *parentItem = m_parentIndex.isValid() ? m_model->itemForIndex(m_parentIndex)
                                                        : m_model->m_rootItem;

        if (!parentItem)
            return;

        m_model->beginRemoveRows(m_parentIndex, m_row, m_row + m_count - 1);
        for (int i = 0; i < m_count; ++i) {
            m_items.append(parentItem->takeChild(m_row));
        }
        m_model->endRemoveRows();
    }

    void undo() {
        MusicItem *parentItem = m_model->itemForIndex(m_parentIndex);
        if (!parentItem)
            return;

        Q_ASSERT(m_count > 0);
        m_model->beginInsertRows(m_parentIndex, m_row, m_row + m_count - 1);

        QListIterator<MusicItem*> i(m_items);
        i.toBack();
        while (i.hasPrevious()) {
            MusicItem *undoItem = i.previous();
            parentItem->insertChild(m_row, undoItem);
        }

        m_model->endInsertRows();
    }

private:
    MusicModel *m_model;
    QPersistentModelIndex m_parentIndex;
    int m_row;
    int m_count;
    QList<MusicItem*> m_items;
};

#endif // REMOVEITEMSCOMMAND_H
