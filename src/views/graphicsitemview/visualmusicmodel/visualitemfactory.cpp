/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualitemfactory.h"
#include "iteminteractions/scoreinteraction.h"
#include "interactinggraphicsitems/scoregraphicsitem.h"

VisualItem *VisualItemFactory::createVisualItem(VisualItem::ItemType type)
{
    switch (type) {
    case VisualItem::VisualScoreItem:
        return newVisualScore();
        break;
    case VisualItem::VisualTuneItem:
        break;
    case VisualItem::VisualPartItem:
        break;
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

    ScoreGraphicsItem *scoreHeaderItem = new ScoreGraphicsItem();
    scoreHeaderItem->setItemInteraction(new ScoreInteraction);
    scoreHeaderItem->setItemPosition(LP::ScoreType, 0, Settings::TextAlignment::Left);
    scoreHeaderItem->setItemPosition(LP::ScoreTitle, 0, Settings::TextAlignment::Center);
    QFont font;
    font.setPointSize(16);
    scoreHeaderItem->setItemFont(LP::ScoreTitle, font);
    scoreHeaderItem->setItemPosition(LP::ScoreComposer, 0, Settings::TextAlignment::Right);
    scoreHeaderItem->setItemPosition(LP::ScoreArranger, 1, Settings::TextAlignment::Right);

    ScoreGraphicsItem *scoreFooterItem = new ScoreGraphicsItem();
    scoreFooterItem->setItemPosition(LP::ScoreYear, 0, Settings::TextAlignment::Left);
    scoreFooterItem->setItemPosition(LP::ScoreCopyright, 0, Settings::TextAlignment::Right);
    scoreFooterItem->setItemInteraction(new ScoreInteraction);

    newItem->appendRow(scoreHeaderItem);
    newItem->appendRow(scoreFooterItem);

    return newItem;
}
