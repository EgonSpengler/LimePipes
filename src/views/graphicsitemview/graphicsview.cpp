/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QDebug>
#include <QLineF>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QPixmap>
#include "visualmusicmodel/interactinggraphicsitems/symbolgraphicsitem.h"
#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    m_itemTypes << static_cast<int>(InteractingGraphicsItemType);
    m_itemTypes << static_cast<int>(StaffGraphicsItemType);
    m_itemTypes << static_cast<int>(MeasureGraphicsItemType);
    m_itemTypes << static_cast<int>(SymbolGraphicsItemType);
    m_itemTypes << static_cast<int>(SymbolGlyphItemType);

    setAcceptDrops(true);
    setMouseTracking(true);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    QGraphicsView::dragEnterEvent(event);
}

void GraphicsView::dragMoveEvent(QDragMoveEvent *event)
{
    QGraphicsView::dragMoveEvent(event);
}

void GraphicsView::dragLeaveEvent(QDragLeaveEvent *event)
{
    QGraphicsView::dragLeaveEvent(event);
}

void GraphicsView::dropEvent(QDropEvent *event)
{
    QGraphicsView::dropEvent(event);
}

GraphicsItemType GraphicsView::itemTypeOfGraphicsItem(const QGraphicsItem *item) const
{
    int type = item->type();
    if (m_itemTypes.contains(type)) {
        return static_cast<GraphicsItemType>(item->type());
    }

    return NoGraphicsItemType;
}

QList<QGraphicsItem *> GraphicsView::selectedSymbolGraphicsItems()
{
    QList<QGraphicsItem*> allSelectedItems(scene()->selectedItems());
    QList<QGraphicsItem*> symbolGraphicsItems;
    foreach (QGraphicsItem *selectedItem, allSelectedItems) {
        GraphicsItemType itemType = itemTypeOfGraphicsItem(selectedItem);
        QGraphicsItem *symbolItem = 0;
        if (itemType == SymbolGlyphItemType) {
            symbolItem = symbolGraphicsItemForGlyphItem(selectedItem);
        }

        if (symbolItem != 0 &&
                !symbolGraphicsItems.contains(symbolItem)) {
            symbolGraphicsItems.append(symbolItem);
        }
    }
    return symbolGraphicsItems;
}

QGraphicsItem *GraphicsView::symbolGraphicsItemForGlyphItem(QGraphicsItem *glyphItem)
{
    if (!glyphItem)
        return 0;

    QGraphicsItem *tempItem = glyphItem;
    GraphicsItemType type = NoGraphicsItemType;
    while (1) {
        type = itemTypeOfGraphicsItem(tempItem);
        if (type == SymbolGraphicsItemType)
            return tempItem;

        if (tempItem->parentItem() == 0)
            return 0;

        tempItem = tempItem->parentItem();
    }
}
