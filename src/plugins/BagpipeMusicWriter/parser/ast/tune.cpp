/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "AstVisitorInterface.h"

#include "tune.h"

using namespace LP;

Tune::Tune(MusicItem *parent)
    : MusicItem(ItemType::TuneType, ItemType::PartType, parent)
{
}

void Tune::accept(AstVisitorInterface *visitor)
{
    visitor->visit(this);

    visitChildren(visitor);

    visitor->finishVisit(this);
}

