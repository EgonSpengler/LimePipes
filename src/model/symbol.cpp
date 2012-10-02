/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class Symbol
  * A Tune consists of Symbols.
  */

#include "symbol.h"

const QScopedPointer<DataPolicyCollection> Symbol::m_policies(initPolicies());

Symbol::Symbol()
    : MusicItem(MusicItem::SymbolType, MusicItem::NoItemType),
      m_pitchIsUsed(false),
      m_lengthIsUsed(false)
{
    initData(LP::NoSymbolType, LP::symbolType);
    initData( tr("No name symbol"), LP::symbolName);
}

Symbol::Symbol(int type, const QString &name, PitchUsage pitchUsage, LengthUsage lengthUsage)
    : MusicItem(MusicItem::SymbolType, MusicItem::NoItemType)
{
    initData(type, LP::symbolType);
    initData(name, LP::symbolName);
    setPitchIsUsed(pitchUsage);
    setLengthIsUsed(lengthUsage);
}

void Symbol::setPitchIsUsed(Symbol::PitchUsage pitchUsage)
{
    m_pitchIsUsed = pitchUsage == HasPitch ? true : false;
}

void Symbol::setLengthIsUsed(Symbol::LengthUsage lengthUsage)
{
    m_lengthIsUsed = lengthUsage == HasLength ? true : false;
}

const DataPolicy Symbol::dataPolicyForRole(int role) const
{
    if (canRoleBeUsedInSubclass(role) &&
            isRoleUsedInSubclass(role)) {
        return DataPolicy(DataPolicy::ReadWrite);
    }
    return m_policies->policyForRole(role);
}

bool Symbol::canRoleBeUsedInSubclass(int role) const
{
    if (role == LP::symbolPitch ||
        role == LP::symbolLength) {
        return true;
    }
    return false;
}

bool Symbol::isRoleUsedInSubclass(int role) const
{
    switch (role) {
    case LP::symbolLength:
        return m_lengthIsUsed;
    case LP::symbolPitch:
        return m_pitchIsUsed;
    }
    return false;
}

DataPolicyCollection *Symbol::initPolicies()
{
    DataPolicyCollection *collection = new DataPolicyCollection();
    collection->setPolicy(Qt::DisplayRole, DataPolicy(DataPolicy::Read, LP::symbolName));
    collection->setPolicy(LP::symbolName, DataPolicy(DataPolicy::Read));
    collection->setPolicy(LP::symbolType, DataPolicy(DataPolicy::Read));
    return collection;
}
