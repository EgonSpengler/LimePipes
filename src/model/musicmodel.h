#ifndef MUSICMODEL_H
#define MUSICMODEL_H

#include <QAbstractItemModel>

class MusicModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit MusicModel(QObject *parent = 0);

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    
signals:
    
public slots:
    
};

#endif // MUSICMODEL_H
