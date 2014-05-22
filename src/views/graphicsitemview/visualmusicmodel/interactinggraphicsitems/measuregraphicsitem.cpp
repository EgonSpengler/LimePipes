/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPen>
#include <QPainter>
#include <QMimeData>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsLinearLayout>
#include <common/defines.h>
#include "measuregraphicsitem.h"

#include <QCoreApplication>

const int InitialLineWidth  = 1;

MeasureGraphicsItem::MeasureGraphicsItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent)
{
    setPenWidth(InitialLineWidth);
    setAcceptDrops(true);
}

void MeasureGraphicsItem::setPenWidth(qreal width)
{
    if (width <= 0)
        return;

    m_linePen.setWidthF(width);
}

qreal MeasureGraphicsItem::penWidth() const
{
    return m_linePen.widthF();
}

void MeasureGraphicsItem::insertChildItem(int index, InteractingGraphicsItem *childItem)
{
    m_symbolItems.insert(index, childItem);
    childItem->setParentItem(this);
    childItem->setVisible(false);

    qreal currentWidth = 0;
    for (int i = 0; i < m_symbolItems.count(); ++i) {
        InteractingGraphicsItem *currentItem = m_symbolItems.at(i);
        qreal currentItemWidth = currentItem->preferredWidth();
        currentItem->setGeometry(currentWidth, 0, currentItemWidth,
                                 geometry().height());
        if (!currentItem->isVisible()) {
            currentItem->setVisible(true);
        }
        currentWidth += currentItemWidth;
    }
}

void MeasureGraphicsItem::setData(const QVariant &value, int key)
{
    InteractingGraphicsItem::setData(value, key);
}

void MeasureGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(m_linePen);
    QRectF rect(geometry());

    qreal rightEdge = rect.right();

    painter->drawLine(0, 0, 0, rect.height());
    painter->drawLine(rightEdge, 0, rightEdge, rect.height());
}

void MeasureGraphicsItem::musicFontHasChanged(const MusicFontPtr &musicFont)
{
    qreal staffSpace = musicFont->staffSpace();
    Engravings engravings(musicFont->engravings());
    qreal width = engravings.thinBarlineThickness * staffSpace;
    setPenWidth(width);
}

void MeasureGraphicsItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat(LP::MimeTypes::Symbol)) {
        event->acceptProposedAction();
    } else {
        InteractingGraphicsItem::dragEnterEvent(event);
        return;
    }

    QPointF itemPos = mapFromScene(event->scenePos());

    m_dragGapItem = new QGraphicsWidget(this);
    for (int i = 0; i < m_symbolItems.count(); ++i) {
        m_dragMoveRects.append(m_symbolItems.at(i)->geometry());
    }
    qDebug() << "Drag enter in measure item at: " << itemPos;
}

void MeasureGraphicsItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (m_dragMoveRects.count() != m_symbolItems.count()) {
        InteractingGraphicsItem::dragMoveEvent(event);
        return;
    }

    qreal eventXPos = mapFromScene(event->scenePos()).x();
    qreal shiftWidth = 0;
    for (int i = 0; i < m_dragMoveRects.count(); ++i) {
        QRectF itemGeometry(m_dragMoveRects.at(i));
        QGraphicsLayoutItem *item = m_symbolItems.at(i);
        if (itemGeometry.x() <= eventXPos &&
                itemGeometry.x() + itemGeometry.width() > eventXPos) {
            qDebug() << "Shift item is " << i + 1;
            shiftWidth = itemGeometry.width();
        }

        itemGeometry.moveLeft(itemGeometry.x() + shiftWidth);
        item->setGeometry(itemGeometry);
    }

    event->acceptProposedAction();
    qDebug() << "Drag move in measure item";
}

void MeasureGraphicsItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->acceptProposedAction();
    clearEndOfDrag();
    qDebug() << "Drag leave in measure item";
}

void MeasureGraphicsItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    event->acceptProposedAction();
    clearEndOfDrag();
    qDebug() << "Drop in measure item";
}

void MeasureGraphicsItem::clearEndOfDrag()
{
    if (m_dragMoveRects.count() != m_symbolItems.count()) {
        return;
    }

    for (int i = 0; i < m_symbolItems.count(); ++i) {
        InteractingGraphicsItem *item = m_symbolItems.at(i);
        item->setGeometry(m_dragMoveRects.at(i));
    }

    m_dragMoveRects.clear();
}
