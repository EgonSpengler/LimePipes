/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QVBoxLayout>
#include <QResizeEvent>
#include <common/itemdataroles.h>
#include <musicitem.h>
#include "graphicsview.h"
#include "graphicsscene.h"
#include "pageviewitem/pageviewitem.h"
#include "visualmusicpresenter.h"
#include "visualmusicmodel/visualmusicmodel.h"
#include "graphicsitemview.h"

GraphicsItemView::GraphicsItemView(QWidget *parent)
    : QAbstractItemView(parent),
      m_graphicsScene(0),
      m_graphicsView(0),
      m_musicPresenter(0),
      m_pageView(0)
{
    m_graphicsScene = new GraphicsScene(this);
    m_graphicsView = new GraphicsView(this);
    m_musicPresenter = new VisualMusicPresenter(this);
    m_pageView = new PageViewItem();

    m_graphicsView->setScene(m_graphicsScene);
    m_musicPresenter->setPageView(m_pageView);
    m_graphicsScene->addItem(m_pageView);

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

void GraphicsItemView::setModel(QAbstractItemModel *model)
{
    if (m_musicPresenter)
        m_musicPresenter->setModel(model);

    QAbstractItemView::setModel(model);
}

void GraphicsItemView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{
}
