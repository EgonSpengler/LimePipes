/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <graphicsitemview/scorepropertiesitem.h>

class ScorePropertiesItemTest : public QObject
{
    Q_OBJECT

public:
    ScorePropertiesItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testTitle();
    void testType();
    void testComposer();
    void testArranger();
    void testYear();
    void testCopyright();
    void testLinkWithItem();
    void testLinkedItem();
    void testSetDataWhenLinkItems();

private:
    ScorePropertiesItem *m_scorePropertiesItem;
};

ScorePropertiesItemTest::ScorePropertiesItemTest()
{
}

void ScorePropertiesItemTest::init()
{
    m_scorePropertiesItem = new ScorePropertiesItem(this);
}

void ScorePropertiesItemTest::cleanup()
{
    delete m_scorePropertiesItem;
}

void ScorePropertiesItemTest::testTitle()
{
    QString title("title 1");
    QSignalSpy spy(m_scorePropertiesItem, SIGNAL(titleChanged(QString)));

    m_scorePropertiesItem->setTitle(title);
    QVERIFY2(m_scorePropertiesItem->title() == title, "Title was't set");
    QVERIFY2(spy.count() == 1, "Title changed signals wasn't emitted");

    m_scorePropertiesItem->setTitle(title);
    QVERIFY2(spy.count() == 1, "Title changed signal was emitted despite same title");
}

void ScorePropertiesItemTest::testType()
{
    QString type("type 1");
    QSignalSpy spy(m_scorePropertiesItem, SIGNAL(typeChanged(QString)));

    m_scorePropertiesItem->setType(type);
    QVERIFY2(m_scorePropertiesItem->type() == type, "Type was't set");
    QVERIFY2(spy.count() == 1, "Type changed signals wasn't emitted");

    m_scorePropertiesItem->setType(type);
    QVERIFY2(spy.count() == 1, "Type changed signal was emitted despite same type");
}

void ScorePropertiesItemTest::testComposer()
{
    QString composer("composer");
    QSignalSpy spy(m_scorePropertiesItem, SIGNAL(composerChanged(QString)));

    m_scorePropertiesItem->setComposer(composer);
    QVERIFY2(m_scorePropertiesItem->composer() == composer, "Composer was't set");
    QVERIFY2(spy.count() == 1, "Composer changed signals wasn't emitted");

    m_scorePropertiesItem->setComposer(composer);
    QVERIFY2(spy.count() == 1, "Composer changed signal was emitted despite same Composer");
}

void ScorePropertiesItemTest::testArranger()
{
    QString arranger("arranger");
    QSignalSpy spy(m_scorePropertiesItem, SIGNAL(arrangerChanged(QString)));

    m_scorePropertiesItem->setArranger(arranger);
    QVERIFY2(m_scorePropertiesItem->arranger() == arranger, "Arranger was't set");
    QVERIFY2(spy.count() == 1, "Arranger changed signals wasn't emitted");

    m_scorePropertiesItem->setArranger(arranger);
    QVERIFY2(spy.count() == 1, "Arranger changed signal was emitted despite same Arranger");
}

void ScorePropertiesItemTest::testYear()
{
    QString year("2013");
    QSignalSpy spy(m_scorePropertiesItem, SIGNAL(yearChanged(QString)));

    m_scorePropertiesItem->setYear(year);
    QVERIFY2(m_scorePropertiesItem->year() == year, "Year was't set");
    QVERIFY2(spy.count() == 1, "Year changed signals wasn't emitted");

    m_scorePropertiesItem->setYear(year);
    QVERIFY2(spy.count() == 1, "Year changed signal was emitted despite same Year");
}

void ScorePropertiesItemTest::testCopyright()
{
    QString copyright("2013");
    QSignalSpy spy(m_scorePropertiesItem, SIGNAL(copyrightChanged(QString)));

    m_scorePropertiesItem->setCopyright(copyright);
    QVERIFY2(m_scorePropertiesItem->copyright() == copyright, "Copyright was't set");
    QVERIFY2(spy.count() == 1, "Copyright changed signals wasn't emitted");

    m_scorePropertiesItem->setCopyright(copyright);
    QVERIFY2(spy.count() == 1, "Copyright changed signal was emitted despite same Copyright");
}

