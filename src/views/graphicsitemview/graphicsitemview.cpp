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
#include "graphicsscene.h"
#include "visualmusicmodel/visualmusicmodel.h"
#include "graphicsitemview.h"

GraphicsItemView::GraphicsItemView(QWidget *parent)
    : QAbstractItemView(parent),
      m_graphicsScene(0),
      m_graphicsView(0)
{
    m_graphicsScene = new GraphicsScene(this);
    m_graphicsView = new GraphicsView(this);

    m_graphicsView->setScene(m_graphicsScene);

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
