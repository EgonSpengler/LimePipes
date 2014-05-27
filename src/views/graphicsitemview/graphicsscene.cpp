/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QDrag>
#include <QMimeData>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include "graphicsscene.h"
#include "visualmusicmodel/interactinggraphicsitems/symbolgraphicsitem.h"
#include "pageviewitem/pageviewitem.h"

GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QColor(0xD0, 0xD0, 0xD0)));

    m_itemTypes << static_cast<int>(InteractingGraphicsItemType);
    m_itemTypes << static_cast<int>(StaffGraphicsItemType);
    m_itemTypes << static_cast<int>(MeasureGraphicsItemType);
    m_itemTypes << static_cast<int>(SymbolGraphicsItemType);
    m_itemTypes << static_cast<int>(SymbolGlyphItemType);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (QGraphicsItem *item = itemAt(event->scenePos(), QTransform())) {
        GraphicsItemType itemType = itemTypeOfGraphicsItem(item);
        qDebug() << "Clicked item type: " << itemType <<
                    QString("(int: %1)").arg(item->type());
        if (itemType == SymbolGraphicsItemType ||
                itemType == SymbolGlyphItemType) {
            if (selectedItems().contains(item)) {
                qDebug() << "Clicked item is selected";
            }
            if (event->button() == Qt::LeftButton) {
                m_symbolDragStart = event->scenePos();
            }
        } else {
            m_symbolDragStart = QPoint();
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_symbolDragStart.isNull()) {
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }

    if (!(event->buttons() & Qt::LeftButton)) {
        return;
    }

    QLineF dragDistance(m_symbolDragStart, event->scenePos());
    if ( dragDistance.length() > QApplication::startDragDistance()) {
        QList<QGraphicsItem*> symbolGraphicsItems = selectedSymbolGraphicsItems();
        qDebug() << QString("Dragging %1 symbol items").arg(symbolGraphicsItems.count());

        //        QGraphicsItemGroup *itemGroup = scene()->createItemGroup(symbolGraphicsItems);
        //        QRectF sceneRect = itemGroup->sceneBoundingRect();
        //        scene()->destroyItemGroup(itemGroup);

        //        QRectF targetRect;
        //        targetRect.setSize(sceneRect.size());
        //        QPixmap pixmap(targetRect.width(), targetRect.height());
        //        QPainter painter(&pixmap);
        //        scene()->render(&painter, targetRect, sceneRect);

        QDrag *drag = new QDrag(this);
        //        drag->setDragCursor(pixmap, Qt::CopyAction);
        QMimeData *mimeData = new QMimeData;
        mimeData->setData(LP::MimeTypes::Symbol, QString("Some text").toUtf8());
        drag->setMimeData(mimeData);

        drag->exec(Qt::CopyAction);
        m_symbolDragStart = QPoint();
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}

void GraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dragEnterEvent(event);
}

GraphicsItemType GraphicsScene::itemTypeOfGraphicsItem(const QGraphicsItem *item) const
{
    int type = item->type();
    if (m_itemTypes.contains(type)) {
        return static_cast<GraphicsItemType>(item->type());
    }

    return NoGraphicsItemType;
}

QList<QGraphicsItem *> GraphicsScene::selectedSymbolGraphicsItems()
{
    QList<QGraphicsItem*> allSelectedItems(selectedItems());
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

QGraphicsItem *GraphicsScene::symbolGraphicsItemForGlyphItem(QGraphicsItem *glyphItem)
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
