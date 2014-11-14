/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "AstVisitorInterface.h"
#include "part.h"

using namespace LP;

Part::Part(MusicItem *parent)
    : MusicItem(parent),
      m_repeat(false)
{
}

void Part::accept(AstVisitorInterface *visitor)
{
    visitor->visit(this);

    visitChildren(visitor);

    visitor->finishVisit(this);
}
bool Part::repeat() const
{
    return m_repeat;
}

void Part::setRepeat(bool repeat)
{
    m_repeat = repeat;
}

