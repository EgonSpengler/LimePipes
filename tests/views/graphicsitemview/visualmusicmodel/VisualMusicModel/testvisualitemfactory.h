/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTVISUALITEMFACTORY_H
#define TESTVISUALITEMFACTORY_H

#include <QList>
#include <views/graphicsitemview/visualmusicmodel/abstractvisualitemfactory.h>

class TestVisualItem;

class TestVisualItemFactory : public AbstractVisualItemFactory
{
public:
    explicit TestVisualItemFactory();

    VisualItem *createVisualItem(VisualItem::ItemType type);

//    TestVisualItem *testVisualItemForVisualItem(VisualItem *visualItem);

private:
    QList<TestVisualItem*> m_visualTestItems;
};

#endif // TESTVISUALITEMFACTORY_H
