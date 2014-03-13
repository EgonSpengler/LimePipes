/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "ghb_melodynote.h"

GHB_MelodyNote::GHB_MelodyNote(PitchPtr pitch, Length::Value length)
    : MelodyNote()
{
    initData(QVariant::fromValue<PitchPtr>(pitch), LP::SymbolPitch);
    initData(QVariant::fromValue<Length::Value>(length), LP::SymbolLength);
}
