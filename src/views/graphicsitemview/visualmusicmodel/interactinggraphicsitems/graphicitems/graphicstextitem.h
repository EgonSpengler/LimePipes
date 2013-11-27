/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GRAPHICSTEXTITEM_H
#define GRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>

class GraphicsTextItem : public QGraphicsTextItem
{
    Q_OBJECT

    friend class GraphicsTextItemTest;
    friend class TextWidgetTest;

public:
    explicit GraphicsTextItem(QGraphicsItem *parent = 0);

    void setAlignment(Qt::Alignment alignment);
    Qt::Alignment alignment() const;

signals:
    void focusOut();
    void focusIn();

private slots:
    void updateGeometry();

private:
    void focusOutEvent(QFocusEvent *event);
    void focusInEvent(QFocusEvent *event);
    Qt::Alignment m_alignment;
};

#endif // GRAPHICSTEXTITEM_H
