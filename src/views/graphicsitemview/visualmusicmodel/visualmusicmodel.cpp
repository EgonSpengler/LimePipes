/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "../graphicsscene.h"
#include "visualmusicmodel.h"

VisualMusicModel::VisualMusicModel(QObject *parent)
    : QObject(parent),
      m_model(0),
      m_scene(0)
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

void VisualMusicModel::dataChanged(const QModelIndex& index)
{
}

void VisualMusicModel::insertMeasureIntoPart(int row, const QModelIndex &part)
{
}

void VisualMusicModel::insertPartIntoTune(int row, const QModelIndex &tune)
{
}

void VisualMusicModel::insertScore(int row, const QString &title)
{
}

void VisualMusicModel::insertSymbolIntoMeasure(int row, const QModelIndex &measure)
{
}

void VisualMusicModel::insertTuneIntoScore(int row, const QModelIndex &score)
{
}

void VisualMusicModel::rowsAboutToBeRemoved(const QModelIndex& parent, int start, int end)
{
}

void VisualMusicModel::setModel(QAbstractItemModel *model)
{
    if (m_model != 0)
        delete m_model;
    m_model = model;
}


QAbstractItemModel *VisualMusicModel::model() const
{
    return m_model;
}
