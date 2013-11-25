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
#include "interactinggraphicsitems/scoregraphicsitem.h"
#include "iteminteractions/scoreinteraction.h"
#include <views/graphicsitemview/visualmusicmodel/visualtune.h>
#include <views/graphicsitemview/visualmusicmodel/visualpart.h>
#include <views/graphicsitemview/visualmusicmodel/visualmeasure.h>
#include <views/graphicsitemview/visualmusicmodel/visualsymbol.h>
#include "../graphicsscene.h"
#include "visualmusicmodel.h"

VisualMusicModel::VisualMusicModel(QObject *parent)
    : QObject(parent),
      m_model(0)
{
}

VisualMusicModel::~VisualMusicModel()
{
}

void VisualMusicModel::rowsInserted(const QModelIndex &parent, int start, int end)
{
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

void VisualMusicModel::scoreDataChanged(const QVariant &value, int dataRole)
{
    QObject *senderObject = sender();
    if (!senderObject) return;

    VisualScore *score = dynamic_cast<VisualScore*>(senderObject);
    if (!score) return;

    if (!m_visualItemIndexes.values().contains(score)) return;
    QModelIndex scoreIndex = m_visualItemIndexes.key(score);
    if (!scoreIndex.isValid()) return;

    m_model->setData(scoreIndex, value, dataRole);
}

void VisualMusicModel::itemRowSequenceChanged()
{
    QObject *senderItem = sender();
    if (!senderItem) return;

    VisualItem *visualItem = qobject_cast<VisualItem*>(senderItem);
    if (visualItem == 0) return;

    if (!visualItem->graphicalType() == VisualItem::GraphicalRowType)
        return;

    if (!m_visualItemIndexes.values().contains(visualItem))
        return;

    int scoreRow = 0;
    QPersistentModelIndex index = m_visualItemIndexes.key(visualItem);
    switch (visualItem->itemType()) {
    case VisualItem::NoVisualItem:
        break;
    case VisualItem::VisualScoreItem: {
        scoreRow = index.row();
        break;
    }
    case VisualItem::VisualTuneItem: {
        scoreRow = index.parent().row();
        break;
    }
    case VisualItem::VisualPartItem: {
        scoreRow = index.parent().parent().row();
        break;
    }
    case VisualItem::VisualMeasureItem: {
        scoreRow = index.parent().parent().parent().row();
        break;
    }
    case VisualItem::VisualSymbolItem: {
        scoreRow = index.parent().parent().parent().parent().row();
        break;
    }
    }

    emit scoreRowSequenceChanged(scoreRow);
}

void VisualMusicModel::insertVisualItem(QPersistentModelIndex itemIndex, VisualItem *item)
{
    connect(item, &VisualItem::rowSequenceChanged,
            this, &VisualMusicModel::itemRowSequenceChanged);
    m_visualItemIndexes.insert(itemIndex, item);
}

void VisualMusicModel::insertNewScores(const QModelIndex &index, int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        QPersistentModelIndex itemIndex(m_model->index(i, 0, index));
        if (itemIndex.isValid()) {
            VisualScore *score = new VisualScore(this);

            ScoreGraphicsItem *scoreHeaderItem = new ScoreGraphicsItem();
            scoreHeaderItem->setItemInteraction(new ScoreInteraction);
            scoreHeaderItem->setItemPosition(LP::ScoreType, 0, TextRowWidget::Left);
            scoreHeaderItem->setItemPosition(LP::ScoreTitle, 0, TextRowWidget::Center);
            QFont font;
            font.setPointSize(16);
            scoreHeaderItem->setItemFont(LP::ScoreTitle, font);
            scoreHeaderItem->setItemPosition(LP::ScoreComposer, 0, TextRowWidget::Right);
            scoreHeaderItem->setItemPosition(LP::ScoreArranger, 1, TextRowWidget::Right);
            score->setHeaderItem(scoreHeaderItem);

            ScoreGraphicsItem *scoreFooterItem = new ScoreGraphicsItem();
            scoreFooterItem->setItemPosition(LP::ScoreYear, 0, TextRowWidget::Left);
            scoreFooterItem->setItemPosition(LP::ScoreCopyright, 0, TextRowWidget::Right);
            scoreFooterItem->setItemInteraction(new ScoreInteraction);

            connect(score, SIGNAL(dataChanged(QVariant,int)),
                    this, SLOT(scoreDataChanged(QVariant,int)));
            insertVisualItem(itemIndex, score);
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
            insertVisualItem(itemIndex, tune);
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
            insertVisualItem(itemIndex, part);
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
            insertVisualItem(itemIndex, measure);
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
            insertVisualItem(itemIndex, symbol);
        }
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

VisualItem *VisualMusicModel::visualItemFromIndex(const QModelIndex &scoreIndex)
{
    if (!m_visualItemIndexes.contains(scoreIndex))
        return 0;

    return m_visualItemIndexes.value(scoreIndex);
}
