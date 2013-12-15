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
    using namespace Settings;

    qRegisterMetaType<Settings::TextAlignment>("Settings::TextAlignment");

    m_leftTextWidget = new TextWidget(this);
    m_leftTextWidget->setAlignment(Qt::AlignLeft);

    m_centerTextWidget = new TextWidget(this);
    m_centerTextWidget->setAlignment(Qt::AlignCenter);

    m_rightTextWidget = new TextWidget(this);
    m_rightTextWidget->setAlignment(Qt::AlignRight);

    setTextVisible(TextAlignment::Left, false);
    setTextVisible(TextAlignment::Center, false);
    setTextVisible(TextAlignment::Right, false);

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

void TextRowWidget::setText(Settings::TextAlignment position, const QString &text)
{
    TextWidget *textWidget = textWidgetForPosition(position);
    textWidget->setText(text);

    setTextVisible(position, !text.isEmpty());
}

QString TextRowWidget::text(Settings::TextAlignment position) const
{
    TextWidget *textWidget = textWidgetForPosition(position);
    return textWidget->text();
}

void TextRowWidget::setFont(Settings::TextAlignment position, const QFont &font)
{
    TextWidget *textWidget = textWidgetForPosition(position);
    textWidget->setFont(font);
}

QFont TextRowWidget::font(Settings::TextAlignment position) const
{
    TextWidget *textWidget = textWidgetForPosition(position);
    return textWidget->font();
}

void TextRowWidget::setColor(Settings::TextAlignment position, const QColor &color)
{
    TextWidget *textWidget = textWidgetForPosition(position);
    textWidget->setColor(color);
}

QColor TextRowWidget::color(Settings::TextAlignment position)
{
    TextWidget *textWidget = textWidgetForPosition(position);
    return textWidget->color();
}

void TextRowWidget::setTextVisible(Settings::TextAlignment position, bool visible)
{
    TextWidget *widget = textWidgetForPosition(position);
    widget->setVisible(visible);
}

bool TextRowWidget::isTextVisible(Settings::TextAlignment position) const
{
    TextWidget *widget = textWidgetForPosition(position);
    return widget->isVisible();
}

TextWidget *TextRowWidget::textWidget(Settings::TextAlignment position)
{
    switch (position) {
    case Settings::TextAlignment::Left:
        return m_leftTextWidget;
    case Settings::TextAlignment::Center:
        return m_centerTextWidget;
    case Settings::TextAlignment::Right:
        return m_rightTextWidget;
    case Settings::TextAlignment::NoAlignment:
        return 0;
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

    Settings::TextAlignment position = textPositionForWidget(textWidget);
    emit textChanged(position, textWidget->text());

    repositionElementTextItems();
}

void TextRowWidget::textWidgetSizeChanged()
{
    repositionElementTextItems();
}

Settings::TextAlignment TextRowWidget::textPositionForWidget(TextWidget *widget) const
{
    if (widget == m_leftTextWidget)
        return Settings::TextAlignment::Left;
    if (widget == m_centerTextWidget)
        return Settings::TextAlignment::Center;
    if (widget == m_rightTextWidget)
        return Settings::TextAlignment::Right;

    return Settings::TextAlignment::Left;
}

TextWidget *TextRowWidget::textWidgetForPosition(Settings::TextAlignment position) const
{
    switch (position) {
    case Settings::TextAlignment::Left: {
        return m_leftTextWidget;
    }
    case Settings::TextAlignment::Center: {
        return m_centerTextWidget;
    }
    case Settings::TextAlignment::Right: {
        return m_rightTextWidget;
    }
    default:
        return m_leftTextWidget;
    }
}
