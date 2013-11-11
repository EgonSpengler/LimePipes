/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPainter>
#include <QTextDocument>
#include <QTextCursor>
#include <QAbstractTextDocumentLayout>
#include "graphicstextitem.h"
#include <QGraphicsSceneResizeEvent>
#include "textwidget.h"

TextWidget::TextWidget(QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      m_textItem(0)
{
    setMinimumWidth(10);
    m_textItem = new GraphicsTextItem(this);
    m_textItem->setTextInteractionFlags(Qt::TextEditorInteraction);

    setSizeFromTextItem();
    createConnections();
}

void TextWidget::setText(const QString &text)
{
    if (text == m_textItem->toPlainText())
        return;

    m_textItem->setPlainText(text);
}

QString TextWidget::text() const
{
    return m_textItem->toPlainText();
}

void TextWidget::setFont(const QFont &font)
{
    m_textItem->setFont(font);
    m_textItem->adjustSize();
}

void TextWidget::setColor(const QColor &color)
{
    m_textItem->setDefaultTextColor(color);
}

QColor TextWidget::color() const
{
    return m_textItem->defaultTextColor();
}

void TextWidget::setAlignment(Qt::Alignment alignment)
{
    m_textItem->setAlignment(alignment);
}

void TextWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setBrush(Qt::blue);
//    painter->drawRect(boundingRect());
}

void TextWidget::textItemDocumentSizeChanged(const QSizeF &size)
{
    setSizeFromTextItem();
    emit sizeChanged(m_textItem->boundingRect().size());
}

void TextWidget::setSizeFromTextItem()
{
    setMinimumSize(m_textItem->boundingRect().size());
    setMaximumSize(m_textItem->boundingRect().size());
}

void TextWidget::textItemFocusIn()
{
    m_textBeforeEdit = m_textItem->toPlainText();
}

void TextWidget::textItemFocusOut()
{
    setPreferredSize(m_textItem->boundingRect().size());
    QString newText = m_textItem->toPlainText();
    if (m_textBeforeEdit != newText) {
        emit textChanged(newText);
    }
}

void TextWidget::createConnections()
{
    connect(m_textItem->document()->documentLayout(), SIGNAL(documentSizeChanged(QSizeF)),
            this, SLOT(textItemDocumentSizeChanged(QSizeF)));
    connect(m_textItem, SIGNAL(focusIn()),
            this, SLOT(textItemFocusIn()));
    connect(m_textItem, SIGNAL(focusOut()),
            this, SLOT(textItemFocusOut()));
}

