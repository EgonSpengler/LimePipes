/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef DEFINES_H
#define DEFINES_H

#include <QMetaType>

enum class StaffType
{
    None,       //!< No lines, e.g. for vocals
    Standard,   //!< The standard 5 line staff
    Unpitched   //!< A one-line-staff for unpitched instruments
};

enum class SymbolCategory
{
    Control,    //!< Non visible control symbols (e.g. part 1 of 2)
    Graphical,  //!< Visible symbols with pixmaps (e.g. melody notes)
    Text        //!< Visible symbols presentable as text
};

Q_DECLARE_METATYPE(StaffType)
Q_DECLARE_METATYPE(SymbolCategory)

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
    MelodyNote
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

#endif // DEFINES_H
