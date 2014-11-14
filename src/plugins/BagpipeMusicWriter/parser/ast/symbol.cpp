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

Symbol::Symbol(MusicItem *parent)
    : MusicItem(parent),
      m_isGroup(false),
      m_dots(0)
{
    Q_UNUSED(parent)
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
quint8 Symbol::dots() const
{
    return m_dots;
}

void Symbol::setDots(const quint8 &dots)
{
    m_dots = dots;
}


