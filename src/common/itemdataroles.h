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
#include <QVector>

namespace LP
{

// Score
enum ScoreDataRole {
    ScoreTitle          = Qt::UserRole,         // QString (256)
    ScoreComposer       = Qt::UserRole + 1,     // QString (257)
    ScoreArranger       = Qt::UserRole + 2,     // QString (258)
    ScoreYear           = Qt::UserRole + 3,     // QString (259)
    ScoreCopyright      = Qt::UserRole + 4,     // QString (260)
    ScoreType           = Qt::UserRole + 5      // QString (261)
};
static QVector<ScoreDataRole> allScoreDataRoles({ScoreTitle,
                                                   ScoreComposer,
                                                   ScoreArranger,
                                                   ScoreYear,
                                                   ScoreCopyright,
                                                   ScoreType});
// Tune
enum TuneDataRole {
    TuneInstrument      = Qt::UserRole + 6      // Instrument (262)
};
static QVector<TuneDataRole> allTuneDataRoles({TuneInstrument});

// Part
enum PartDataRole {
    PartRepeat          = Qt::UserRole + 7,     // bool (263)
    PartStaffType       = Qt::UserRole + 8,     // StaffType in defines.h (264)
    PartClefType        = Qt::UserRole + 9      // ClefType in defines.h (265)
};
static QVector<PartDataRole> allPartDataRoles({PartRepeat,
                                               PartStaffType,
                                               PartClefType});

// Measure
enum MeasureDataRole {
    MeasureIsUpbeat     = Qt::UserRole + 10      // bool (266)
};
static QVector<MeasureDataRole> allMeasureDataRoles({MeasureIsUpbeat});

// Symbol
enum SymbolDataRole {
    SymbolCategory      = Qt::UserRole + 11,    // SymbolCategory in defines.h (267)
    SymbolType          = Qt::UserRole + 12,    // int (268)
    SymbolName          = Qt::UserRole + 13,    // QString (269)
    SymbolLength        = Qt::UserRole + 14,    // Length (270)
    SymbolPitch         = Qt::UserRole + 15,    // PitchPtr (271)
    SymbolPitchContext  = Qt::UserRole + 16,    // PitchContextPtr (272)
    SymbolSpanType      = Qt::UserRole + 17,    // SymbolSpanType in defines.h. (273)
    SymbolSpanBuddy     = Qt::UserRole + 18     // QPersistentModelIndex (274)
};
static QVector<SymbolDataRole> allSymbolDataRoles({SymbolType,
                                                   SymbolCategory,
                                                   SymbolPitchContext,
                                                   SymbolLength,
                                                   SymbolPitch,
                                                   SymbolName,
                                                   SymbolSpanType,
                                                   SymbolSpanBuddy});

// MelodyNote
enum MelodyNoteDataRole {
    MelodyNoteDots      = Qt::UserRole + 19     // int (273)
};

}

#endif // ITEMDATATYPES_H
