/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class GreatHighlandBagpipe
  * The Instrument plugin for the Great Highland Bagpipe.
  */

#include "greathighlandbagpipe.h"
#include <ghb_melodynote.h>
#include <ghb_doubling.h>
#include <bar.h>

Symbol *GreatHighlandBagpipe::getSymbol(const QString &symbol)
{
    if (symbol == tr("Melody Note")) {
        return new GHB_MelodyNote(m_bagpipe->pitchContext()->pitchForStaffPos(0), Length::_4);
    }
    if (symbol == tr("Bar")) {
        return new Bar();
    }
    if (symbol == tr("Doubling")) {
        return new GHB_Doubling();
    }
    return new Symbol();
}

GreatHighlandBagpipe::GreatHighlandBagpipe()
    : m_bagpipe(InstrumentPtr(new GHB_Instrument()))
{
}

Q_EXPORT_PLUGIN2(lp_greathighlandbagpipe, GreatHighlandBagpipe)
