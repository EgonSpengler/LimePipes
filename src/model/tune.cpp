/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class Tune
  * A Tune represents a Score played by a specific instrument.
  */

#include "tune.h"
#include <QXmlStreamWriter>
#include <symbols/barline.h>

void Tune::setInstrument(InstrumentPtr instrument)
{
    m_data.insert(LP::tuneInstrument, QVariant::fromValue<InstrumentPtr>(instrument));
}

int Tune::startRowOfPart(int partNumber)
{
    if (childCount() == 0 ||
            partNumber <= 0)
        return 0;
    return findStartOfPart(partNumber);
}

Tune::Tune(MusicItem *parent)
    : MusicItem(MusicItem::TuneType, MusicItem::PartType, parent)
{
    setInstrument(InstrumentPtr(new NullInstrument()));
}

Tune::Tune(InstrumentPtr instrument)
    : MusicItem(MusicItem::TuneType, MusicItem::PartType)
{
    setInstrument(instrument);
}

bool Tune::okToInsertChild(const MusicItem *item, int row)
{
    // Todo: Measure item should be aware of instrument
    return true;

//    const Symbol *symbol = symbolFromMusicItem(item);

//    if (symbol) {
//        if (symbol->symbolType() == LP::BarLine)
//            return true;

//        int type = symbol->symbolType();
//        if (instrument()->supportsSymbolType(type) &&
//                rowIsPrecededByStartOfPart(row))
//            return true;
//    }
//    return false;
}

const Symbol *Tune::symbolFromMusicItem(const MusicItem *item)
{
    return static_cast<const Symbol*>(item);
}

bool Tune::itemSupportsWritingOfData(int role) const
{
    Q_UNUSED(role)
    return false;
}

void Tune::writeItemDataToXmlStream(QXmlStreamWriter *writer)
{
    Q_UNUSED(writer)
}

void Tune::readCurrentElementFromXmlStream(QXmlStreamReader *reader)
{
    Q_UNUSED(reader)
}

int Tune::findStartOfPart(int partNumber)
{
    int partStartCount = 0;
    int currentRow = 0;
    foreach (MusicItem *childItem, children()) {
        if (childItem->data(LP::barLineType).isValid() &&
                childItem->data(LP::barLineType).canConvert<BarLine::Type>()) {
            if (childItem->data(LP::barLineType).value<BarLine::Type>() == BarLine::StartPart)
                ++partStartCount;
            if (partNumber + 1 == partStartCount)
                return currentRow;
        }
        ++currentRow;
    }
    return childCount();
}

bool Tune::rowIsPrecededByStartOfPart(int row)
{
    if (row < 1)
        return false;

    if (row >= childCount())
        row = childCount() - 1;

    for (int i=row; row!=0; row--) {
        QVariant barLineTypeVar = children().at(i)->data(LP::barLineType);
        if (barLineTypeVar.isValid() &&
                barLineTypeVar.canConvert<BarLine::Type>()) {
            if (barLineTypeVar.value<BarLine::Type>() == BarLine::StartPart)
                return true;
        }
    }
    return true;
}
