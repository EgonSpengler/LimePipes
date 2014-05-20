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
#include "graphicsviewzoom.h"

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    new GraphicsViewZoom(this);

    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    m_itemTypes << static_cast<int>(InteractingGraphicsItemType);
    m_itemTypes << static_cast<int>(StaffGraphicsItemType);
    m_itemTypes << static_cast<int>(MeasureGraphicsItemType);
    m_itemTypes << static_cast<int>(SymbolGraphicsItemType);
    m_itemTypes << static_cast<int>(SymbolGlyphItemType);

    setAcceptDrops(true);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (!scene()) {
        QGraphicsView::mousePressEvent(event);
        return;
    }

    if (QGraphicsItem *item = itemAt(event->pos())) {
        GraphicsItemType itemType = itemTypeOfGraphicsItem(item);
        if (itemType == SymbolGraphicsItemType ||
                itemType == SymbolGlyphItemType) {
            if (scene()->selectedItems().contains(item)) {
                qDebug() << "Clicked item is selected";
            }
            if (event->button() == Qt::LeftButton) {
                m_symbolDragStart = event->pos();
            }
        } else {
            m_symbolDragStart = QPoint();
        }
    }

    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_symbolDragStart.isNull()) {
        QGraphicsView::mouseMoveEvent(event);
        return;
    }

    if (!(event->buttons() & Qt::LeftButton)) {
            return;
    }

    QLineF dragDistance(m_symbolDragStart, event->pos());
    if ( dragDistance.length() > QApplication::startDragDistance()) {
        QList<QGraphicsItem*> symbolGraphicsItems = selectedSymbolGraphicsItems();
        qDebug() << QString("Dragging %1 symbol items").arg(symbolGraphicsItems.count());

        QGraphicsItemGroup *itemGroup = scene()->createItemGroup(symbolGraphicsItems);
        QRectF sceneRect = itemGroup->sceneBoundingRect();
        scene()->destroyItemGroup(itemGroup);

        QRectF targetRect;
        targetRect.setSize(sceneRect.size());
        QPixmap pixmap(targetRect.width(), targetRect.height());
        QPainter painter(&pixmap);
        scene()->render(&painter, targetRect, sceneRect);

        QDrag *drag = new QDrag(this);
        drag->setDragCursor(pixmap, Qt::CopyAction);
        QMimeData *mimeData = new QMimeData;
        mimeData->setData(LP::MimeTypes::Symbol, QString("Some text").toUtf8());
        drag->setMimeData(mimeData);

        drag->exec(Qt::CopyAction);
        m_symbolDragStart = QPoint();
    }

//    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{

//    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
//    event->acceptProposedAction();

    QGraphicsView::dragEnterEvent(event);
}

void GraphicsView::dragMoveEvent(QDragMoveEvent *event)
{
//    event->acceptProposedAction();
    QGraphicsView::dragMoveEvent(event);
}

void GraphicsView::dragLeaveEvent(QDragLeaveEvent *event)
{

    QGraphicsView::dragLeaveEvent(event);
}

void GraphicsView::dropEvent(QDropEvent *event)
{
    event->acceptProposedAction();

//    QGraphicsView::dropEvent(event);
}

GraphicsItemType GraphicsView::itemTypeOfGraphicsItem(const QGraphicsItem *item) const
{
    if (m_itemTypes.contains(item->type())) {
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
