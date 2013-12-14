/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */
#ifndef VISUALMUSICMODEL_H_7R3SY07L
#define VISUALMUSICMODEL_H_7R3SY07L

#include <QObject>
#include <QHash>
#include <QPersistentModelIndex>
#include "visualitem.h"
#include "rowiterator.h"
#include "abstractvisualitemfactory.h"

class VisualMusicModel : public QObject
{
    Q_OBJECT

    friend class VisualMusicModelTest;
    friend class RowIterator;

public:
    explicit VisualMusicModel(AbstractVisualItemFactory *itemFactory, QObject *parent=0);
    virtual ~VisualMusicModel();

    void setModel(QAbstractItemModel *model);
    QAbstractItemModel *model() const;

    RowIterator rowIteratorForScore(int index);

signals:
    void scoreRowSequenceChanged(int scoreIndex);

private slots:
    void rowsInserted(const QModelIndex &parent, int start, int end);
    void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& dataRoles);
    void visualItemDataChanged(const QVariant& value, int dataRole);
    void itemRowSequenceChanged();

private:
    VisualItem *visualItemFromIndex(const QModelIndex& itemIndex) const;
    void insertNewVisualItems(const QModelIndex& index, int start, int end, VisualItem::ItemType itemType);
    void insertVisualItem(QPersistentModelIndex itemIndex, VisualItem *item);
    QAbstractItemModel *m_model;
    QHash<QPersistentModelIndex, VisualItem*> m_visualItemIndexes;
    AbstractVisualItemFactory *m_itemFactory;
};

#endif // VISUALMUSICMODEL_H_7R3SY07L
