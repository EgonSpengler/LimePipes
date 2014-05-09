/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GRAPHICSITEMVIEW_H
#define GRAPHICSITEMVIEW_H

#include <QAbstractItemView>
#include <common/pluginmanagerinterface.h>

class GraphicsView;
class GraphicsScene;
class VisualMusicPresenter;
class PageViewItem;
class VisualMusicModel;
class VisualItemFactory;

class GraphicsItemView : public QAbstractItemView
{
    friend class GraphicsItemViewTest;

    Q_OBJECT
public:
    explicit GraphicsItemView(QWidget *parent = 0);
    ~GraphicsItemView();

    QRect visualRect(const QModelIndex &index) const;
    void scrollTo(const QModelIndex &index, ScrollHint hint);
    QModelIndex indexAt(const QPoint &point) const;
    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers);
    int horizontalOffset() const;
    int verticalOffset() const;
    bool isIndexHidden(const QModelIndex &index) const;
    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command);
    QRegion visualRegionForSelection(const QItemSelection &selection) const;

    void setModel(QAbstractItemModel *model);

    void setPluginManager(PluginManager pluginManager);

private slots:
    void currentChanged(const QModelIndex& current, const QModelIndex& previous);

private:
    GraphicsScene *m_graphicsScene;
    GraphicsView *m_graphicsView;
    VisualMusicPresenter *m_musicPresenter;
    PageViewItem *m_pageView;
    VisualMusicModel *m_visualMusicModel;
    VisualItemFactory *m_visualItemFactory;
};

#endif // GRAPHICSITEMVIEW_H
