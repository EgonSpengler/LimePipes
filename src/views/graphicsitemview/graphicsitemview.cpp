/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "graphicsitemview.h"
#include "graphicsscene.h"
#include "graphicsview.h"
#include <QResizeEvent>
#include <QVBoxLayout>

GraphicsItemView::GraphicsItemView(QWidget *parent) :
    QAbstractItemView(parent)
{
    m_scene = new GraphicsScene(this);
    m_view = new GraphicsView(m_scene);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_view);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

QRect GraphicsItemView::visualRect(const QModelIndex &index) const
{
    return QRect();
}

QModelIndex GraphicsItemView::indexAt(const QPoint &point) const
{
    return QModelIndex();
}

QModelIndex GraphicsItemView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
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
