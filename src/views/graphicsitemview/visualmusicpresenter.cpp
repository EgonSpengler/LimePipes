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

    createConnections();
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

void VisualMusicPresenter::scoreInserted(const QModelIndex &scoreIndex)
{
    InteractingScore *interactingScore = new InteractingScore(this);
    m_interactingScores.insert(scoreIndex.row(), interactingScore);

    ScorePropertiesItem *visualScore = m_visualMusicModel->scorePropertiesItemFromIndex(scoreIndex);
    if (!visualScore)
        return;
    interactingScore->linkWithItem(visualScore);
    m_pageView->appendRow(interactingScore->headerItem());
    m_pageView->appendRow(interactingScore->footerItem());
}

void VisualMusicPresenter::createConnections()
{
    connect(m_visualMusicModel, SIGNAL(scoreInserted(QModelIndex)),
            this, SLOT(scoreInserted(QModelIndex)));
}

VisualMusicModel *VisualMusicPresenter::visualMusicModel() const
{
    return m_visualMusicModel;
}
