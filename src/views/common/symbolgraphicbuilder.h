/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLGRAPHICBUILDER_H
#define SYMBOLGRAPHICBUILDER_H

#include <QVariant>
#include "symbolgraphic.h"
#include "musicfont/musicfont.h"

class SymbolGraphicBuilder
{
public:
    explicit SymbolGraphicBuilder();
    virtual ~SymbolGraphicBuilder() {}

    SymbolGraphicPtr symbolGraphic() { return m_graphic; }

    void setLineHeight(int lineHeight);
    qreal lineHeight() const;

public slots:
    virtual void createPixmaps(int lineHeight) = 0;
    virtual void updateSymbolGraphic() = 0;
    virtual bool isSymbolGraphicAffectedByDataRole(int role) = 0;

protected:
    MusicFontPtr musicFont() { return s_musicFont; }
    QVariant itemData(int role) { return QVariant(); }

    void setSymbolGraphicPixmap(const QPixmap &pixmap) { m_graphic->setPixmap(pixmap); }
    void setSymbolGraphicYOffset(qreal yOffset) { m_graphic->setYOffset(yOffset); }

private:
    void initSymbolGraphic();
//    MusicItem *m_item;  // There has to be a new way of getting data, not MusicItem
    SymbolGraphicPtr m_graphic;
    static MusicFontPtr s_musicFont;
};

#endif // SYMBOLGRAPHICBUILDER_H
