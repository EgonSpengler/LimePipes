/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "pageitem.h"
#include "pagecontentrowitem.h"
#include <QGraphicsLayout>
#include <QGraphicsLinearLayout>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPrinter>

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
    setPageAndContentRectFromPrinter(printer);

    // Layout adjusts itselt to the contents rect
    setContentsMargins(m_pageContentRect.x(), m_pageContentRect.y(),
                       m_pageRect.width() - m_pageContentRect.x() - m_pageContentRect.width(),
                       m_pageRect.height() - m_pageContentRect.y() - m_pageContentRect.height());

    m_layout = new QGraphicsLinearLayout(Qt::Vertical);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    setLayout(m_layout);

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

void PageItem::setPageAndContentRectFromPrinter(const QPrinter &printer)
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

int PageItem::remainingVerticalSpace() const
{
    if (!m_layout->count())
        return m_pageContentRect.height();

    QGraphicsLayoutItem *lastItem = m_layout->itemAt(m_layout->count() - 1);

    return m_pageContentRect.height() -
            (lastItem->geometry().y() - m_pageContentRect.y()) -
             lastItem->geometry().height();
}

int PageItem::rowCount() const
{
    return m_layout->count();
}

PageContentRowItem *PageItem::rowAt(int index)
{
    if (!isValidRowIndex(index))
        return 0;

    return qgraphicsitem_cast<PageContentRowItem *>(m_layout->itemAt(index)->graphicsItem());
}

void PageItem::removeRow(int index)
{
    int verticalSpaceBefore = remainingVerticalSpace();
    m_layout->removeAt(index);
    m_layout->activate();
    emit remainingVerticalSpaceChanged(verticalSpaceBefore, remainingVerticalSpace());
}

void PageItem::removeRow(PageContentRowItem *row)
{
    int verticalSpaceBefore = remainingVerticalSpace();
    m_layout->removeItem(row);
    m_layout->activate();
    emit remainingVerticalSpaceChanged(verticalSpaceBefore, remainingVerticalSpace());
}

void PageItem::appendRow(PageContentRowItem *row)
{
    insertRow(m_layout->count(), row);
}

void PageItem::prependRow(PageContentRowItem *row)
{
    insertRow(0, row);
}

void PageItem::insertRow(int index, PageContentRowItem *row)
{
    int spaceBefore = remainingVerticalSpace();
    m_layout->insertItem(index, row);
    m_layout->activate();
    emit remainingVerticalSpaceChanged(spaceBefore, remainingVerticalSpace());
    if (remainingVerticalSpace() < 0)
        emit lastRowExceedsContentBounds();
}

bool PageItem::isValidRowIndex(int rowIndex)
{
    if (rowIndex < 0 ||
            rowIndex >= m_layout->count())
        return false;
    return true;
}
