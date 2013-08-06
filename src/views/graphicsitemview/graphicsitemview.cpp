/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QVBoxLayout>
#include <QResizeEvent>
#include <itemdatatypes.h>
#include <musicitem.h>
#include <datatypes/instrument.h>
#include "graphicsview.h"
#include "visualmusicmodel/visualmusicmodel.h"
#include "graphicsitemview.h"

GraphicsItemView::GraphicsItemView(QWidget *parent)
    : QAbstractItemView(parent),
      m_graphicsView(0),
      m_visualMusicModel(0)
{
    m_graphicsView = new GraphicsView(this);
    m_visualMusicModel = new VisualMusicModel(this);

    m_graphicsView->setScene(m_visualMusicModel->scene());

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_graphicsView);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

GraphicsItemView::~GraphicsItemView()
{
}

QRect GraphicsItemView::visualRect(const QModelIndex &index) const
{
    return QRect();
}

QModelIndex GraphicsItemView::indexAt(const QPoint &point) const
{
    return QModelIndex();
}

QModelIndex GraphicsItemView::moveCursor(QAbstractItemView::CursorAction cursorAction,
        Qt::KeyboardModifiers modifiers)
{
    return QModelIndex();
}

int GraphicsItemView::horizontalOffset() const
{
    return 0;
}

int GraphicsItemView::verticalOffset() const
{
    return 0;
}

bool GraphicsItemView::isIndexHidden(const QModelIndex &index) const
{
    return false;
}

void GraphicsItemView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{
}

QRegion GraphicsItemView::visualRegionForSelection(const QItemSelection &selection) const
{
    return QRegion();
}

void GraphicsItemView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{
}

void GraphicsItemView::setVisualMusicModel(VisualMusicModelInterface *visualMusicModel)
{
    if (m_visualMusicModel != 0) {
        delete m_visualMusicModel;
    }

    m_visualMusicModel = visualMusicModel;
}

VisualMusicModelInterface *GraphicsItemView::visualMusicModel() const
{
    return m_visualMusicModel;
}

void GraphicsItemView::rowsInserted(const QModelIndex &parent, int start, int end)
{
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

void GraphicsItemView::handleInsertScores(int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        QModelIndex scoreIndex = model()->index(i, 0);
        QString scoreTitle = scoreIndex.data(LP::scoreTitle).toString();
        if (scoreTitle.isEmpty()) continue;

        m_visualMusicModel->insertScore(i, scoreTitle);
    }
}

void GraphicsItemView::handleInsertTunes(const QModelIndex &scoreIndex, int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        m_visualMusicModel->insertTuneIntoScore(i, scoreIndex);
    }
}

void GraphicsItemView::handleInsertPartIntoTune(const QModelIndex &tuneIndex, int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        m_visualMusicModel->insertPartIntoTune(i, tuneIndex);
    }
}

void GraphicsItemView::handleInsertMeasureIntoPart(const QModelIndex &partIndex, int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        m_visualMusicModel->insertMeasureIntoPart(i, partIndex);
    }
}

void GraphicsItemView::handleInsertSymbolIntoMeasure(const QModelIndex &measureIndex, int start, int end)
{
    if (!model()) return;
    for (int i=start; i<=end; i++) {
        m_visualMusicModel->insertSymbolIntoMeasure(i, measureIndex);
    }
}

