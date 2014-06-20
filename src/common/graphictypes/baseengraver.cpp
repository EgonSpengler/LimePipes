/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/layoutsettings.h>

#include "baseengraver.h"

BaseEngraver::BaseEngraver()
{
    setMusicFont(LayoutSettings::musicFont());
    QObject::connect(LayoutSettings::musicFont().data(), &MusicFont::fontChanged,
                     [this] {
        setMusicFont(LayoutSettings::musicFont());
    });
}

MusicFontPtr BaseEngraver::musicFont() const
{
    return m_musicFont;
}

void BaseEngraver::setMusicFont(const MusicFontPtr &musicFont)
{
    m_musicFont = musicFont;
    musicFontHasChanged(m_musicFont);
}

