/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>

#include <musicitemfactory.h>

class MusicItemFactoryTest : public QObject
{
    Q_OBJECT
    
public:
    MusicItemFactoryTest();
    
private Q_SLOTS:
    void testGetMusicItem();
};

MusicItemFactoryTest::MusicItemFactoryTest()
{
}

void MusicItemFactoryTest::testGetMusicItem()
{
    MusicItem *item = 0;

    item = MusicItemFactory::getMusicItem(MusicItem::RootItem);
    QVERIFY2(item->type() == MusicItem::RootItem, "MusicItemFactory returns no Root item");
    delete item;

    item = MusicItemFactory::getMusicItem(MusicItem::Score);
    QVERIFY2(item->type() == MusicItem::Score, "MusicItemFactory returns no Score item");
    delete item;

    item = MusicItemFactory::getMusicItem(MusicItem::Tune);
    QVERIFY2(item->type() == MusicItem::Tune, "MusicItemFactory returns no Tune item");
    delete item;

    item = MusicItemFactory::getMusicItem(MusicItem::Symbol);
    QVERIFY2(item->type() == MusicItem::Symbol, "MusicItemFactory returns no Symbol item");
    delete item;

    item = MusicItemFactory::getMusicItem(MusicItem::NoItem);
    QVERIFY2(item->type() == MusicItem::NoItem, "MusicItemFactory returns no Item for the NoItem-type");
    delete item;
}

QTEST_APPLESS_MAIN(MusicItemFactoryTest)

#include "tst_musicitemfactorytest.moc"
