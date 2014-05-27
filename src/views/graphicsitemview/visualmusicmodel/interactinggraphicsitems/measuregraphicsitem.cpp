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
#include "symbolgraphicsitem.h"
#include "measuregraphicsitem.h"

const int InitialLineWidth  = 1;

MeasureGraphicsItem::MeasureGraphicsItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent)
{
    setPenWidth(InitialLineWidth);
    setAcceptDrops(true);

    m_layout = new QGraphicsLinearLayout(Qt::Horizontal, this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
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

void MeasureGraphicsItem::setSymbolGeometry(SymbolGraphicsItem *symbolItem, const QRectF &rect)
{
    symbolItem->setGeometryAnimated(rect);
}

void MeasureGraphicsItem::insertChildItem(int index, InteractingGraphicsItem *childItem)
{
    SymbolGraphicsItem *symbolItem = qgraphicsitem_cast<SymbolGraphicsItem*>(childItem);
    if (!symbolItem) {
        qWarning() << "Non symbol can't be inserted into measure";
        return;
    }

    m_layout->insertItem(index, childItem);
    m_symbolItems.insert(index, symbolItem);
}

void MeasureGraphicsItem::setData(const QVariant &value, int key)
{
    InteractingGraphicsItem::setData(value, key);
}

void MeasureGraphicsItem::setGeometry(const QRectF &rect)
{
    InteractingGraphicsItem::setGeometry(rect);
//    qDebug() << "SetGeometry in measure graphics item: " << rect;
}

void MeasureGraphicsItem::layoutSymbolItems()
{
    QList<QRectF> geometries(symbolGeometries());
    if (!geometries.count() == m_symbolItems.count())
        return;

    for (int i = 0; i < geometries.count(); ++i) {
        SymbolGraphicsItem *currentItem = m_symbolItems.at(i);

        setSymbolGeometry(currentItem, geometries.at(i));

        if (!currentItem->isVisible()) {
            currentItem->fadeIn();
        }
    }
}

QList<QRectF> MeasureGraphicsItem::symbolGeometries() const
{
    QList<QRectF> geometries;
    QRectF itemGeometry;
    qreal currentWidth = 0;
    for (int i = 0; i < m_symbolItems.count(); ++i) {
        SymbolGraphicsItem *currentItem = m_symbolItems.at(i);
        qreal currentItemWidth = currentItem->preferredWidth();
        itemGeometry = QRectF(currentWidth, 0, currentItemWidth,
                              geometry().height());
        geometries << itemGeometry;
        currentWidth += currentItemWidth;
    }
    return geometries;
}

void MeasureGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(m_linePen);
    QRectF rect(geometry());

    qreal rightEdge = rect.width();

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

    m_dragMoveRects = symbolGeometries();
}

void MeasureGraphicsItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (m_dragMoveRects.count() != m_symbolItems.count()) {
        InteractingGraphicsItem::dragMoveEvent(event);
        return;
    }
    event->acceptProposedAction();

    qreal eventXPos = mapFromScene(event->scenePos()).x();
    qreal shiftWidth = 0;
    for (int i = 0; i < m_dragMoveRects.count(); ++i) {
        QRectF itemGeometry(m_dragMoveRects.at(i));
        SymbolGraphicsItem *item = m_symbolItems.at(i);
        if (itemGeometry.x() <= eventXPos &&
                itemGeometry.x() + itemGeometry.width() > eventXPos) {
            qDebug() << "Shift item is " << i + 1;
            shiftWidth = itemGeometry.width();
        }

        itemGeometry.moveLeft(itemGeometry.x() + shiftWidth);
        setSymbolGeometry(item, itemGeometry);
    }
}

void MeasureGraphicsItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->acceptProposedAction();
    clearEndOfDrag();
}

void MeasureGraphicsItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    event->acceptProposedAction();
    clearEndOfDrag();
}

void MeasureGraphicsItem::clearEndOfDrag()
{
    if (m_dragMoveRects.count() != m_symbolItems.count()) {
        return;
    }

    for (int i = 0; i < m_symbolItems.count(); ++i) {
        SymbolGraphicsItem *item = m_symbolItems.at(i);
        setSymbolGeometry(item, m_dragMoveRects.at(i));
    }

    m_dragMoveRects.clear();
}
