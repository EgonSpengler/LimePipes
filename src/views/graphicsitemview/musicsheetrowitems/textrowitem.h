/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TEXTROWITEM_H
#define TEXTROWITEM_H

#include "../pageviewitem/pagecontentrowitem.h"

class QPainter;

class TextRowItem : public PageContentRowItem
{
public:
    TextRowItem(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/);
};

#endif // TEXTROWITEM_H
