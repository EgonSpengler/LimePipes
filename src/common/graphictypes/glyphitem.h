/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GLYPHITEM_H
#define GLYPHITEM_H

#include <QChar>
#include <QRectF>
#include <common/graphictypes/SMuFL/smufl.h>
#include <QGraphicsItem>

class GlyphItem : public QGraphicsItem
{
public:
    explicit GlyphItem(QGraphicsItem *parent = 0);
    explicit GlyphItem(const QString& glyphName, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QString glyphName() const;
    void setGlyphName(const QString &glyphName);

    SMuFLPtr smufl() const;
    void setSmufl(const SMuFLPtr &smufl);

protected:
    virtual void smuflHasChanged(const SMuFLPtr &smufl) { Q_UNUSED(smufl); }

private:
    void initFromGlyphName(const QString& glyphName);
    QString m_glyphName;
    QChar m_char;
    SMuFLPtr m_smufl;
    QRectF m_boundingRect;
};

#endif // GLYPHITEM_H
