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
#include <QObject>

Symbol::Symbol()
    : MusicItem(MusicItem::SymbolType, MusicItem::NoItemType)
{
    setData(LP::NoSymbolType, LP::symbolType);
    setData( tr("No name symbol"), LP::symbolName);
}

Symbol::Symbol(int type, const QString &name)
    : MusicItem(MusicItem::SymbolType, MusicItem::NoItemType)
{
    setData(type, LP::symbolType);
    setData(name, LP::symbolName);
}

QVariant Symbol::data(int role) const
{
    if (isRoleAccepted(role)) {
        role = mergeDoubleRoles(role);
        return m_data.value(role);
    }
    return QVariant();
}

void Symbol::setData(const QVariant &value, int role)
{
    if (isRoleAccepted(role)) {
        role = mergeDoubleRoles(role);
        m_data.insert(role, value);
    }
}

int Symbol::mergeDoubleRoles(int role) const
{
    if (role == Qt::DisplayRole) {
        role = LP::symbolName;
    }
    return role;
}

bool Symbol::isRoleAccepted(int role) const
{
    switch (role) {
    case Qt::DisplayRole:
    case LP::symbolType:
    case LP::symbolName:
    case LP::symbolLength:
        return true;
    }
    return false;
}
