/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef BASEENGRAVER_H
#define BASEENGRAVER_H

#include <common/graphictypes/MusicFont/musicfont.h>

class SymbolGraphicBuilder;

class BaseEngraver
{
public:
    BaseEngraver();
    virtual ~BaseEngraver() {}

    virtual void insertGraphicsBuilder(int index, SymbolGraphicBuilder *builder) {}
    virtual void removeGraphicsBuilder(SymbolGraphicBuilder *builder) {}

    MusicFontPtr musicFont() const;
    void setMusicFont(const MusicFontPtr &musicFont);

protected:
    virtual void musicFontHasChanged(const MusicFontPtr &musicFont) {}

private:
    MusicFontPtr m_musicFont;
};

#endif // BASEENGRAVER_H
