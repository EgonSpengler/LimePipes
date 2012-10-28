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

const int MelodyNote::MaxDots;

MelodyNote::MelodyNote()
    : Symbol(LP::MelodyNote, tr("Melody Note"))
{
    initSymbol();
}

MelodyNote::MelodyNote(int type, const QString &name)
    : Symbol(type, name)
{
    initSymbol();
}

bool MelodyNote::itemSupportsWritingOfData(int role) const
{
    if (role == LP::melodyNoteDots)
        return true;
    return Symbol::itemSupportsWritingOfData(role);
}

void MelodyNote::beforeWritingData(QVariant &value, int role)
{
    if (!value.isValid())
        return;

    if (role == LP::melodyNoteDots &&
            value.canConvert<int>()) {
        if (value.value<int>() < 0)
            value.setValue(0);
        if (value.value<int>() > MelodyNote::MaxDots)
            value.setValue(MelodyNote::MaxDots);
    }
}

void MelodyNote::initSymbol()
{
    initData(0, LP::melodyNoteDots);
    setSymbolOptions(Symbol::HasPitch |
                     Symbol::HasLength);
    setSymbolGraphicBuilder(new MelodyNoteGraphicBuilder(this));
}
