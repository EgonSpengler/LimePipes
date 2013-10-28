/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QSignalMapper>
#include <QGraphicsLinearLayout>
#include "textwidget.h"
#include "textrowwidget.h"

TextRowWidget::TextRowWidget(QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      m_layout(0),
      m_leftTextWidget(0),
      m_centerTextWidget(0),
      m_rightTextWdget(0),
      m_signalMapper(0)
{
    m_leftTextWidget = new TextWidget();

    m_centerTextWidget = new TextWidget();
    m_rightTextWdget = new TextWidget();
    m_signalMapper = new QSignalMapper(this);
    m_signalMapper->setMapping(m_leftTextWidget, m_leftTextWidget);
    m_signalMapper->setMapping(m_centerTextWidget, m_centerTextWidget);
    m_signalMapper->setMapping(m_rightTextWdget, m_rightTextWdget);

    m_layout = new QGraphicsLinearLayout(Qt::Horizontal, this);
    m_layout->addItem(m_leftTextWidget);
    m_layout->addItem(m_centerTextWidget);
    m_layout->addItem(m_rightTextWdget);

    createConnections();
}

void TextRowWidget::createConnections()
{
    connect(m_leftTextWidget, SIGNAL(textChanged(QString)),
            m_signalMapper, SLOT(map()));
    connect(m_centerTextWidget, SIGNAL(textChanged(QString)),
            m_signalMapper, SLOT(map()));
    connect(m_rightTextWdget, SIGNAL(textChanged(QString)),
            m_signalMapper, SLOT(map()));
    connect(m_signalMapper, SIGNAL(mapped(QObject*)),
            this, SLOT(textWidgetTextChanged(QObject*)));
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

void TextRowWidget::textWidgetTextChanged(QObject *object)
{
    TextWidget *widget = qobject_cast<TextWidget*>(object);
    if (!widget) return;

    TextRowWidget::TextPosition position = textPositionForWidget(widget);
    emit textChanged(position, widget->text());
}

TextRowWidget::TextPosition TextRowWidget::textPositionForWidget(TextWidget *widget) const
{
    if (widget == m_leftTextWidget)
        return Left;
    if (widget == m_centerTextWidget)
        return Center;
    if (widget == m_rightTextWdget)
        return Right;

    return Left;
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
