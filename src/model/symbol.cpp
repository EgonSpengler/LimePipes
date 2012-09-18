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
    : MusicItem(MusicItem::SymbolType, MusicItem::NoItemType)
{
    initData(LP::NoSymbolType, LP::symbolType);
    initData( tr("No name symbol"), LP::symbolName);
}

Symbol::Symbol(int type, const QString &name)
    : MusicItem(MusicItem::SymbolType, MusicItem::NoItemType)
{
    initData(type, LP::symbolType);
    initData(name, LP::symbolName);
}

DataPolicyCollection *Symbol::initPolicies()
{
    DataPolicyCollection *collection = new DataPolicyCollection();
    collection->setPolicy(Qt::DisplayRole, DataPolicy(DataPolicy::Read, LP::symbolName));
    collection->setPolicy(LP::symbolName, DataPolicy(DataPolicy::Read));
    collection->setPolicy(LP::symbolType, DataPolicy(DataPolicy::Read));
    collection->setPolicy(LP::symbolLength, DataPolicy(DataPolicy::ReadWrite));
    return collection;
}
