/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef DATAKEYS_H
#define DATAKEYS_H

#include <QString>

namespace DataKey {

// Score
const QString ScoreTitle("title");
const QString ScoreComposer("composer");
const QString ScoreArranger("arranger");
const QString ScoreYear("year");
const QString ScoreCopyright("copyright");
const QString ScoreType("type");

// Part
const QString PartRepeat("repeat");

// Measure
const QString MeasureIsUpbeat("upbeat");

// Symbol
const QString SymbolType("type");
const QString SymbolName("name");
const QString SymbolSpanType("span type");

// General
const QString InstrumentKey("instrument");
const QString TimeSignatureKey("time sig");
const QString StaffType("staff type");
const QString ClefType("clef");
const QString Lenght("length");
const QString Pitch("pitch");

}

#endif // DATAKEYS_H
