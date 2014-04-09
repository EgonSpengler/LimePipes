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
    case VisualItem::VisualSymbolItem:
        return newVisualSymbol();
    case VisualItem::NoVisualItem:
        break;
    }

    return 0;
}

void VisualItemFactory::setSmuflForGraphicsItem(InteractingGraphicsItem *graphicsItem)
{
    if (!pluginManger().isNull())
        graphicsItem->setSmufl(pluginManger()->smufl());
}

VisualItem *VisualItemFactory::newVisualScore()
{
    VisualItem *newItem = new VisualItem(VisualItem::VisualScoreItem,
                                         VisualItem::GraphicalRowType);

    ScoreGraphicsItem *scoreHeaderItem = new ScoreGraphicsItem(Settings::Score::Header);
    scoreHeaderItem->setItemInteraction(new ScoreInteraction);
    setSmuflForGraphicsItem(scoreHeaderItem);

    ScoreGraphicsItem *scoreFooterItem = new ScoreGraphicsItem(Settings::Score::Footer);
    scoreFooterItem->setItemInteraction(new ScoreInteraction);
    setSmuflForGraphicsItem(scoreFooterItem);

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
    if (!pluginManger().isNull())
        newItem->setSmufl(pluginManger()->smufl());

    return newItem;
}

VisualItem *VisualItemFactory::newVisualMeasure()
{
    VisualItem *newItem = new VisualItem(VisualItem::VisualMeasureItem,
                                         VisualItem::GraphicalInlineType);

    MeasureGraphicsItem *measureGraphicsItem = new MeasureGraphicsItem;
    newItem->setInlineGraphic(measureGraphicsItem);
    setSmuflForGraphicsItem(measureGraphicsItem);

    return newItem;
}

VisualItem *VisualItemFactory::newVisualSymbol()
{
    VisualItem *newItem = new VisualItem(VisualItem::VisualSymbolItem,
                                         VisualItem::GraphicalInlineType);

    SymbolGraphicsItem *symbolGraphicsItem = new SymbolGraphicsItem;
    if (!pluginManger().isNull())
        symbolGraphicsItem->setPluginManager(pluginManger());
    newItem->setInlineGraphic(symbolGraphicsItem);
    setSmuflForGraphicsItem(symbolGraphicsItem);

    return newItem;
}
