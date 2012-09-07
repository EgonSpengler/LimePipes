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

void Tune::setInstrument(Instrument *instrument)
{
    setData(QVariant::fromValue<Instrument*>(instrument), LP::tuneInstrument);
}

bool Tune::okToInsertChild(const MusicItem *item)
{
    const Symbol *symbol = symbolFromMusicItem(item);
    if (this->hasInstrument()) {
        if (symbol) {
            return instrument()->supportsSymbolType(symbol->symbolType());
        }
    }
    return false;
}

QVariant Tune::data(int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return instrument()->name() + " tune";
    case LP::tuneInstrument:
        return m_data.value(role);
    default:
        return QVariant();
    }
}

void Tune::setData(const QVariant &value, int role)
{
    switch (role) {
    case LP::tuneInstrument:
        m_data.insert(role, value);
    }
}

