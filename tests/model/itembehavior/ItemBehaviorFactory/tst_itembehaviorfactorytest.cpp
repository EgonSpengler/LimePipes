/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <itembehavior.h>
#include <itembehaviorfactory.h>

class ItemBehaviorFactoryTest : public QObject
{
    Q_OBJECT
    
public:
    ItemBehaviorFactoryTest();
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testGetBehavior();
};

ItemBehaviorFactoryTest::ItemBehaviorFactoryTest()
{
}

void ItemBehaviorFactoryTest::init()
{
}

void ItemBehaviorFactoryTest::cleanup()
{
}

void ItemBehaviorFactoryTest::testGetBehavior()
{
    ItemBehavior *behavior = 0;

    behavior = ItemBehaviorFactory::getBehavior(ItemBehavior::RootItem);
    QVERIFY2(behavior->type() == ItemBehavior::RootItem, "Factory returns not the correct behavior for root item");

    behavior = ItemBehaviorFactory::getBehavior(ItemBehavior::Score);
    QVERIFY2(behavior->type() == ItemBehavior::Score, "Factory returns not the correct behavior for scores");

    behavior = ItemBehaviorFactory::getBehavior(ItemBehavior::Tune);
    QVERIFY2(behavior->type() == ItemBehavior::Tune, "Factory returns not the correct behavior for tunes");

    behavior = ItemBehaviorFactory::getBehavior(ItemBehavior::Symbol);
    QVERIFY2(behavior->type() == ItemBehavior::Symbol, "Factory returns not the correct behavior for Symbols");

    delete behavior;
}

QTEST_APPLESS_MAIN(ItemBehaviorFactoryTest)

#include "tst_itembehaviorfactorytest.moc"
