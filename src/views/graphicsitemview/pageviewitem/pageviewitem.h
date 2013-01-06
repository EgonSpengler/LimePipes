/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PAGEVIEWITEM_H
#define PAGEVIEWITEM_H

#include <QGraphicsWidget>
#include <QList>
#include "../itemtypes.h"
#include "pageitem.h"

class QGraphicsLinearLayout;

class PageViewItem : public QGraphicsWidget
{
public:
    PageViewItem(QGraphicsItem *parent = 0);

    enum { Type = PageViewItemType };
    int type() const { return Type; }

    QRectF boundingRect() const;

private:
    void addPage();
    QGraphicsLinearLayout *m_pageLayout;
    QList<PageItem*> m_pages;
};

#endif // PAGEVIEWITEM_H
