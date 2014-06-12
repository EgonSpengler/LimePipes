/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "baseengraver.h"

BaseEngraver::BaseEngraver()
{
}

MusicFontPtr BaseEngraver::musicFont() const
{
    return m_musicFont;
}

void BaseEngraver::setMusicFont(const MusicFontPtr &musicFont)
{
    if (m_musicFont == musicFont)
        return;

    m_musicFont = musicFont;
    musicFontHasChanged(m_musicFont);
}

