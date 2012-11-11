/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef INSERTITEMCOMMAND_H
#define INSERTITEMCOMMAND_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QUndoCommand>
#include <musicitem.h>
#include <musicmodel.h>

class InsertItemCommand : public QUndoCommand
{
public:
    InsertItemCommand(MusicModel *model, const QString &text, const QModelIndex &parentIndex, int row, MusicItem *item, QUndoCommand *parent = 0)
        : QUndoCommand(text, parent), m_model(model), m_parentIndex(parentIndex), m_row(row), m_item(item)
    {
        m_parentItem = m_model->itemForIndex(parentIndex);
    }

    void redo() {
        Q_ASSERT(m_parentItem->childType() == m_item->type());
        m_model->beginInsertRows(m_parentIndex, m_row, m_row);
        m_parentItem->insertChild(m_row, m_item);
        m_model->endInsertRows();
    }

    void undo() {
        m_model->beginRemoveRows(m_parentIndex, m_row, m_row);
        MusicItem *takenChild = m_parentItem->takeChild(m_row);
        Q_ASSERT(m_item == takenChild);
        m_model->endRemoveRows();
    }

private:
    MusicModel *m_model;
    QPersistentModelIndex m_parentIndex;
    int m_row;
    MusicItem *m_parentItem;
    MusicItem *m_item;
};

#endif // INSERTITEMCOMMAND_H
