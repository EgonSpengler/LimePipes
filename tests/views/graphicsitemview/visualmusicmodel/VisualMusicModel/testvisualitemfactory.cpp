/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "testvisualitem.h"
#include "testvisualitemfactory.h"

TestVisualItemFactory::TestVisualItemFactory()
{
}

VisualItem *TestVisualItemFactory::createVisualItem(VisualItem::ItemType type)
{
    TestVisualItem *visualItem = new TestVisualItem();
    visualItem->setItemType(type);
    m_visualTestItems.append(visualItem);
    switch (type) {
    case VisualItem::VisualScoreItem:
        visualItem->setGraphicalType(VisualItem::GraphicalRowType);
        break;
    case VisualItem::VisualTuneItem:
        visualItem->setGraphicalType(VisualItem::GraphicalRowType);
        break;
    case VisualItem::VisualPartItem:
        visualItem->setGraphicalType(VisualItem::GraphicalRowType);
        break;
    case VisualItem::VisualMeasureItem:
        visualItem->setGraphicalType(VisualItem::GraphicalInlineType);
        break;
    case VisualItem::VisualSymbolItem:
        visualItem->setGraphicalType(VisualItem::GraphicalInlineType);
        break;
    case VisualItem::NoVisualItem:
        visualItem->setGraphicalType(VisualItem::NoGraphicalType);
        break;
    }

    return visualItem;
}

//TestVisualItem *TestVisualItemFactory::testVisualItemForVisualItem(VisualItem *visualItem)
//{
//    if (!m_visualTestItems.contains(visualItem))
//        return 0;
//    return m_visualTestItems.indexOf(visualItem);
//}
