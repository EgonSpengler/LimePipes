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

const QScopedPointer<DataPolicyCollection> Tune::m_policies(initPolicies());

void Tune::setInstrument(InstrumentPtr instrument)
{
    m_data.insert(LP::tuneInstrument, QVariant::fromValue<InstrumentPtr>(instrument));
}

bool Tune::okToInsertChild(const MusicItem *item)
{
    const Symbol *symbol = symbolFromMusicItem(item);
    if (symbol) {
        int type = symbol->symbolType();
        return instrument()->supportsSymbolType(type);
    }
    return false;
}

QVariant Tune::readData(int role) const
{
    if (role == Qt::DisplayRole) {
        return this->instrument()->name() + " tune";
    }
    return MusicItem::readData(role);
}

DataPolicyCollection *Tune::initPolicies()
{
    DataPolicyCollection *collection = new DataPolicyCollection();
    collection->setPolicy(Qt::DisplayRole, DataPolicy(DataPolicy::Read));
    collection->setPolicy(LP::tuneInstrument, DataPolicy(DataPolicy::Read));
    return collection;
}

