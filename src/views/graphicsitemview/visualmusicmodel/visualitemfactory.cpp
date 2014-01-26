/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualitemfactory.h"
#include <common/settingdefines.h>
#include "iteminteractions/scoreinteraction.h"
#include "interactinggraphicsitems/scoregraphicsitem.h"
#include "interactinggraphicsitems/staffgraphicsitem.h"
#include "visualpart.h"

VisualItem *VisualItemFactory::createVisualItem(VisualItem::ItemType type)
{
    switch (type) {
    case VisualItem::VisualScoreItem:
        return newVisualScore();
    case VisualItem::VisualTuneItem:
        return newVisualTune();
    case VisualItem::VisualPartItem:
        return newVisualPart();
    case VisualItem::VisualMeasureItem:
        break;
    case VisualItem::VisualSymbolItem:
        break;
    case VisualItem::NoVisualItem:
        break;
    }

    return 0;
}

VisualItem *VisualItemFactory::newVisualScore()
{
    VisualItem *newItem = new VisualItem(VisualItem::VisualScoreItem,
                                         VisualItem::GraphicalRowType);

    ScoreGraphicsItem *scoreHeaderItem = new ScoreGraphicsItem(Settings::Score::Header);
    scoreHeaderItem->setItemInteraction(new ScoreInteraction);

    ScoreGraphicsItem *scoreFooterItem = new ScoreGraphicsItem(Settings::Score::Footer);
    scoreFooterItem->setItemInteraction(new ScoreInteraction);

    newItem->appendRow(scoreHeaderItem);
    newItem->appendRow(scoreFooterItem);

    return newItem;
}

VisualItem *VisualItemFactory::newVisualTune()
{
    VisualItem *newItem = new VisualItem(VisualItem::VisualTuneItem,
                                         VisualItem::GraphicalRowType);
    return newItem;
}

VisualItem *VisualItemFactory::newVisualPart()
{
    VisualItem *newItem = new VisualPart();

    return newItem;
}
