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

class VisualMusicModel;
class QAbstractItemModel;

class VisualMusicPresenter : public QObject
{
    friend class VisualMusicPresenterTest;
public:
    explicit VisualMusicPresenter(QObject *parent = 0);

    void setPageView(PageViewInterface *pageView);
    PageViewInterface *pageView() const;

    void setModel(QAbstractItemModel* model);
    QAbstractItemModel *model() const;


private:
    VisualMusicModel *visualMusicModel() const;
    PageViewInterface *m_pageView;
    VisualMusicModel *m_visualMusicModel;
};

#endif // VISUALMUSICPRESENTER_H
