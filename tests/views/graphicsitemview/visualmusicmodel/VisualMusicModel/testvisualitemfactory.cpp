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
    return visualItem;
}

//TestVisualItem *TestVisualItemFactory::testVisualItemForVisualItem(VisualItem *visualItem)
//{
//    if (!m_visualTestItems.contains(visualItem))
//        return 0;
//    return m_visualTestItems.indexOf(visualItem);
//}
