/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GHB_MELODYNOTE_H
#define GHB_MELODYNOTE_H

#include <melodynote.h>
#include <ghb_symboltypes.h>
#include <pitch.h>
#include <length.h>

class GHB_MelodyNote : public MelodyNote
{
public:
    GHB_MelodyNote(PitchPtr pitch, Length::Value length)
        : MelodyNote(GHB::MelodyNote, "Melody Note")
    {
        initData(QVariant::fromValue<PitchPtr>(pitch), LP::symbolPitch);
        initData(QVariant::fromValue<Length::Value>(length), LP::symbolLength);
    }
};

#endif // GHB_MELODYNOTE_H
