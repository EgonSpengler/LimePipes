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
#include "abstractvisualitem.h"
#include "visualmusicmodelinterface.h"

class GraphicsScene;
class VisualRootItem;

class VisualMusicModel : public QObject,
                         public VisualMusicModelInterface
{
    Q_OBJECT

    friend class VisualMusicModelTest;

public:
    explicit VisualMusicModel(QObject *parent=0);
    virtual ~VisualMusicModel();

    QGraphicsScene *scene();
    void setModel(QAbstractItemModel *model);
    QAbstractItemModel *model() const;

private slots:
    void rowsInserted(const QModelIndex &parent, int start, int end);

private:
    void createRootItemIfNotPresent();
    template <class T>
    void insertNewItemsIntoHash(const QModelIndex& index, int start, int end,
                                QHash<QPersistentModelIndex, AbstractVisualItem*>& hash);
    QAbstractItemModel *m_model;
    GraphicsScene *m_scene;
    VisualRootItem *m_rootItem;
    QHash<QPersistentModelIndex, AbstractVisualItem*> m_visualScoreIndexes;
    QHash<QPersistentModelIndex, AbstractVisualItem*> m_visualTuneIndexes;
    QHash<QPersistentModelIndex, AbstractVisualItem*> m_visualPartIndexes;
    QHash<QPersistentModelIndex, AbstractVisualItem*> m_visualMeasureIndexes;
    QHash<QPersistentModelIndex, AbstractVisualItem*> m_visualSymbolIndexes;
};

#endif // VISUALMUSICMODEL_H_7R3SY07L
