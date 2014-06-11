/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GRAPHICSMAPPERINTERFACE_H
#define GRAPHICSMAPPERINTERFACE_H

#include <QModelIndex>

class QGraphicsItem;

class GraphicsMapperInterface
{
public:
    virtual ~GraphicsMapperInterface() {}

    virtual QModelIndex indexForItem(QGraphicsItem *item) const = 0;
    virtual QGraphicsItem *itemForIndex(const QModelIndex &index) const = 0;
};

#endif // GRAPHICSMAPPERINTERFACE_H
