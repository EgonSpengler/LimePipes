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
    void handleInsertScores(int start, int end);
    void handleInsertTunes(const QModelIndex& scoreIndex, int start, int end);
    void handleInsertPartIntoTune(const QModelIndex& tuneIndex, int start, int end);
    void handleInsertMeasureIntoPart(const QModelIndex& partIndex, int start, int end);
    void handleInsertSymbolIntoMeasure(const QModelIndex& measureIndex, int start, int end);
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
