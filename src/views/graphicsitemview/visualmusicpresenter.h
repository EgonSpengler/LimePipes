/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALMUSICPRESENTER_H
#define VISUALMUSICPRESENTER_H

#include <QObject>
#include "pageviewinterface.h"

class QGraphicsItem;

class VisualMusicPresenter : public QObject
{
    friend class VisualMusicPresenterTest;
public:
    explicit VisualMusicPresenter(QObject *parent = 0);

    void setPageView(PageViewInterface *pageView);
    PageViewInterface *pageView() const;

private:
    PageViewInterface *m_pageView;
};

#endif // VISUALMUSICPRESENTER_H