void ScorePropertiesItemTest::testLinkWithItem()
{
    ScorePropertiesItem *item1 = new ScorePropertiesItem(this);
    ScorePropertiesItem *item2 = new ScorePropertiesItem(this);
    QSignalSpy spySetTitle12(item2, SIGNAL(titleChanged(QString)));
    QSignalSpy spySetTitle21(item1, SIGNAL(titleChanged(QString)));
    QSignalSpy spySetType12(item2, SIGNAL(typeChanged(QString)));
    QSignalSpy spySetType21(item1, SIGNAL(typeChanged(QString)));
    QSignalSpy spySetComposer12(item2, SIGNAL(composerChanged(QString)));
    QSignalSpy spySetComposer21(item1, SIGNAL(composerChanged(QString)));
    QSignalSpy spySetArranger12(item2, SIGNAL(arrangerChanged(QString)));
    QSignalSpy spySetArranger21(item1, SIGNAL(arrangerChanged(QString)));
    QSignalSpy spySetYear12(item2, SIGNAL(yearChanged(QString)));
    QSignalSpy spySetYear21(item1, SIGNAL(yearChanged(QString)));
    QSignalSpy spySetCopyright12(item2, SIGNAL(copyrightChanged(QString)));
    QSignalSpy spySetCopyright21(item1, SIGNAL(copyrightChanged(QString)));

    item1->linkWithItem(item2);

    // Set Title 1 -> 2
    item1->setTitle("testtitle");
    QVERIFY2(spySetTitle12.count() == 1, "Set new title wasn't called on item 2");

    // Set Title 2 -> 1
    item2->setTitle("testtitle2");
    QVERIFY2(spySetTitle21.count() == 2, "Set new title wasn't called on item 1");

    // Set Type 1 -> 2
    item1->setType("testtype");
    QVERIFY2(spySetType12.count() == 1, "Set new type wasn't called on item 2");

    // Set Type 2 -> 1
    item2->setType("testtype");
    QVERIFY2(spySetType21.count() == 2, "Set new type wasn't called on item 1");

    // Set Composer 1 -> 2
    item1->setComposer("composer");
    QVERIFY2(spySetComposer12.count() == 1, "Set new composer wasn't called on item2");

    // Set Composer 2 -> 1
    item2->setComposer("composer2");
    QVERIFY2(spySetComposer21.count() == 2, "Set new composer wasn't called on item1");

    // Set Arranger 1 -> 2
    item1->setArranger("arranger");
    QVERIFY2(spySetArranger12.count() == 1, "Set new arranger wasn't called on item2");

    // Set Arranger 2 -> 1
    item2->setArranger("arranger2");
    QVERIFY2(spySetArranger21.count() == 2, "Set new arranger wasn't called on item1");

    // Set Year 1 -> 2
    item1->setYear("2013");
    QVERIFY2(spySetYear12.count() == 1, "Set new year wasn't called on item2");

    // Set Year 2 -> 1
    item2->setYear("20132");
    QVERIFY2(spySetYear21.count() == 2, "Set new year wasn't called on item1");

    // Set Copyright 1 -> 2
    item1->setCopyright("Thomas B.");
    QVERIFY2(spySetCopyright12.count() == 1, "Set new copyright wasn't called on item2");

    // Set Copyright 2 -> 1
    item2->setCopyright("Thomas B.2");
    QVERIFY2(spySetCopyright21.count() == 2, "Set new copyright wasn't called on item1");
}

void ScorePropertiesItemTest::testLinkedItem()
{
    ScorePropertiesItem *item1 = new ScorePropertiesItem(this);
    ScorePropertiesItem *item2 = new ScorePropertiesItem(this);

    item1->linkWithItem(item2);

    QVERIFY2(item1->linkedItem() == item2, "Item 1 hasn't item2 as linked item");
    QVERIFY2(item2->linkedItem() == item1, "Item 2 hasn't item1 as linked item");
}

void ScorePropertiesItemTest::testSetDataWhenLinkItems()
{
    QString title("Testtitle");
    QString type("Testtype");
    QString composer("Composer");
    QString arranger("Arranger");
    QString year("2013");
    QString copyright("C TB");

    ScorePropertiesItem *item1 = new ScorePropertiesItem(this);
    ScorePropertiesItem *item2 = new ScorePropertiesItem(this);
    item1->setTitle(title);
    item1->setType(type);
    item1->setComposer(composer);
    item1->setArranger(arranger);
    item1->setYear(year);
    item1->setCopyright(copyright);

    item2->linkWithItem(item1);
    QVERIFY2(item2->title() == title, "Title was not set while linking items");
    QVERIFY2(item2->type() == type, "Type was not set while linking items");
    QVERIFY2(item2->composer() == composer, "Composer was not set while linking items");
    QVERIFY2(item2->arranger() == arranger, "Arranger was not set while linking items");
    QVERIFY2(item2->year() == year, "Year was not set while linking items");
    QVERIFY2(item2->copyright() == copyright, "Copyright was not set while linking items");
}

QTEST_APPLESS_MAIN(ScorePropertiesItemTest)

#include "tst_scorepropertiesitemtest.moc"
