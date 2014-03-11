/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualmusicmodel/visualmusicmodel.h"
#include "visualmusicmodel/visualitemfactory.h"
#include "visualmusicpresenter.h"

VisualMusicPresenter::VisualMusicPresenter(QObject *parent)
    : QObject(parent),
      m_pageView(0),
      m_visualMusicModel(0),
      m_itemFactory(0)
{
    m_itemFactory = new VisualItemFactory();
    m_visualMusicModel = new VisualMusicModel(m_itemFactory, this);

    createConnections();
}

void VisualMusicPresenter::createConnections()
{
    connect(m_visualMusicModel, &VisualMusicModel::scoreRowSequenceChanged,
            this, &VisualMusicPresenter::scoreRowSequenceChanged);
}

VisualMusicPresenter::~VisualMusicPresenter()
{
    delete m_itemFactory;
}

void VisualMusicPresenter::setPageView(PageViewInterface *pageView)
{
    m_pageView = pageView;
}

PageViewInterface *VisualMusicPresenter::pageView() const
{
    return m_pageView;
}

void VisualMusicPresenter::setModel(QAbstractItemModel *model)
{
    if (m_visualMusicModel->model() != model &&
            model != 0)
         m_visualMusicModel->setModel(model);
}

QAbstractItemModel *VisualMusicPresenter::model() const
{
    return m_visualMusicModel->model();
}

void VisualMusicPresenter::setPluginManager(PluginManager pluginManager)
{
    m_itemFactory->setPluginManager(pluginManager);
}

void VisualMusicPresenter::scoreRowSequenceChanged(int scoreIndex)
{
    RowIterator iterator = m_visualMusicModel->rowIteratorForScore(scoreIndex);
    for (int i=0; i<iterator.rowCount(); i++) {
        m_pageView->appendRow(iterator.rowAt(i));
    }
}

VisualMusicModel *VisualMusicPresenter::visualMusicModel() const
{
    return m_visualMusicModel;
}
