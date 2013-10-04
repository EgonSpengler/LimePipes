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
#include "visualmusicmodelinterface.h"

class GraphicsView;
class GraphicsScene;

class GraphicsItemView : public QAbstractItemView
{
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

private:
    GraphicsScene *m_graphicsScene;
    GraphicsView *m_graphicsView;
};

#endif // GRAPHICSITEMVIEW_H
