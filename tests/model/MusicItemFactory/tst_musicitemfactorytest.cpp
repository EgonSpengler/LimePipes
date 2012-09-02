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

    item = MusicItemFactory::getMusicItem(MusicItem::RootItemType);
    QVERIFY2(item->type() == MusicItem::RootItemType, "MusicItemFactory returns no Root item");
    delete item;

    item = MusicItemFactory::getMusicItem(MusicItem::ScoreType);
    QVERIFY2(item->type() == MusicItem::ScoreType, "MusicItemFactory returns no Score item");
    delete item;

    item = MusicItemFactory::getMusicItem(MusicItem::TuneType);
    QVERIFY2(item->type() == MusicItem::TuneType, "MusicItemFactory returns no Tune item");
    delete item;

    item = MusicItemFactory::getMusicItem(MusicItem::SymbolType);
    QVERIFY2(item->type() == MusicItem::SymbolType, "MusicItemFactory returns no Symbol item");
    delete item;

    item = MusicItemFactory::getMusicItem(MusicItem::NoItemType);
    QVERIFY2(item->type() == MusicItem::NoItemType, "MusicItemFactory returns no Item for the NoItem-type");
    delete item;
}

QTEST_APPLESS_MAIN(MusicItemFactoryTest)

#include "tst_musicitemfactorytest.moc"
