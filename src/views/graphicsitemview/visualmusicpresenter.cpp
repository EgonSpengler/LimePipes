/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QGraphicsItem>
#include "visualmusicpresenter.h"

VisualMusicPresenter::VisualMusicPresenter(QObject *parent)
    : QObject(parent),
      m_pageView(0)
{
}

void VisualMusicPresenter::setPageView(PageViewInterface *pageView)
{
    m_pageView = pageView;
}

PageViewInterface *VisualMusicPresenter::pageView() const
{
    return m_pageView;
}
