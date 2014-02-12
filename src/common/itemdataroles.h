/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @enum LP::ScoreDataRole
  * All data roles used by \ref Score "Score items"
  * @var LP::DataRole LP::scoreCopyright
  * The copyright for a tune without the copyright sign.
  *
  * @enum LP::TuneDataRole
  * All data roles used by \ref Tune "Tune items"
  *
  * @enum LP::PartDataRole
  * All data roles used by \ref Part "Part items"
  *
  * @enum LP::MeasureDataRole
  * All data roles used by \ref Measure "Measure items"
  *
  * @enum LP::SymbolDataRole
  * All data roles used by \ref Symbol "Symbol items"
  *
  */

#ifndef ITEMDATATYPES_H
#define ITEMDATATYPES_H

#include <Qt>

namespace LP {

// Score
enum ScoreDataRole {
    ScoreTitle          = Qt::UserRole,         // QString
    ScoreComposer       = Qt::UserRole + 1,     // QString
    ScoreArranger       = Qt::UserRole + 2,     // QString
    ScoreYear           = Qt::UserRole + 3,     // QString
    ScoreCopyright      = Qt::UserRole + 4,     // QString
    ScoreType           = Qt::UserRole + 5      // QString
};

// Tune
enum TuneDataRole {
    TuneInstrument      = Qt::UserRole + 6      // Instrument
};

// Part
enum PartDataRole {
    PartRepeat          = Qt::UserRole + 7,     // bool
    PartStaffType       = Qt::UserRole + 8      // StaffType in defines.h
};

// Measure
enum MeasureDataRole {
    MeasureIsUpbeat     = Qt::UserRole + 9      // bool
};

// Symbol
enum SymbolDataRole {
    SymbolCategory      = Qt::UserRole + 10,    // SymbolCategory in defines.h
    SymbolType          = Qt::UserRole + 11,    // int
    SymbolName          = Qt::UserRole + 12,    // QString
    SymbolLength        = Qt::UserRole + 13,    // Length
    SymbolPitch         = Qt::UserRole + 14,    // Pitch
};

// MelodyNote
enum MelodyNoteDataRole {
    MelodyNoteDots      = Qt::UserRole + 15
};

}

#endif // ITEMDATATYPES_H
