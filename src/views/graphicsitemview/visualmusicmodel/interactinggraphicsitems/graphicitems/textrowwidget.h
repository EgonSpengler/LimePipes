/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TEXTROWWIDGET_H
#define TEXTROWWIDGET_H

#include <QMetaType>
#include <common/settingdefines.h>
#include <QGraphicsWidget>

class QSignalMapper;
class TextWidget;
class QGraphicsLinearLayout;

class TextRowWidget : public QGraphicsWidget
{
    Q_OBJECT

public:
    explicit TextRowWidget(QGraphicsItem *parent = 0);

    void setText(Settings::TextAlignment position, const QString& text);
    QString text(Settings::TextAlignment position) const;

    void setFont(Settings::TextAlignment position, const QFont& font);
    QFont font(Settings::TextAlignment position) const;

    void setColor(Settings::TextAlignment position, const QColor& color);
    QColor color(Settings::TextAlignment position);

    void setTextVisible(Settings::TextAlignment position, bool visible);
    bool isTextVisible(Settings::TextAlignment position) const;

    TextWidget *textWidget(Settings::TextAlignment position);

    void setGeometry(const QRectF &rect);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void textChanged(Settings::TextAlignment position, const QString& newText);

private slots:
    void textWidgetTextChanged(TextWidget *textWidget);
    void textWidgetSizeChanged();

private:
    void createConnections();
    void repositionElementTextItems();
    TextWidget *textWidgetForPosition(Settings::TextAlignment position) const;
    Settings::TextAlignment textPositionForWidget(TextWidget *widget) const;
    TextWidget *m_leftTextWidget;
    TextWidget *m_centerTextWidget;
    TextWidget *m_rightTextWidget;
};

#endif // TEXTROWWIDGET_H
