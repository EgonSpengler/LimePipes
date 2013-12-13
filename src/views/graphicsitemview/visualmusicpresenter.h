/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALMUSICPRESENTER_H
#define VISUALMUSICPRESENTER_H

#include <QList>
#include <QObject>
#include "pageviewinterface.h"
#include "graphicsitemview/visualmusicmodel/iteminteractions/scoreinteraction.h"

class AbstractVisualItemFactory;
class VisualMusicModel;
class QAbstractItemModel;
class QModelIndex;

class VisualMusicPresenter : public QObject
{
    friend class VisualMusicPresenterTest;

    Q_OBJECT
public:
    explicit VisualMusicPresenter(QObject *parent = 0);
    ~VisualMusicPresenter();

    void setPageView(PageViewInterface *pageView);
    PageViewInterface *pageView() const;

    void setModel(QAbstractItemModel* model);
    QAbstractItemModel *model() const;

private slots:
    void scoreRowSequenceChanged(int scoreIndex);

private:
    void createConnections();
    VisualMusicModel *visualMusicModel() const;
    PageViewInterface *m_pageView;
    VisualMusicModel *m_visualMusicModel;
    AbstractVisualItemFactory *m_itemFactory;
};

#endif // VISUALMUSICPRESENTER_H
