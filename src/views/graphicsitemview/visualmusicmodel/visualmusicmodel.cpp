/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QAbstractItemModel>
#include <musicitem.h>
#include <views/graphicsitemview/visualmusicmodel/visualscore.h>
#include <views/graphicsitemview/visualmusicmodel/visualtune.h>
#include <views/graphicsitemview/visualmusicmodel/visualpart.h>
#include <views/graphicsitemview/visualmusicmodel/visualmeasure.h>
#include <views/graphicsitemview/visualmusicmodel/visualsymbol.h>
#include "../graphicsscene.h"
#include "visualrootitem.h"
#include "visualmusicmodel.h"

VisualMusicModel::VisualMusicModel(QObject *parent)
    : QObject(parent),
      m_model(0),
      m_scene(0),
      m_rootItem(0)
{
    m_scene = new GraphicsScene(this);
}

VisualMusicModel::~VisualMusicModel()
{
}

QGraphicsScene *VisualMusicModel::scene()
{
    return m_scene;
}

void VisualMusicModel::rowsInserted(const QModelIndex &parent, int start, int end)
{
    createRootItemIfNotPresent();

    if (!parent.isValid()) {
        insertNewItemsIntoHash<VisualScore>(parent, start, end, m_visualScoreIndexes);
    }
    MusicItem *item = static_cast<MusicItem*>(parent.internalPointer());
    if (!item) return;

    if (item->type() == MusicItem::ScoreType) {
        insertNewItemsIntoHash<VisualTune>(parent, start, end, m_visualTuneIndexes);
    }
    if (item->type() == MusicItem::TuneType) {
        insertNewItemsIntoHash<VisualPart>(parent, start, end, m_visualPartIndexes);
    }
    if (item->type() == MusicItem::PartType) {
        insertNewItemsIntoHash<VisualMeasure>(parent, start, end, m_visualMeasureIndexes);
    }
    if (item->type() == MusicItem::MeasureType) {
        insertNewItemsIntoHash<VisualSymbol>(parent, start, end, m_visualSymbolIndexes);
    }
}

void VisualMusicModel::createRootItemIfNotPresent()
{
    if (m_rootItem == 0)
        m_rootItem = new VisualRootItem();
}

void VisualMusicModel::setModel(QAbstractItemModel *model)
{
    m_model = model;

    connect(m_model, SIGNAL(rowsInserted(QModelIndex, int, int)),
            this, SLOT(rowsInserted(QModelIndex,int,int)));
}


QAbstractItemModel *VisualMusicModel::model() const
{
    return m_model;
}

template <class T>
void VisualMusicModel::insertNewItemsIntoHash(const QModelIndex &index, int start, int end,
                                              QHash<QPersistentModelIndex, AbstractVisualItem *> &hash)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        QPersistentModelIndex itemIndex(m_model->index(i, 0, index));
        if (itemIndex.isValid()) {
            T *item = new T();
            hash.insert(itemIndex, item);
        }
    }
}
