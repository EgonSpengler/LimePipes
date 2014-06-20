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
#include "iteminteractions/symbolinteraction.h"
#include "interactinggraphicsitems/scoregraphicsitem.h"
#include "interactinggraphicsitems/measuregraphicsitem.h"
#include "interactinggraphicsitems/symbolgraphicsitem.h"
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
        return newVisualMeasure();
    case VisualItem::NoVisualItem:
        break;
    default:
        return 0;
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
    VisualPart *newItem = new VisualPart();

    return newItem;
}

VisualItem *VisualItemFactory::newVisualMeasure()
{
    VisualItem *newItem = new VisualItem(VisualItem::VisualMeasureItem,
                                         VisualItem::GraphicalInlineType);

    MeasureGraphicsItem *measureGraphicsItem = new MeasureGraphicsItem;
    newItem->setInlineGraphic(measureGraphicsItem);

    return newItem;
}

VisualItem *VisualItemFactory::newVisualSymbol(int symbolType)
{
    VisualItem *newItem = new VisualItem(VisualItem::VisualSymbolItem,
                                         VisualItem::GraphicalInlineType);

    SymbolGraphicsItem *symbolGraphicsItem = new SymbolGraphicsItem;
    SymbolInteraction *symbolInteraction = new SymbolInteraction(pluginManger()->musicFont());
    ItemInteraction *additionalInteraction = pluginManger()->itemInteractionForType(symbolType);
    if (additionalInteraction) {
        symbolInteraction->setAdditionalInteraction(additionalInteraction);
    }

    symbolGraphicsItem->setItemInteraction(symbolInteraction);
    if (!pluginManger().isNull())
        symbolGraphicsItem->setPluginManager(pluginManger());
    newItem->setInlineGraphic(symbolGraphicsItem);

    return newItem;
}


VisualItem *VisualItemFactory::createVisualSymbol(int symbolType)
{
    return newVisualSymbol(symbolType);
}
