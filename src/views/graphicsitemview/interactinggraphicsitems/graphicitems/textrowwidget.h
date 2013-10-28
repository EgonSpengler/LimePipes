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

class QSignalMapper;
class TextWidget;
class QGraphicsLinearLayout;

class TextRowWidget : public QGraphicsWidget
{
    Q_OBJECT

public:
    enum TextPosition {
        Left,
        Center,
        Right
    };

    explicit TextRowWidget(QGraphicsItem *parent = 0);

    void setText(TextPosition position, const QString& text);
    QString text(TextPosition position) const;

signals:
    void textChanged(TextRowWidget::TextPosition position, const QString& newText);

private slots:
    void textWidgetTextChanged(QObject *object);

private:
    void createConnections();
    TextWidget *textWidgetForPosition(TextPosition position) const;
    TextPosition textPositionForWidget(TextWidget *widget) const;
    QGraphicsLinearLayout *m_layout;
    TextWidget *m_leftTextWidget;
    TextWidget *m_centerTextWidget;
    TextWidget *m_rightTextWdget;
    QSignalMapper *m_signalMapper;
};

#endif // TEXTROWWIDGET_H
