/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QPoint>
#include <QList>
#include <QGraphicsView>
#include <common/defines.h>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    GraphicsItemType itemTypeOfGraphicsItem(const QGraphicsItem *item) const;
    QList<QGraphicsItem*> selectedSymbolGraphicsItems();
    QGraphicsItem *symbolGraphicsItemForGlyphItem(QGraphicsItem *glyphItem);
    QList<int> m_itemTypes;
    QPoint m_symbolDragStart;
};

#endif // GRAPHICSVIEW_H
