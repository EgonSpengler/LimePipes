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
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qreal distance = QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length();
//    if (distance < QApplication::startDragDistance()) {
//        return;
//    }

//    QDrag *drag = new QDrag(event->widget());
//    QMimeData *mime = new QMimeData;
//    drag->setMimeData(mime);

    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}
