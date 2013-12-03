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
#include <QGraphicsWidget>

class QSignalMapper;
class TextWidget;
class QGraphicsLinearLayout;

class TextRowWidget : public QGraphicsWidget
{
    Q_OBJECT

public:
    enum RowAlignment {
        NoAlignment,
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
    QColor color(RowAlignment position);

    void setTextVisible(RowAlignment position, bool visible);
    bool isTextVisible(RowAlignment position) const;

    TextWidget *textWidget(RowAlignment position);

    void setGeometry(const QRectF &rect);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void textChanged(TextRowWidget::RowAlignment position, const QString& newText);

private slots:
    void textWidgetTextChanged(TextWidget *textWidget);
    void textWidgetSizeChanged();

private:
    void createConnections();
    void repositionElementTextItems();
    TextWidget *textWidgetForPosition(RowAlignment position) const;
    RowAlignment textPositionForWidget(TextWidget *widget) const;
    TextWidget *m_leftTextWidget;
    TextWidget *m_centerTextWidget;
    TextWidget *m_rightTextWidget;
};

Q_DECLARE_METATYPE(TextRowWidget::RowAlignment)

#endif // TEXTROWWIDGET_H
