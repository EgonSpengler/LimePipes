/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICMODELINTERFACE_H
#define MUSICMODELINTERFACE_H

#include <common/datatypes/instrument.h>

class Score;
class Tune;
class Symbol;
class QModelIndex;
class QStringList;
class QUndoStack;
class MusicItem;

class MusicModelInterface
{
public:
    virtual QModelIndex insertScore(int row, const QString &title) = 0;
    virtual QModelIndex appendScore(const QString &title) = 0;

    virtual QModelIndex insertTuneIntoScore(int row, const QModelIndex &score, const QString &instrumentName) = 0;
    virtual QModelIndex appendTuneToScore(const QModelIndex &score, const QString &instrumentName) = 0;
    virtual QModelIndex insertTuneWithScore(int rowOfScore, const QString &scoreTitle, const QString &instrumentName) = 0;

    virtual QModelIndex insertPartIntoTune(int row, const QModelIndex &tune, int measures, bool withRepeat=false) = 0;
    virtual QModelIndex appendPartToTune(const QModelIndex &tune, int measures, bool withRepeat=false) = 0;

    virtual QModelIndex insertMeasureIntoPart(int row, const QModelIndex &part) = 0;
    virtual QModelIndex appendMeasureToPart(const QModelIndex &part) = 0;

    virtual QModelIndex insertSymbolIntoMeasure(int row, const QModelIndex &measure, int type) = 0;
    virtual QModelIndex appendSymbolToMeasure(const QModelIndex &measure, int type) = 0;

    virtual MusicItem *itemForIndex(const QModelIndex& index) const = 0;

    virtual bool isIndexScore(const QModelIndex &index) const = 0;
    virtual bool isIndexTune(const QModelIndex &index) const = 0;
    virtual bool isIndexSymbol(const QModelIndex &index) const = 0;
    virtual bool isIndexPart(const QModelIndex &index) const = 0;
    virtual bool isIndexMeasure(const QModelIndex &index) const = 0;
    virtual bool indexSupportsWritingOfData(const QModelIndex &index, int role) const = 0;

    virtual void clear() = 0;

    QString filename() const { return m_filename; }
    void setFilename(const QString &filename) { m_filename = filename; }

    virtual void save(const QString &filename=QString()) = 0;
    virtual void load(const QString &filename=QString()) = 0;

    virtual QUndoStack *undoStack() const = 0;

protected:
    QString m_filename;
};

#endif // MUSICMODELINTERFACE_H
