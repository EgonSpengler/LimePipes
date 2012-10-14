/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICMODELINTERFACE_H
#define MUSICMODELINTERFACE_H

#include "datatypes/instrument.h"

class Score;
class Tune;
class Symbol;
class QModelIndex;
class MusicItem;

class MusicModelInterface
{
public:
    virtual QModelIndex insertScore(int row, const QString &title) = 0;
    virtual QModelIndex appendScore(const QString &title) = 0;
    virtual QModelIndex insertTuneIntoScore(int row, const QModelIndex &score, InstrumentPtr instrument) = 0;
    virtual QModelIndex appendTuneToScore(const QModelIndex &score, InstrumentPtr instrument) = 0;
    virtual QModelIndex insertTuneWithScore(int rowOfScore, const QString &scoreTitle, InstrumentPtr instrument) = 0;
    virtual QModelIndex insertSymbol(int row, const QModelIndex &tune, Symbol *symbol) = 0;

    virtual MusicItem *itemForIndex(const QModelIndex& index) const = 0;
    virtual void clear() = 0;

    virtual bool isIndexScore(const QModelIndex &index) const = 0;
    virtual bool isIndexTune(const QModelIndex &index) const = 0;
    virtual bool isIndexSymbol(const QModelIndex &index) const = 0;

    virtual Score *scoreFromIndex(const QModelIndex &index) const = 0;
    virtual Tune *tuneFromIndex(const QModelIndex &index) const = 0;
    virtual Symbol *symbolFromIndex(const QModelIndex &index) const = 0;
    virtual PitchContextPtr pitchContextFromTuneIndex(const QModelIndex &index) const = 0;
};

#endif // MUSICMODELINTERFACE_H
