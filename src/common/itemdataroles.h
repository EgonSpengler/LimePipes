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
    TuneInstrument      = Qt::UserRole + 10,    // Instrument (266)
    TuneTimeSignature   = Qt::UserRole + 11     // TimeSignature (267)
};
static QVector<TuneDataRole> allTuneDataRoles({TuneInstrument,
                                               TuneTimeSignature});

// Part
enum PartDataRole {
    PartRepeat          = Qt::UserRole + 20,     // bool (276)
    PartStaffType       = Qt::UserRole + 21,     // StaffType in defines.h (277)
    PartClefType        = Qt::UserRole + 22      // ClefType in defines.h (278)
};
static QVector<PartDataRole> allPartDataRoles({PartRepeat,
                                               PartStaffType,
                                               PartClefType});

// Measure
enum MeasureDataRole {
    MeasureIsUpbeat     = Qt::UserRole + 30,      // bool (286)
    MeasureTimeSignature = Qt::UserRole + 31      // TimeSignature (287)
};
static QVector<MeasureDataRole> allMeasureDataRoles({MeasureIsUpbeat,
                                                     MeasureTimeSignature});

// Symbol
enum SymbolDataRole {
    SymbolType          = Qt::UserRole + 40,    // int (296)
    SymbolInstrument    = Qt::UserRole + 41,
    SymbolName          = Qt::UserRole + 42,    // QString (297)
    SymbolLength        = Qt::UserRole + 43,    // Length (298)
    SymbolPitch         = Qt::UserRole + 44,    // Pitch (299)
    SymbolSpanType      = Qt::UserRole + 45,    // SymbolSpanType in defines.h. (301)
    SymbolSpanBuddy     = Qt::UserRole + 46     // QPersistentModelIndex (302)
};
static QVector<SymbolDataRole> allSymbolDataRoles({SymbolType,
                                                   SymbolInstrument,
                                                   SymbolLength,
                                                   SymbolPitch,
                                                   SymbolName,
                                                   SymbolSpanType,
                                                   SymbolSpanBuddy});

// MelodyNote
enum MelodyNoteDataRole {
    MelodyNoteDots      = Qt::UserRole + 60     // int (316)
};

}

#endif // ITEMDATATYPES_H
