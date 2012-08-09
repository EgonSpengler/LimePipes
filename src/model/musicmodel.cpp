#include "musicmodel.h"

MusicModel::MusicModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

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
