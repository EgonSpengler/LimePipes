/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QGraphicsWidget>

class GraphicsTextItem;
class QGraphicsTextItem;

class TextWidget : public QGraphicsWidget
{
    Q_OBJECT

    friend class TextWidgetTest;

public:
    explicit TextWidget(QGraphicsItem *parent = 0);

    void setText(const QString& text);
    QString text() const;

    void setFont(const QFont &font);
    QFont font() const;

    void setColor(const QColor& color);
    QColor color() const;

    void setAlignment(Qt::Alignment alignment);
    Qt::Alignment alignment() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void textChanged(const QString& text);
    void sizeChanged(const QSizeF& newSize);

private slots:
    void textItemDocumentSizeChanged(const QSizeF& size);
    void textItemFocusIn();
    void textItemFocusOut();

private:
    void createConnections();
    void setSizeFromTextItem();
    GraphicsTextItem *m_textItem;
    QString m_textBeforeEdit;
};

#endif // TEXTWIDGET_H
