/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GLYPHITEM_H
#define GLYPHITEM_H

#include <QGraphicsItem>

class GlyphItem : public QGraphicsItem
{
public:
    explicit GlyphItem(const QString& glyphName, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void initFromGlyphName(const QString& glyphName);

};

#endif // GLYPHITEM_H
