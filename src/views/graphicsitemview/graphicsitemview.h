/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GRAPHICSITEMVIEW_H
#define GRAPHICSITEMVIEW_H

#include <QTransform>
#include <QAbstractItemView>

#include <common/pluginmanagerinterface.h>
#include <app/applicationinterface.h>

class GraphicsView;
class GraphicsScene;
class VisualMusicPresenter;
class PageViewItem;
class VisualMusicModel;
class VisualItemFactory;

class GraphicsItemView : public QWidget
{
    friend class GraphicsItemViewTest;

    Q_OBJECT
public:
    explicit GraphicsItemView(QWidget *parent = 0);
    ~GraphicsItemView();

    void setModel(QAbstractItemModel *model);

    void setPluginManager(PluginManager pluginManager);

    void setApplication(const Application &application);

public slots:
    void scale(qreal level);

private:
    GraphicsScene *m_graphicsScene;
    GraphicsView *m_graphicsView;
    VisualMusicPresenter *m_musicPresenter;
    PageViewItem *m_pageView;
    VisualMusicModel *m_visualMusicModel;
    VisualItemFactory *m_visualItemFactory;
};

#endif // GRAPHICSITEMVIEW_H
