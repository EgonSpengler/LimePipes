/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QFrame>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QScrollBar>
#include <common/itemdataroles.h>
#include <musicitem.h>
#include <visualmusicmodel/visualmusicmodel.h>
#include <visualmusicmodel/visualitemfactory.h>
#include <visualmusicmodel/interactinggraphicsitems/interactinggraphicsitem.h>
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
      m_pageView(0),
      m_visualMusicModel(0),
      m_visualItemFactory(0)
{
    m_pageView = new PageViewItem();

    m_graphicsScene = new GraphicsScene(this);
    m_graphicsView = new GraphicsView(this);
    QFrame *viewPortWidget = new QFrame();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_graphicsView);
    layout->setContentsMargins(0, 0, 0, 0);
    viewPortWidget->setLayout(layout);
    setViewport(viewPortWidget);

    m_visualItemFactory = new VisualItemFactory();
    m_visualMusicModel = new VisualMusicModel(m_visualItemFactory, this);
    m_musicPresenter = new VisualMusicPresenter(this);
    m_musicPresenter->setVisualMusicModel(m_visualMusicModel);

    m_graphicsView->setScene(m_graphicsScene);
    m_musicPresenter->setPageView(m_pageView);
    m_graphicsScene->addItem(m_pageView);

}

GraphicsItemView::~GraphicsItemView()
{
    delete m_visualItemFactory;
}

QRect GraphicsItemView::visualRect(const QModelIndex &index) const
{
    QRectF sceneRect = m_visualMusicModel->sceneBoundingRectForIndex(index);
    return m_graphicsView->mapFromScene(sceneRect).boundingRect();
}

QModelIndex GraphicsItemView::indexAt(const QPoint &point) const
{
    QPointF scenePoint = m_graphicsView->mapToScene(point);

    return m_visualMusicModel->indexAt(scenePoint);
}

QModelIndex GraphicsItemView::moveCursor(QAbstractItemView::CursorAction cursorAction,
        Qt::KeyboardModifiers modifiers)
{
    return QModelIndex();
}

int GraphicsItemView::horizontalOffset() const
{
    return m_graphicsView->horizontalScrollBar()->value();
}

int GraphicsItemView::verticalOffset() const
{
    return m_graphicsView->verticalScrollBar()->value();
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
    if (m_visualMusicModel->model() != model &&
            model != 0)
         m_visualMusicModel->setModel(model);

    QAbstractItemView::setModel(model);
}

void GraphicsItemView::setPluginManager(PluginManager pluginManager)
{
    m_visualItemFactory->setPluginManager(pluginManager);
}

void GraphicsItemView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{
}
