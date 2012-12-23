/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>

#include "tst_rootitemtest.h"

void RootItemTest::init()
{
    m_rootItem = new RootItem();
}

void RootItemTest::cleanup()
{
    delete m_rootItem;
}

void RootItemTest::testType()
{
    QVERIFY2(m_rootItem->type() == MusicItem::RootItemType, "Root item returns the wrong type");
}

void RootItemTest::testChildType()
{
    QVERIFY2(m_rootItem->childType() == MusicItem::ScoreType, "The child itemtype of RootItem is not Score type");
}

QTEST_MAIN(RootItemTest)

#include "tst_rootitemtest.moc"
