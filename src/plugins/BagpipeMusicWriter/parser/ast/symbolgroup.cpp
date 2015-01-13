/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "AstVisitorInterface.h"
#include "symbolgroup.h"

SymbolGroup::SymbolGroup(SymbolType type, MusicItem *parent)
    : Symbol(type, parent),
      m_closed(false)
{
    setIsGroup(true);
}

SymbolGroup::~SymbolGroup()
{
}

void SymbolGroup::accept(AstVisitorInterface *visitor)
{
    visitor->visit(this);

    visitChildren(visitor);

    visitor->finishVisit(this);
}

bool SymbolGroup::closed() const
{
    return m_closed;
}

void SymbolGroup::setClosed(bool closed)
{
    m_closed = closed;
}

