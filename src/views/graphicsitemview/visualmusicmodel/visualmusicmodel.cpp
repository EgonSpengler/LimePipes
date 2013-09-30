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
#include "../abstractscorepropertiesholder.h"
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
        insertNewScores(parent, start, end);
    }
    MusicItem *item = static_cast<MusicItem*>(parent.internalPointer());
    if (!item) return;

    if (item->type() == MusicItem::ScoreType) {
        insertNewTunes(parent, start, end);
    }
    if (item->type() == MusicItem::TuneType) {
        insertNewParts(parent, start, end);
    }
    if (item->type() == MusicItem::PartType) {
        insertNewMeasures(parent, start, end);
    }
    if (item->type() == MusicItem::MeasureType) {
        insertNewSymbols(parent, start, end);
    }
}

void VisualMusicModel::insertNewScores(const QModelIndex &index, int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        QPersistentModelIndex itemIndex(m_model->index(i, 0, index));
        if (itemIndex.isValid()) {
            VisualScore *score = new VisualScore(this);
            m_visualScoreIndexes.insert(itemIndex, score);
            emit scoreInserted(itemIndex);
        }
    }
}

void VisualMusicModel::insertNewTunes(const QModelIndex &index, int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        QPersistentModelIndex itemIndex(m_model->index(i, 0, index));
        if (itemIndex.isValid()) {
            VisualTune *tune = new VisualTune(this);
            m_visualTuneIndexes.insert(itemIndex, tune);
            emit tuneInserted(itemIndex);
        }
    }
}

void VisualMusicModel::insertNewParts(const QModelIndex &index, int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        QPersistentModelIndex itemIndex(m_model->index(i, 0, index));
        if (itemIndex.isValid()) {
            VisualPart *part = new VisualPart(this);
            m_visualPartIndexes.insert(itemIndex, part);
            emit partInserted(itemIndex);
        }
    }
}

void VisualMusicModel::insertNewMeasures(const QModelIndex &index, int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        QPersistentModelIndex itemIndex(m_model->index(i, 0, index));
        if (itemIndex.isValid()) {
            VisualMeasure *measure = new VisualMeasure(this);
            m_visualMeasureIndexes.insert(itemIndex, measure);
            emit measureInserted(itemIndex);
        }
    }
}

void VisualMusicModel::insertNewSymbols(const QModelIndex &index, int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        QPersistentModelIndex itemIndex(m_model->index(i, 0, index));
        if (itemIndex.isValid()) {
            VisualSymbol *symbol = new VisualSymbol(this);
            m_visualSymbolIndexes.insert(itemIndex, symbol);
            emit symbolInserted(itemIndex);
        }
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

AbstractScorePropertiesHolder *VisualMusicModel::scorePropertiesHolderFromIndex(const QModelIndex &scoreIndex)
{
    if (!m_visualScoreIndexes.contains(scoreIndex))
        return 0;

    return static_cast<AbstractScorePropertiesHolder*>(m_visualScoreIndexes.value(scoreIndex));
}

VisualScoreInterface *VisualMusicModel::visualScoreFromIndex(const QModelIndex &scoreIndex)
{
    if (!m_visualScoreIndexes.contains(scoreIndex))
        return 0;

    return static_cast<VisualScoreInterface*>(m_visualScoreIndexes.value(scoreIndex));
}
