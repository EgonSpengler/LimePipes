/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QTextBlockFormat>
#include <QTextCursor>
#include <QTextDocument>
#include "graphicstextitem.h"

GraphicsTextItem::GraphicsTextItem(QGraphicsItem *parent)
    : QGraphicsTextItem(parent),
      m_alignment(Qt::AlignLeft)
{
    updateGeometry();
    connect(document(), SIGNAL(contentsChanged()),
            this, SLOT(updateGeometry()));
}

void GraphicsTextItem::setAlignment(Qt::Alignment alignment)
{
    if (m_alignment == alignment)
        return;

    m_alignment = alignment;

    QTextOption textOption(document()->defaultTextOption());
    textOption.setAlignment(alignment);
    document()->setDefaultTextOption(textOption);

    QTextBlockFormat format;
    format.setAlignment(alignment);

    QTextCursor cursor(textCursor());
    cursor.select(QTextCursor::Document);
    cursor.setBlockFormat(format);
    cursor.clearSelection();

    setTextCursor(cursor);
}

void GraphicsTextItem::updateGeometry()
{
    setTextWidth(-1);
    setTextWidth(boundingRect().width());
    setAlignment(m_alignment);
}

void GraphicsTextItem::focusOutEvent(QFocusEvent *event)
{
    QGraphicsTextItem::focusOutEvent(event);
    emit focusOut();
}

void GraphicsTextItem::focusInEvent(QFocusEvent *event)
{
    QGraphicsTextItem::focusInEvent(event);
    emit focusIn();
}
