/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef DEFINES_H
#define DEFINES_H

#include <QString>
#include <QDebug>
#include <QGraphicsItem>
#include <QMetaType>

enum class StaffType
{
    None,       //!< No lines, e.g. for vocals
    Standard,   //!< The standard 5 line staff
    Unpitched   //!< A one-line-staff for unpitched instruments
};
Q_DECLARE_METATYPE(StaffType)

enum class ClefType
{
    // G-Clefs
    FrenchViolin = 1,
    Treble = 2,
    G = ClefType::Treble,  // The most common G-Clef

    // C-Clefs
    Soprano = 3,
    MezzoSoprano = 4,
    Alto = 5,
    Tenor = 6,
    BaritoneC = 7,
    C = ClefType::Alto,  // The most common C-Clef

    // F-Clefs
    BaritoneF = 8,
    Bass = 9,
    Subbass = 10,
    F = ClefType::Bass

};
Q_DECLARE_METATYPE(ClefType)

enum class SymbolCategory
{
    None,    //!< Non visible control symbols (e.g. part 1 of 2)
    Graphical,  //!< Visible symbols with graphics created by a SymbolGraphicBuilder
    Spanning,   //!< Visible symbols which consist of an start and end symbol
    Text        //!< Visible symbols presentable as text
};
Q_DECLARE_METATYPE(SymbolCategory)

enum class SymbolSpanType
{
    Start = 1,
    End
};
Q_DECLARE_METATYPE(SymbolSpanType)

enum GraphicsItemType {
    NoGraphicsItemType = QGraphicsItem::UserType,
    InteractingGraphicsItemType = QGraphicsItem::UserType + 1,
    StaffGraphicsItemType = QGraphicsItem::UserType + 2,
    MeasureGraphicsItemType = QGraphicsItem::UserType + 3,
    SymbolGraphicsItemType = QGraphicsItem::UserType + 4,
    SymbolGlyphItemType = QGraphicsItem::UserType + 5,

    PageViewItemType = QGraphicsItem::UserType + 6,
    PageItemType = QGraphicsItem::UserType + 7,
};

inline QDebug operator <<(QDebug dbg, const GraphicsItemType & type)
{
    switch (type) {
    case (InteractingGraphicsItemType):
        dbg.nospace() << QStringLiteral("Interacting Item");
        break;
    case (StaffGraphicsItemType):
        dbg.nospace() << QStringLiteral("Staff Item");
        break;
    case (MeasureGraphicsItemType):
        dbg.nospace() << QStringLiteral("Measure Item");
        break;
    case (SymbolGraphicsItemType):
        dbg.nospace() << QStringLiteral("Symbol Item");
        break;
    case (SymbolGlyphItemType):
        dbg.nospace() << QStringLiteral("Symbol glyph Item");
        break;
    case (PageViewItemType):
        dbg.nospace() << QStringLiteral("Page View Item");
        break;
    case (PageItemType):
        dbg.nospace() << QStringLiteral("Page Item");
        break;
    default:
        dbg.nospace() << QStringLiteral("No Item Type");
        break;
    }

    return dbg.space();
}

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

enum class ItemType {
    Score,
    Tune,
    Part,
    Measure,
    Symbol
};

enum InstrumentType {
    NoInstrument  = 0,
    GreatHighlandBagpipe,
    ScottishSideDrum,
    BassDrum,
    TenorDrum,
    TinWhistle,
    Vocals
};

enum IntegratedSymbolTypes {
    NoSymbolType = 0,
    MelodyNote,
    Tie
};

enum FirstSymbolTypeForInstrument {
    GreatHighlandBagpipeSymbol  = GET_FIRST_SYMBOL_TYPE(GreatHighlandBagpipe),
    ScottishSideDrumSymbol      = GET_FIRST_SYMBOL_TYPE(ScottishSideDrum),
    BassDrumSymbol              = GET_FIRST_SYMBOL_TYPE(BassDrum),
    TenorDrumSymbol             = GET_FIRST_SYMBOL_TYPE(TenorDrum),
    TinWhistleSymbol            = GET_FIRST_SYMBOL_TYPE(TinWhistle),
    VocalsSymbol                = GET_FIRST_SYMBOL_TYPE(Vocals)
};

namespace MimeTypes {
const QString Score  = "application/vnd.limepipes.xml.score.z";
const QString Tune   = "application/vnd.limepipes.xml.tune.z";
const QString Part   = "application/vnd.limepipes.xml.part.z";
const QString Measure = "application/vnd.limepipes.xml.measure.z";
const QString Symbol = "application/vnd.limepipes.xml.symbol.z";
}

}

#endif // DEFINES_H
