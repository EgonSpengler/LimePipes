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

#include <QVector>
#include <Qt>

namespace LP {

// Score
enum ScoreDataRole {
    ScoreTitle          = Qt::UserRole,
    ScoreComposer       = Qt::UserRole + 1,
    ScoreArranger       = Qt::UserRole + 2,
    ScoreYear           = Qt::UserRole + 3,
    ScoreCopyright      = Qt::UserRole + 4,
    ScoreType           = Qt::UserRole + 5
};

// Tune
enum TuneDataRole {
    TuneInstrument      = Qt::UserRole + 7
};

// Part
enum PartDataRole {
    PartRepeat          = Qt::UserRole + 8,
    PartStaffType       = Qt::UserRole + 9
};

// Measure
enum MeasureDataRole {
    MeasureIsUpbeat     = Qt::UserRole + 10
};

// Symbol
enum SymbolDataRole {
    SymbolType          = Qt::UserRole + 11,
    SymbolName          = Qt::UserRole + 12,
    SymbolLength        = Qt::UserRole + 13,
    SymbolPitch         = Qt::UserRole + 14,
    SymbolGraphic       = Qt::UserRole + 15
};

// MelodyNote
enum MelodyNoteDataRole {
    MelodyNoteDots      = Qt::UserRole + 16
};

}

#endif // ITEMDATATYPES_H
