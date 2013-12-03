/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPainter>
#include <QTextCursor>
#include <QSignalMapper>
#include <QGraphicsLinearLayout>
#include "textwidget.h"
#include "textrowwidget.h"

TextRowWidget::TextRowWidget(QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      m_leftTextWidget(0),
      m_centerTextWidget(0),
      m_rightTextWidget(0)
{
    qRegisterMetaType<TextRowWidget::RowAlignment>("TextRowWidget::RowAlignment");

    m_leftTextWidget = new TextWidget(this);
    m_leftTextWidget->setAlignment(Qt::AlignLeft);

    m_centerTextWidget = new TextWidget(this);
    m_centerTextWidget->setAlignment(Qt::AlignCenter);

    m_rightTextWidget = new TextWidget(this);
    m_rightTextWidget->setAlignment(Qt::AlignRight);

    setTextVisible(Left, false);
    setTextVisible(Center, false);
    setTextVisible(Right, false);

    createConnections();
}

void TextRowWidget::createConnections()
{
    connect(m_leftTextWidget, &TextWidget::textChanged,
            [this] { textWidgetTextChanged(m_leftTextWidget); });
    connect(m_leftTextWidget, &TextWidget::sizeChanged,
            this, &TextRowWidget::textWidgetSizeChanged);

    connect(m_centerTextWidget, &TextWidget::textChanged,
            [this] { textWidgetTextChanged(m_centerTextWidget); });
    connect(m_centerTextWidget, &TextWidget::sizeChanged,
            this, &TextRowWidget::textWidgetSizeChanged);

    connect(m_rightTextWidget, &TextWidget::textChanged,
            [this] { textWidgetTextChanged(m_rightTextWidget); });
    connect(m_rightTextWidget, &TextWidget::sizeChanged,
            this, &TextRowWidget::textWidgetSizeChanged);
}

void TextRowWidget::repositionElementTextItems()
{
    qreal textWidth = 0;
    qreal textXPos = 0;

    // Left text
    m_leftTextWidget->setPos(0, 0);

    // Center text
    textWidth = m_centerTextWidget->boundingRect().width();
    textXPos = (geometry().width() - textWidth) / 2;
    m_centerTextWidget->setPos(textXPos, 0);

    // Right text
    textWidth = m_rightTextWidget->boundingRect().width();
    textXPos = geometry().width() - textWidth;
    m_rightTextWidget->setPos(textXPos, 0);

    qreal maxHeight = qMax(m_leftTextWidget->boundingRect().height(),
                           m_centerTextWidget->boundingRect().height());
    maxHeight = qMax(m_rightTextWidget->boundingRect().height(),
                     maxHeight);
    setPreferredHeight(maxHeight);
}

void TextRowWidget::setText(TextRowWidget::RowAlignment position, const QString &text)
{
    TextWidget *textWidget = textWidgetForPosition(position);
    textWidget->setText(text);

    setTextVisible(position, !text.isEmpty());
}

QString TextRowWidget::text(TextRowWidget::RowAlignment position) const
{
    TextWidget *textWidget = textWidgetForPosition(position);
    return textWidget->text();
}

void TextRowWidget::setFont(TextRowWidget::RowAlignment position, const QFont &font)
{
    TextWidget *textWidget = textWidgetForPosition(position);
    textWidget->setFont(font);
}

QFont TextRowWidget::font(TextRowWidget::RowAlignment position) const
{
    TextWidget *textWidget = textWidgetForPosition(position);
    return textWidget->font();
}

void TextRowWidget::setColor(TextRowWidget::RowAlignment position, const QColor &color)
{
    TextWidget *textWidget = textWidgetForPosition(position);
    textWidget->setColor(color);
}

QColor TextRowWidget::color(TextRowWidget::RowAlignment position)
{
    TextWidget *textWidget = textWidgetForPosition(position);
    return textWidget->color();
}

void TextRowWidget::setTextVisible(TextRowWidget::RowAlignment position, bool visible)
{
    TextWidget *widget = textWidgetForPosition(position);
    widget->setVisible(visible);
}

bool TextRowWidget::isTextVisible(TextRowWidget::RowAlignment position) const
{
    TextWidget *widget = textWidgetForPosition(position);
    return widget->isVisible();
}

TextWidget *TextRowWidget::textWidget(TextRowWidget::RowAlignment position)
{
    switch (position) {
    case TextRowWidget::Left:
        return m_leftTextWidget;
        break;
    case TextRowWidget::Center:
        return m_centerTextWidget;
        break;
    case TextRowWidget::Right:
        return m_rightTextWidget;
        break;
    case TextRowWidget::NoAlignment:
        break;
    }

    return 0;
}

void TextRowWidget::setGeometry(const QRectF &rect)
{
    QGraphicsWidget::setGeometry(rect);

    repositionElementTextItems();
}

void TextRowWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->drawRect(boundingRect());
}

void TextRowWidget::textWidgetTextChanged(TextWidget *textWidget)
{
    if (!textWidget) return;

    TextRowWidget::RowAlignment position = textPositionForWidget(textWidget);
    emit textChanged(position, textWidget->text());

    repositionElementTextItems();
}

void TextRowWidget::textWidgetSizeChanged()
{
    repositionElementTextItems();
}

TextRowWidget::RowAlignment TextRowWidget::textPositionForWidget(TextWidget *widget) const
{
    if (widget == m_leftTextWidget)
        return Left;
    if (widget == m_centerTextWidget)
        return Center;
    if (widget == m_rightTextWidget)
        return Right;

    return Left;
}

TextWidget *TextRowWidget::textWidgetForPosition(TextRowWidget::RowAlignment position) const
{
    switch (position) {
    case Left: {
        return m_leftTextWidget;
    }
    case Center: {
        return m_centerTextWidget;
    }
    case Right: {
        return m_rightTextWidget;
    }
    default:
        return m_leftTextWidget;
    }
}
