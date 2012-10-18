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
    GHB_MelodyNote(PitchPtr pitch, Length::Value length);
};

#endif // GHB_MELODYNOTE_H
