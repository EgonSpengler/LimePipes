/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "pageitem.h"
#include <QGraphicsLayout>
#include <QGraphicsLinearLayout>
#include <QGraphicsDropShadowEffect>
#include <common/layoutsettings.h>
#include <QPainter>
#include <QPrinter>
#include <QApplication>
#include <QScreen>

PageItem::PageItem(QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      SettingsObserver(Settings::Category::Layout),
      m_pageRect(QRectF()),
      m_pageContentRect(QRectF())
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    LayoutSettings::registerObserver(this);
    LayoutSettings settings;
    setPageLayout(settings.pageLayout());

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

void PageItem::setPageLayout(const QPageLayout &layout)
{
    QScreen *screen = QApplication::primaryScreen();
    int pixelPerInch = screen->physicalDotsPerInch();
    int resolution = pixelPerInch;
    m_pageRect = layout.fullRectPixels(resolution);
    m_pageContentRect = layout.paintRectPixels(resolution);

    setPreferredSize(m_pageRect.size());

    // Layout adjusts itselt to the contents rect
    setContentsMargins(m_pageContentRect.x(), m_pageContentRect.y(),
                       m_pageRect.width() - m_pageContentRect.x() - m_pageContentRect.width(),
                       m_pageRect.height() - m_pageContentRect.y() - m_pageContentRect.height());

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

int PageItem::indexOfRow(QGraphicsWidget *row)
{
    return childItems().indexOf(row);
}

QGraphicsWidget *PageItem::rowAt(int index)
{
    if (!isValidRowIndex(index))
        return 0;

    return dynamic_cast<QGraphicsWidget *>(m_layout->itemAt(index)->graphicsItem());
}

void PageItem::removeRow(int index)
{
    int verticalSpaceBefore = remainingVerticalSpace();
    m_layout->removeAt(index);
    m_layout->activate();
    emit remainingVerticalSpaceChanged(verticalSpaceBefore, remainingVerticalSpace());
}

void PageItem::removeRow(QGraphicsWidget *row)
{
    int verticalSpaceBefore = remainingVerticalSpace();
    m_layout->removeItem(row);
    m_layout->activate();
    emit remainingVerticalSpaceChanged(verticalSpaceBefore, remainingVerticalSpace());
}

void PageItem::prepareWidgetForRow(QGraphicsWidget *rowWidget)
{
    rowWidget->setSizePolicy(QSizePolicy::MinimumExpanding, // horizontal
                             QSizePolicy::Fixed);           // vertical
}

void PageItem::appendRow(QGraphicsWidget *row)
{
    insertRow(m_layout->count(), row);
}

void PageItem::prependRow(QGraphicsWidget *row)
{
    insertRow(0, row);
}

void PageItem::insertRow(int index, QGraphicsWidget *row)
{
    prepareWidgetForRow(row);
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

void PageItem::notify()
{
    LayoutSettings settings;
    QPageLayout layout = settings.pageLayout();
    setPageLayout(layout);
}
