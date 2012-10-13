/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class MelodyNote
  * A @ref Symbol "melody note symbol".
  */

#include "melodynote.h"

MelodyNote::MelodyNote()
    : Symbol(LP::MelodyNote, tr("Melody Note"))
{
    initSymbolOptions();
}

MelodyNote::MelodyNote(int type, const QString &name)
    : Symbol(type, name)
{
    initSymbolOptions();
}

void MelodyNote::initSymbolOptions()
{
    setSymbolOptions(Symbol::HasPitch |
                     Symbol::HasLength);
}


