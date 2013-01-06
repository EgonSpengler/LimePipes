/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "graphicsscene.h"
#include "pageviewitem/pageviewitem.h"

GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(QColor(0xD0, 0xD0, 0xD0)));

    m_pageViewItem = new PageViewItem();
    addItem(m_pageViewItem);
}
