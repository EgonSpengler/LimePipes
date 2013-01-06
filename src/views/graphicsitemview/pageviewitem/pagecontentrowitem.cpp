/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "pagecontentrowitem.h"

PageContentRowItem::PageContentRowItem(QGraphicsItem *parent) :
    QGraphicsWidget(parent)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    setGeometry(0, 0, preferredWidth(), preferredHeight());
}
