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

public:
    explicit GraphicsTextItem(QGraphicsItem *parent = 0);

signals:
    void focusOut();
    void focusIn();

private:
    void focusOutEvent(QFocusEvent *event);
    void focusInEvent(QFocusEvent *event);
};

#endif // GRAPHICSTEXTITEM_H
