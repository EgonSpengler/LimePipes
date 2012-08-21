/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICMODEL_H
#define MUSICMODEL_H

#include <QAbstractItemModel>
#include <musicitem.h>

class MusicModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit MusicModel(QObject *parent = 0) :
        QAbstractItemModel(parent), m_rootItem(0) {}
    ~MusicModel() { delete m_rootItem; }

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    
    MusicItem *itemForIndex(const QModelIndex& index) const;

private:
    MusicItem *m_rootItem;
};

#endif // MUSICMODEL_H
