/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musicmodeltestplugin.h"
#include <QtPlugin>

Symbol *MusicModelTestPlugin::getSymbol(const QString &symbol)
{
    if (symbol == "Testsymbol") {
        return new Symbol(LP::MelodyNote, "Testsymbol");
    }
    if (symbol == symbolNameWithPitchAndLength) {
        int staffPosOfDefaultPitch = m_instrument->pitchContext()->highestStaffPos();
        return new TestsymbolWithPitchAndLength(m_instrument->pitchContext()->pitchForStaffPos(staffPosOfDefaultPitch));
    }
    return new Symbol();
}

Q_EXPORT_PLUGIN2(lp_musicmodeltestplugin, MusicModelTestPlugin)
