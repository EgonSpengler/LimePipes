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

class ItemBehaviorTest : public QObject
{
    Q_OBJECT
    
public:
    ItemBehaviorTest();
    
private Q_SLOTS:
    void testCreate();
    void testSetData();
};

ItemBehaviorTest::ItemBehaviorTest()
{
}

void ItemBehaviorTest::testCreate()
{
    ItemBehavior *behavior = new ItemBehavior(ItemBehavior::TuneType, ItemBehavior::SymbolType);
    QVERIFY2(behavior->type() == ItemBehavior::TuneType, "Failed setting behavior type in constructor");
    QVERIFY2(behavior->childType() == ItemBehavior::SymbolType, "Failed setting behavior child type in constructor");
}

void ItemBehaviorTest::testSetData()
{
    ItemBehavior *behavior = new ItemBehavior(ItemBehavior::NoItemType, ItemBehavior::NoItemType);
    behavior->setData(QString("hello"), Qt::DisplayRole);
    QVERIFY2(behavior->data(Qt::DisplayRole) == "hello", "Failed setting data of behavior");
}

QTEST_APPLESS_MAIN(ItemBehaviorTest)

#include "tst_itembehaviortest.moc"
