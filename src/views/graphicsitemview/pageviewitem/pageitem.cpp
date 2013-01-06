/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "pageitem.h"
#include "pagecontentrowitem.h"
#include <QPainter>
#include <QPrinter>
#include <QGraphicsDropShadowEffect>

namespace {

const int DefaultShortEdgeWidth = 950;

}

PageItem::PageItem(QGraphicsItem *parent)
    : QGraphicsWidget(parent), m_shortEdgeWidth(DefaultShortEdgeWidth), m_pageRect(QRectF()), m_pageContentRect(QRectF())
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPrinter printer;
    qreal minEdge = qMin(printer.paperRect().width(),
                         printer.paperRect().height());
    qreal margin = minEdge * 0.1;
    printer.setPageMargins(margin, margin, margin, margin, QPrinter::DevicePixel);
    setPageAndPaperRectFromPrinter(printer);

    m_pageContentItem = new PageContentItem(this);
    m_pageContentItem->setPreferredWidth(m_pageContentRect.width());
    m_pageContentItem->setGeometry(m_pageContentRect.topLeft().x(), m_pageContentRect.topLeft().y(),
                            m_pageContentRect.width(), 0);

    QPalette pagePalette = palette();
    pagePalette.setColor(QPalette::Window, Qt::white);
    setPalette(pagePalette);
    setAutoFillBackground(true);

    QGraphicsDropShadowEffect *dropShadow = new QGraphicsDropShadowEffect();
    dropShadow->setBlurRadius(10);
    dropShadow->setOffset(0.0, 0.0);
    setGraphicsEffect(dropShadow);
}

void PageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QColor(0xD0, 0xD0, 0xD0));
    painter->drawRect(m_pageRect);
    painter->drawRect(m_pageContentRect);
}

void PageItem::setPageAndPaperRectFromPrinter(const QPrinter &printer)
{
    m_pageRect = printer.paperRect();
    m_pageContentRect = printer.pageRect();

    qreal scaleFactor = 0;
    if (printer.orientation() == QPrinter::Portrait)
        scaleFactor = m_shortEdgeWidth / m_pageRect.width();
    else
        scaleFactor = m_shortEdgeWidth / m_pageRect.height();

    m_pageRect.setSize(QSizeF(m_pageRect.width() * scaleFactor,
                               m_pageRect.height() * scaleFactor));
    m_pageRect.setTopLeft(QPointF(m_pageRect.x() * scaleFactor,
                                   m_pageRect.y() * scaleFactor));

    m_pageContentRect.setSize(QSizeF(m_pageContentRect.width() * scaleFactor,
                              m_pageContentRect.height() * scaleFactor));
    m_pageContentRect.setTopLeft(QPointF(m_pageContentRect.x() * scaleFactor,
                                   m_pageContentRect.y() * scaleFactor));

    setPreferredSize(m_pageRect.size());
}

int PageItem::rowCount() const
{
    return m_pageContentItem->rowCount();
}

PageContentRowItem *PageItem::rowAt(int index)
{
    return m_pageContentItem->rowAt(index);
}

void PageItem::removeRow(int index)
{
    m_pageContentItem->removeRow(index);
}

void PageItem::removeRow(PageContentRowItem *row)
{
    m_pageContentItem->removeRow(row);
}

void PageItem::appendRow(PageContentRowItem *row)
{
    m_pageContentItem->insertRow(m_pageContentItem->rowCount(), row);
}

void PageItem::prependRow(PageContentRowItem *row)
{
    m_pageContentItem->insertRow(0, row);
}

void PageItem::insertRow(int index, PageContentRowItem *row)
{
    m_pageContentItem->insertRow(index, row);
}
