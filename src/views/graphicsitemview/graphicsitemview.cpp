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
#include <QScrollArea>
#include <QGraphicsView>
#include <QDebug>
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
    : QWidget(parent),
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
    m_graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
//    m_graphicsView->setInteractive(false);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_graphicsView);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    m_visualItemFactory = new VisualItemFactory();
    m_visualMusicModel = new VisualMusicModel(m_visualItemFactory, this);
    m_musicPresenter = new VisualMusicPresenter(this);
    m_musicPresenter->setVisualMusicModel(m_visualMusicModel);
    m_graphicsScene->setVisualMusicModel(m_visualMusicModel);

    m_graphicsView->setScene(m_graphicsScene);
    m_musicPresenter->setPageView(m_pageView);
    m_graphicsScene->addItem(m_pageView);
}

GraphicsItemView::~GraphicsItemView()
{
    delete m_visualItemFactory;
}

void GraphicsItemView::setModel(QAbstractItemModel *model)
{
    if (m_visualMusicModel->model() != model &&
            model != 0) {
         m_visualMusicModel->setModel(model);
    }
}

void GraphicsItemView::setPluginManager(PluginManager pluginManager)
{
    m_visualItemFactory->setPluginManager(pluginManager);
    m_visualMusicModel->setPluginManager(pluginManager);
}

void GraphicsItemView::scale(qreal level)
{
    if (level == 0)
        return;

    // Asuming, that the graphics view has no other
    // transformations applied
    m_graphicsView->setTransform(QTransform::fromScale(level, level));
}

void GraphicsItemView::setApplication(const Application &application)
{
    m_graphicsScene->setApplication(application);
}

