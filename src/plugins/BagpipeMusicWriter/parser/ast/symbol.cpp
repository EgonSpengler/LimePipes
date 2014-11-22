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

#include "AstVisitorInterface.h"
#include "symbol.h"

using namespace LP;

Symbol::Symbol(SymbolType type, MusicItem *parent)
    : MusicItem(parent),
      m_isGroup(false),
      m_type(type)
{
}

Symbol::~Symbol()
{
}

void Symbol::accept(AstVisitorInterface *visitor)
{
    visitor->visit(this);

    visitChildren(visitor);

    visitor->finishVisit(this);
}

bool Symbol::isGroup() const
{
    return m_isGroup;
}

void Symbol::setIsGroup(bool isGroup)
{
    m_isGroup = isGroup;
}

SymbolType Symbol::type() const
{
    return m_type;
}

void Symbol::setType(const SymbolType &type)
{
    m_type = type;
}



