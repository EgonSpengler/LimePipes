/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PAGECONTENTITEM_H
#define PAGECONTENTITEM_H

#include <QGraphicsWidget>
#include "../itemtypes.h"

class PageContentRowItem;
class QGraphicsLinearLayout;

class PageContentItem : public QGraphicsWidget
{
public:
    PageContentItem(QGraphicsItem *parent = 0);

    enum { Type = PageContentItemType };
    int type() const { return Type; }

    void insertRow(int index, PageContentRowItem *row);
    int rowCount() const;
    PageContentRowItem *rowAt(int index);
    void removeRow(int index);
    void removeRow(PageContentRowItem *row);

private:
    QGraphicsLinearLayout *m_layout;
};

#endif // PAGECONTENTITEM_H
