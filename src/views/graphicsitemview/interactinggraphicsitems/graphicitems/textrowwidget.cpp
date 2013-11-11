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
      m_layout(0),
      m_leftTextWidget(0),
      m_centerTextWidget(0),
      m_rightTextWidget(0),
      m_signalMapper(0)
{
    m_leftTextWidget = new TextWidget(this);
    m_leftTextWidget->setAlignment(Qt::AlignLeft);

    m_centerTextWidget = new TextWidget(this);
    m_centerTextWidget->setAlignment(Qt::AlignCenter);

    m_rightTextWidget = new TextWidget(this);
    m_rightTextWidget->setAlignment(Qt::AlignRight);

    m_signalMapper = new QSignalMapper(this);
    m_signalMapper->setMapping(m_leftTextWidget, m_leftTextWidget);
    m_signalMapper->setMapping(m_centerTextWidget, m_centerTextWidget);
    m_signalMapper->setMapping(m_rightTextWidget, m_rightTextWidget);

    setTextPositionVisible(Left, false);
    setTextPositionVisible(Center, false);
    setTextPositionVisible(Right, false);

    createConnections();
}

void TextRowWidget::createConnections()
{
    connect(m_leftTextWidget, SIGNAL(sizeChanged(QSizeF)),
            this, SLOT(textWidgetSizeChanged(QSizeF)));
    connect(m_centerTextWidget, SIGNAL(sizeChanged(QSizeF)),
            this, SLOT(textWidgetSizeChanged(QSizeF)));
    connect(m_rightTextWidget, SIGNAL(sizeChanged(QSizeF)),
            this, SLOT(textWidgetSizeChanged(QSizeF)));
    connect(m_leftTextWidget, SIGNAL(textChanged(QString)),
            m_signalMapper, SLOT(map()));
    connect(m_centerTextWidget, SIGNAL(textChanged(QString)),
            m_signalMapper, SLOT(map()));
    connect(m_rightTextWidget, SIGNAL(textChanged(QString)),
            m_signalMapper, SLOT(map()));
    connect(m_signalMapper, SIGNAL(mapped(QObject*)),
            this, SLOT(textWidgetTextChanged(QObject*)));
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

    setTextPositionVisible(position, !text.isEmpty());
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

void TextRowWidget::setColor(TextRowWidget::RowAlignment position, const QColor &color)
{
    TextWidget *textWidget = textWidgetForPosition(position);
    textWidget->setColor(color);
}

void TextRowWidget::color(TextRowWidget::RowAlignment position)
{
    TextWidget *textWidget = textWidgetForPosition(position);
    textWidget->color();
}

void TextRowWidget::setTextPositionVisible(TextRowWidget::RowAlignment position, bool visible)
{
    TextWidget *widget = textWidgetForPosition(position);
    widget->setVisible(visible);
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

void TextRowWidget::textWidgetTextChanged(QObject *object)
{
    TextWidget *widget = qobject_cast<TextWidget*>(object);
    if (!widget) return;

    TextRowWidget::RowAlignment position = textPositionForWidget(widget);
    emit textChanged(position, widget->text());

    repositionElementTextItems();
}

void TextRowWidget::textWidgetSizeChanged(const QSizeF &newSize)
{
    Q_UNUSED(newSize);
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
