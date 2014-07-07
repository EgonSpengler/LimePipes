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

static const int ItemDataBase  = Qt::UserRole;
static const int ScoreDataBase = Qt::UserRole + 10;
static const int TuneDataBase  = Qt::UserRole + 30;
static const int PartDataBase  = Qt::UserRole + 50;
static const int MeasureDataBase  = Qt::UserRole + 70;
static const int SymbolDataBase  = Qt::UserRole + 90;
static const int MelodyNoteDataBase  = Qt::UserRole + 110;

namespace LP
{

enum ItemDataRole {
    MusicItemType            = ItemDataBase          // int (256)
};

// Score
enum ScoreDataRole {
    ScoreTitle          = ScoreDataBase,         // QString (266)
    ScoreComposer       = ScoreDataBase + 1,     // QString (267)
    ScoreArranger       = ScoreDataBase + 2,     // QString (268)
    ScoreYear           = ScoreDataBase + 3,     // QString (269)
    ScoreCopyright      = ScoreDataBase + 4,     // QString (270)
    ScoreType           = ScoreDataBase + 5      // QString (271)
};
static QVector<ScoreDataRole> allScoreDataRoles({ScoreTitle,
                                                 ScoreComposer,
                                                 ScoreArranger,
                                                 ScoreYear,
                                                 ScoreCopyright,
                                                 ScoreType});
// Tune
enum TuneDataRole {
    TuneInstrument      = TuneDataBase,        // Instrument (286)
    TuneTimeSignature   = TuneDataBase + 1     // TimeSignature (287)
};
static QVector<TuneDataRole> allTuneDataRoles({TuneInstrument,
                                               TuneTimeSignature});

// Part
enum PartDataRole {
    PartRepeat          = PartDataBase,         // bool (306)
    PartStaffType       = PartDataBase + 1,     // StaffType in defines.h (307)
    PartClefType        = PartDataBase + 2      // ClefType in defines.h (308)
};
static QVector<PartDataRole> allPartDataRoles({PartRepeat,
                                               PartStaffType,
                                               PartClefType});

// Measure
enum MeasureDataRole {
    MeasureIsUpbeat     = MeasureDataBase,           // bool (326)
    MeasureTimeSignature = MeasureDataBase + 1      // TimeSignature (327)
};
static QVector<MeasureDataRole> allMeasureDataRoles({MeasureIsUpbeat,
                                                     MeasureTimeSignature});

// Symbol
enum SymbolDataRole {
    SymbolType          = SymbolDataBase,        // int  (346)
    SymbolInstrument    = SymbolDataBase + 1,    // int  (347)
    SymbolName          = SymbolDataBase + 2,    // QString (348)
    SymbolLength        = SymbolDataBase + 3,    // Length  (349)
    SymbolPitch         = SymbolDataBase + 4,    // Pitch   (350)
    SymbolSpanType      = SymbolDataBase + 5,    // SymbolSpanType in defines.h. (351)
    SymbolSpanBuddy     = SymbolDataBase + 6     // QPersistentModelIndex (352)
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
    MelodyNoteDots      = MelodyNoteDataBase      // int (316)
};

}

#endif // ITEMDATATYPES_H
