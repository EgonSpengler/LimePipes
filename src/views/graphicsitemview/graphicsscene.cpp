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
#include <QAbstractItemModel>
#include "graphicsscene.h"
#include "visualmusicmodel/visualmusicmodel.h"
#include "visualmusicmodel/interactinggraphicsitems/symbolgraphicsitem.h"
#include "visualmusicmodel/interactinggraphicsitems/measuregraphicsitem.h"

GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(parent),
      m_visualMusicModel(0)
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
    if (m_symbolDragStart.isNull() ||
            !(event->buttons() & Qt::LeftButton)) {
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }

    if (!m_visualMusicModel) {
        qDebug() << "No VisualMusicModel set in GraphicsScene. Can't start drag.";
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }

    QLineF dragDistance(m_symbolDragStart, event->scenePos());
    if ( dragDistance.length() > QApplication::startDragDistance()) {
        QList<QGraphicsItem*> symbolGraphicsItems = selectedSymbolGraphicsItems();
        qDebug() << QString("Dragging %1 symbol items").arg(symbolGraphicsItems.count());

        m_dragSymbolIndexes.clear();
        foreach (QGraphicsItem *symbolItem, symbolGraphicsItems) {
            QModelIndex symbolIndex = m_visualMusicModel->indexForItem(symbolItem);
            if (symbolIndex.isValid()) {
                m_dragSymbolIndexes.append(symbolIndex);
            }
        }
        qDebug() << "Selected symbol indexes: " << m_dragSymbolIndexes;

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
        if (m_dragSymbolIndexes.count()) {
            const QAbstractItemModel *model = m_dragSymbolIndexes.at(0).model();
            if (model) {
                qDebug() << "Setting drag mime data from model";
                QMimeData *data = model->mimeData(m_dragSymbolIndexes);
                drag->setMimeData(data);
            }
        }

        drag->exec(Qt::MoveAction);

        m_symbolDragStart = QPoint();
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "GraphicsScene dropEvent";
    const QMimeData *mimeData = event->mimeData();

    qDebug() << "GraphicsScene drop event mime formats: " << mimeData->formats();
    if (mimeData->formats().contains(LP::MimeTypes::Symbol)) {
        Qt::DropAction dropAction = event->dropAction();
        if (dropAction != Qt::MoveAction) {
            qDebug() << "GraphicsScene: Another drop action as moving is currently not supported";
            return;
        }

        qDebug() << "Symbols dropped";
        QGraphicsItem *dropItem = itemAt(event->scenePos(), QTransform());
        if (!dropItem)
            goto baseImpl;

        GraphicsItemType dropItemType = itemTypeOfGraphicsItem(dropItem);
        qDebug() << "Drop target: " << dropItemType;
        if (dropItemType == MeasureGraphicsItemType) {
            MeasureGraphicsItem *measureItem = qgraphicsitem_cast<MeasureGraphicsItem*>(dropItem);
            if (!measureItem) {
                qWarning() << "Can't cast drop item to measure graphics item";
                goto baseImpl;
            }

            QPointF dropPos = measureItem->mapFromScene(event->scenePos());
            QGraphicsItem *dropItem = measureItem->dropItemAt(dropPos);
            if (dropItem == measureItem) {
                qDebug() << "Drop on measure";
            } else {
                qDebug() << "Drop on " << itemTypeOfGraphicsItem(dropItem);
            }

            QModelIndex dropItemIndex = m_visualMusicModel->indexForItem(dropItem);
            qDebug() << "Drop index: " << dropItemIndex;
            QAbstractItemModel *itemModel = m_visualMusicModel->model();
            if (!itemModel) {
                qWarning() << "Can't dropMimeData. VisualMusicModel has no abstract item model set.";
                goto baseImpl;
            }

            QGraphicsScene::dropEvent(event);
            bool dropSuccess = itemModel->dropMimeData(event->mimeData(), dropAction,
                                                       dropItemIndex.row(), dropItemIndex.column(),
                                                       dropItemIndex.parent());
            if (!dropSuccess)
                return;

            if (dropAction == Qt::MoveAction) {
                foreach (const QModelIndex &index, m_dragSymbolIndexes) {
                    itemModel->removeRow(index.row(), index.parent());
                }
            }

            return; // No base implementation call
        }
    }

baseImpl:
    QGraphicsScene::dropEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}

void GraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dragEnterEvent(event);
}

void GraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dragMoveEvent(event);
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

VisualMusicModel *GraphicsScene::visualMusicModel() const
{
    return m_visualMusicModel;
}

void GraphicsScene::setVisualMusicModel(VisualMusicModel *visualMusicModel)
{
    m_visualMusicModel = visualMusicModel;
}

