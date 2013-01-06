/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QGraphicsLinearLayout>
#include "pagecontentitem.h"
#include <views/graphicsitemview/pageviewitem/pagecontentrowitem.h>

PageContentItem::PageContentItem(QGraphicsItem *parent)
    : QGraphicsWidget(parent)
{
    m_layout = new QGraphicsLinearLayout(Qt::Vertical);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    setLayout(m_layout);
}

void PageContentItem::insertRow(int index, PageContentRowItem *row)
{
    m_layout->insertItem(index, row);
}

int PageContentItem::rowCount() const
{
    return m_layout->count();
}

PageContentRowItem *PageContentItem::rowAt(int index)
{
    return qgraphicsitem_cast<PageContentRowItem *>(m_layout->itemAt(index)->graphicsItem());
}

void PageContentItem::removeRow(int index)
{
    m_layout->removeAt(index);
}

void PageContentItem::removeRow(PageContentRowItem *row)
{
    m_layout->removeItem(row);
}
