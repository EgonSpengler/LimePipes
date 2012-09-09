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
#include <symbol.h>
#include "datatypes/instrument.h"

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
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    QModelIndex insertScore(int row, const QString &title);
    QModelIndex insertTuneIntoScore(int row, const QModelIndex &score, Instrument *instrument);
    QModelIndex insertTuneWithScore(int rowOfScore, const QString &scoreTitle, Instrument *instrument);
    QModelIndex insertSymbol(int row, const QModelIndex &tune, Symbol *symbol);
    
    MusicItem *itemForIndex(const QModelIndex& index) const;
    void clear();

private:
    MusicItem *m_rootItem;
    void createRootItemIfNotPresent();
    bool isRowValid(MusicItem *item, int row) const;
    QModelIndex insertItem(int row, const QModelIndex &parent, MusicItem *item);
};

#endif // MUSICMODEL_H
