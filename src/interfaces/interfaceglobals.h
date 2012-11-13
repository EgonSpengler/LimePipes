/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @namespace LP
  * Contains global definitions
  *
  * @enum LP::InstrumentType
  * The predefined Instrument types.
  * This numeric values will be used to identify a Instrument and will be stored into
  * files. Therefore the value for a Instrument should never change.
  * @var LP::InstrumentType LP::NoInstrument
  * A defauld value which is used for @ref Instrument "Instruments" default constructor.
  *
  * @enum LP::IntegratedSymbolTypes
  * Symbols, that are used by more than one Instrument. E.g. @ref MelodyNote "MelodyNotes"
  *
  * @enum LP::FirstSymbolTypeForInstrument
  * To defineSymbol types directly in a plugin, the first numeric type is defined here.
  * For example the Great Highland Bagpipe specific Embellishments can be defined as followed:
  * @code
  * const int DoublingType    = GreatHighlandBagpipeSymbol;
  * const int GripType        = GreatHighlandBagpipeSymbol + 1;
  * const int SingleGraceType = GreatHighlandBagpipeSymbol + 2;
  * @endcode
  */

#ifndef INSTRUMENT_GLOBALS_H
#define INSTRUMENT_GLOBALS_H

#define GET_FIRST_SYMBOL_TYPE(InstrumentID) InstrumentID * 200 + 300

namespace LP {

enum InstrumentType {
    NoInstrument  = 1,
    GreatHighlandBagpipe,
    ScottishSideDrum,
    BassDrum,
    TenorDrum,
    TinWhistle,
    Vocals
};

enum IntegratedSymbolTypes {
    NoSymbolType = 1,
    MelodyNote,
    BarLine
};

enum FirstSymbolTypeForInstrument {
    GreatHighlandBagpipeSymbol  = GET_FIRST_SYMBOL_TYPE(GreatHighlandBagpipe),
    ScottishSideDrumSymbol      = GET_FIRST_SYMBOL_TYPE(ScottishSideDrum),
    BassDrumSymbol              = GET_FIRST_SYMBOL_TYPE(BassDrum),
    TenorDrumSymbol             = GET_FIRST_SYMBOL_TYPE(TenorDrum),
    TinWhistleSymbol            = GET_FIRST_SYMBOL_TYPE(TinWhistle),
    VocalsSymbol                = GET_FIRST_SYMBOL_TYPE(Vocals)
};

}

#endif // INSTRUMENT_GLOBALS_H
