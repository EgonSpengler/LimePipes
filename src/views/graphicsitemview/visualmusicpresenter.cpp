/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualmusicmodel/visualmusicmodel.h"
#include "visualmusicpresenter.h"

VisualMusicPresenter::VisualMusicPresenter(QObject *parent)
    : QObject(parent),
      m_pageView(0),
      m_visualMusicModel(0)
{
    m_visualMusicModel = new VisualMusicModel(this);
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

VisualMusicModel *VisualMusicPresenter::visualMusicModel() const
{
    return m_visualMusicModel;
}
