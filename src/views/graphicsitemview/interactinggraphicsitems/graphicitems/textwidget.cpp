/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPainter>
#include <QTextDocument>
#include "graphicstextitem.h"
#include <QGraphicsSceneResizeEvent>
#include "textwidget.h"

TextWidget::TextWidget(QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      m_textItem(0)
{
    setAutoFillBackground(true);
    m_textItem = new GraphicsTextItem(this);
    m_textItem->setTextInteractionFlags(Qt::TextEditorInteraction);

    createConnections();
    textItemBlockCountChanged();
}

void TextWidget::setText(const QString &text)
{
    m_textItem->setPlainText(text);
}

QString TextWidget::text() const
{
    return m_textItem->toPlainText();
}

void TextWidget::textItemBlockCountChanged()
{
    m_textItem->adjustSize();
    m_textItem->setTextWidth(boundingRect().width());
    setPreferredHeight(m_textItem->document()->size().height());
}

void TextWidget::textItemFocusIn()
{
    m_textBeforeEdit = m_textItem->toPlainText();
}

void TextWidget::textItemFocusOut()
{
    QString newText = m_textItem->toPlainText();
    if (m_textBeforeEdit != newText)
        emit textChanged(newText);
}

void TextWidget::createConnections()
{
    connect(m_textItem->document(), SIGNAL(blockCountChanged(int)),
            this, SLOT(textItemBlockCountChanged()));
    connect(m_textItem, SIGNAL(focusIn()),
            this, SLOT(textItemFocusIn()));
    connect(m_textItem, SIGNAL(focusOut()),
            this, SLOT(textItemFocusOut()));
}

void TextWidget::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    m_textItem->setTextWidth(event->newSize().width());
}
