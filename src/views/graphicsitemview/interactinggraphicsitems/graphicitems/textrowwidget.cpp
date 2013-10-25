/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QGraphicsLinearLayout>
#include "textwidget.h"
#include "textrowwidget.h"

TextRowWidget::TextRowWidget(QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      m_layout(0),
      m_leftTextWidget(0),
      m_centerTextWidget(0),
      m_rightTextWdget(0)
{
    m_leftTextWidget = new TextWidget();
    m_centerTextWidget = new TextWidget();
    m_rightTextWdget = new TextWidget();

    m_layout = new QGraphicsLinearLayout(Qt::Horizontal, this);
    m_layout->addItem(m_leftTextWidget);
    m_layout->addItem(m_centerTextWidget);
    m_layout->addItem(m_rightTextWdget);
}

void TextRowWidget::setText(TextRowWidget::TextPosition position, const QString &text)
{
    TextWidget *textWidget = textWidgetForPosition(position);
    textWidget->setText(text);
}

QString TextRowWidget::text(TextRowWidget::TextPosition position) const
{
    TextWidget *textWidget = textWidgetForPosition(position);
    return textWidget->text();
}

TextWidget *TextRowWidget::textWidgetForPosition(TextRowWidget::TextPosition position) const
{
    switch (position) {
    case Left: {
        return m_leftTextWidget;
    }
    case Center: {
        return m_centerTextWidget;
    }
    case Right: {
        return m_rightTextWdget;
    }
    default:
        return m_leftTextWidget;
    }
}
