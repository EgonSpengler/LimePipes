/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PAGECONTENTROWITEM_H
#define PAGECONTENTROWITEM_H

#include <QGraphicsWidget>
#include "../itemtypes.h"

class PageContentRowItem : public QGraphicsWidget
{
public:
    explicit PageContentRowItem(QGraphicsItem *parent = 0);

    enum { Type = PageContentRowItemType };
    int type() const { return Type; }
};

#endif // PAGECONTENTROWITEM_H
