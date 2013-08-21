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
        handleInsertScores(start, end);
    }
    MusicItem *item = static_cast<MusicItem*>(parent.internalPointer());
    if (!item) return;

    if (item->type() == MusicItem::ScoreType) {
        handleInsertTunes(parent, start, end);
    }
    if (item->type() == MusicItem::TuneType) {
        handleInsertPartIntoTune(parent, start, end);
    }
    if (item->type() == MusicItem::PartType) {
        handleInsertMeasureIntoPart(parent, start, end);
    }
    if (item->type() == MusicItem::MeasureType) {
        handleInsertSymbolIntoMeasure(parent, start, end);
    }
}

void VisualMusicModel::createRootItemIfNotPresent()
{
    if (m_rootItem == 0)
        m_rootItem = new VisualRootItem();
}

void VisualMusicModel::handleInsertScores(int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        QPersistentModelIndex scoreIndex(m_model->index(i, 0));
        if (scoreIndex.isValid()) {
            VisualScore *score = new VisualScore();
            m_visualScoreIndexes.insert(scoreIndex, score);
        }
    }
}

void VisualMusicModel::handleInsertTunes(const QModelIndex &scoreIndex, int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        QPersistentModelIndex tuneIndex(m_model->index(i, 0, scoreIndex));
        if (tuneIndex.isValid()) {
            VisualTune *tune = new VisualTune();
            m_visualTuneIndexes.insert(tuneIndex, tune);
        }
    }
}

void VisualMusicModel::handleInsertPartIntoTune(const QModelIndex &tuneIndex, int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        QPersistentModelIndex partIndex(m_model->index(i, 0, tuneIndex));
        if (partIndex.isValid()) {
            VisualPart *part = new VisualPart();
            m_visualPartIndexes.insert(partIndex, part);
        }
    }
}

void VisualMusicModel::handleInsertMeasureIntoPart(const QModelIndex &partIndex, int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
    }
}

void VisualMusicModel::handleInsertSymbolIntoMeasure(const QModelIndex &measureIndex, int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
    }
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
