/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "pageviewitem.h"
#include "pageitem.h"
#include <QGraphicsLinearLayout>

PageViewItem::PageViewItem(QGraphicsItem *parent)
    : QGraphicsWidget(parent)
{
    m_pageLayout = new QGraphicsLinearLayout(Qt::Vertical, this);
    m_pageLayout->setSpacing(30.0);

    addPage();
}

QRectF PageViewItem::boundingRect() const
{
    return m_pageLayout->geometry();
}

void PageViewItem::addPage()
{
    PageItem *page = new PageItem(this);
    m_pageLayout->addItem(page);
    m_pages.append(page);
}
