/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TEXTROWWIDGET_H
#define TEXTROWWIDGET_H

#include <QGraphicsWidget>

class TextWidget;
class QGraphicsLinearLayout;

class TextRowWidget : public QGraphicsWidget
{
public:
    enum TextPosition {
        Left,
        Center,
        Right
    };

    explicit TextRowWidget(QGraphicsItem *parent = 0);

    void setText(TextPosition position, const QString& text);
    QString text(TextPosition position) const;

private:
    TextWidget *textWidgetForPosition(TextPosition position) const;
    QGraphicsLinearLayout *m_layout;
    TextWidget *m_leftTextWidget;
    TextWidget *m_centerTextWidget;
    TextWidget *m_rightTextWdget;
};

#endif // TEXTROWWIDGET_H
