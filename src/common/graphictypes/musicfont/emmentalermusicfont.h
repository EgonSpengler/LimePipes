/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef EMMENTALERMUSICFONT_H
#define EMMENTALERMUSICFONT_H

#include "musicfont.h"

class EmmentalerMusicFont : public MusicFont
{
public:
    explicit EmmentalerMusicFont(int staffLineHeight);

private:
    void addNumberGlyphs();
    void addCharGlyphs();
    void addRestGlyphs();
    void addAccidentalGlyphs();
    void addClefGlyphs();
    void addTimeSigGlyphs();
    void addNoteheadGlyphs();
    void addDotGlyphs();
    void addFlagGlyphs();
};

#endif // EMMENTALERMUSICFONT_H
