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
    enum RowAlignment {
        Left,
        Center,
        Right
    };

    explicit TextRowWidget(QGraphicsItem *parent = 0);

    void setText(RowAlignment position, const QString& text);
    QString text(RowAlignment position) const;

    void setFont(RowAlignment position, const QFont& font);
    QFont font(RowAlignment position) const;

    void setColor(RowAlignment position, const QColor& color);
    void color(RowAlignment position);

    void setTextPositionVisible(RowAlignment position, bool active);

    void setGeometry(const QRectF &rect);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void textChanged(TextRowWidget::RowAlignment position, const QString& newText);

private slots:
    void textWidgetTextChanged(QObject *object);
    void textWidgetSizeChanged(const QSizeF& newSize);

private:
    void createConnections();
    void repositionElementTextItems();
    TextWidget *textWidgetForPosition(RowAlignment position) const;
    RowAlignment textPositionForWidget(TextWidget *widget) const;
    QGraphicsLinearLayout *m_layout;
    TextWidget *m_leftTextWidget;
    TextWidget *m_centerTextWidget;
    TextWidget *m_rightTextWidget;
    QSignalMapper *m_signalMapper;
};

#endif // TEXTROWWIDGET_H
