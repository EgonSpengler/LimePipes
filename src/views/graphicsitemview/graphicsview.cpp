/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "graphicsview.h"
#include "graphicsviewzoom.h"

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    new GraphicsViewZoom(this);
}
