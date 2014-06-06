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
#include <common/graphictypes/MusicFont/musicfont.h>
#include <common/defines.h>
#include <QGraphicsItem>

class GlyphItem : public QGraphicsItem
{
public:
    explicit GlyphItem(QGraphicsItem *parent = 0);
    explicit GlyphItem(const QString& glyphName, QGraphicsItem *parent = 0);

    enum { Type = SymbolGlyphItemType };
    int type() const { return Type; }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /*!
     * \brief glyphName The name of the glyph. If a subclass is only a container for more GlyphItems,
     *        it can return the name of the right glyph item. This should be the glyph
     * \return
     */
    virtual QString glyphName() const;

    /*!
     * \brief glyphData Returns the GlyphData in item coordinates. If a subclass of GlyphItem
     *        is only a container for more GlyphItems, it can reimplement this method to return
     *        the right positions.
     * \return  The GlyphData
     */
    virtual GlyphData itemGlyphData() const;

    void setGlyphName(const QString &glyphName);

    MusicFontPtr musicFont() const;
    void setMusicFont(const MusicFontPtr &musicFont);

    void setColorRole(const FontColor &colorRole);
    FontColor colorRole() const;

protected:
    virtual void musicFontHasChanged(const MusicFontPtr &musicFont) { Q_UNUSED(musicFont); }
    virtual void colorRoleHasChanged(const FontColor &colorRole) { Q_UNUSED(colorRole); }
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    GlyphData glyphDataToItemCoordinates(const GlyphData &itemGlyphData) const;

private:
    void initFromGlyphName(const QString& glyphName);
    QString m_glyphName;
    QChar m_char;
    MusicFontPtr m_musicFont;
    QRectF m_boundingRect;
    FontColor m_colorRole;
};

#endif // GLYPHITEM_H
