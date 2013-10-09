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

class AbstractScorePropertiesItemTest : public QObject
{
    Q_OBJECT

public:
    AbstractScorePropertiesItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testTitle();
    void testComposer();
    void testArranger();
    void testYear();
    void testCopyright();
    void testTimesignature();
    void testLinkWithItem();

private:
    ScorePropertiesItem *m_scorePropertiesItem;
};

AbstractScorePropertiesItemTest::AbstractScorePropertiesItemTest()
{
}

void AbstractScorePropertiesItemTest::init()
{
    m_scorePropertiesItem = new ScorePropertiesItem(this);
}

void AbstractScorePropertiesItemTest::cleanup()
{
    delete m_scorePropertiesItem;
}

void AbstractScorePropertiesItemTest::testTitle()
{
    QString title("title 1");
    QSignalSpy spy(m_scorePropertiesItem, SIGNAL(titleChanged(QString)));

    m_scorePropertiesItem->setTitle(title);
    QVERIFY2(m_scorePropertiesItem->title() == title, "Title was't set");
    QVERIFY2(spy.count() == 1, "Title changed signals wasn't emitted");

    m_scorePropertiesItem->setTitle(title);
    QVERIFY2(spy.count() == 1, "Title changed signal was emitted despite same title");
}

void AbstractScorePropertiesItemTest::testComposer()
{
    QString composer("composer");
    QSignalSpy spy(m_scorePropertiesItem, SIGNAL(composerChanged(QString)));

    m_scorePropertiesItem->setComposer(composer);
    QVERIFY2(m_scorePropertiesItem->composer() == composer, "Composer was't set");
    QVERIFY2(spy.count() == 1, "Composer changed signals wasn't emitted");

    m_scorePropertiesItem->setComposer(composer);
    QVERIFY2(spy.count() == 1, "Composer changed signal was emitted despite same Composer");
}

void AbstractScorePropertiesItemTest::testArranger()
{
    QString arranger("arranger");
    QSignalSpy spy(m_scorePropertiesItem, SIGNAL(arrangerChanged(QString)));

    m_scorePropertiesItem->setArranger(arranger);
    QVERIFY2(m_scorePropertiesItem->arranger() == arranger, "Arranger was't set");
    QVERIFY2(spy.count() == 1, "Arranger changed signals wasn't emitted");

    m_scorePropertiesItem->setArranger(arranger);
    QVERIFY2(spy.count() == 1, "Arranger changed signal was emitted despite same Arranger");
}

void AbstractScorePropertiesItemTest::testYear()
{
    QString year("2013");
    QSignalSpy spy(m_scorePropertiesItem, SIGNAL(yearChanged(QString)));

    m_scorePropertiesItem->setYear(year);
    QVERIFY2(m_scorePropertiesItem->year() == year, "Year was't set");
    QVERIFY2(spy.count() == 1, "Year changed signals wasn't emitted");

    m_scorePropertiesItem->setYear(year);
    QVERIFY2(spy.count() == 1, "Year changed signal was emitted despite same Year");
}

void AbstractScorePropertiesItemTest::testCopyright()
{
    QString copyright("2013");
    QSignalSpy spy(m_scorePropertiesItem, SIGNAL(copyrightChanged(QString)));

    m_scorePropertiesItem->setCopyright(copyright);
    QVERIFY2(m_scorePropertiesItem->copyright() == copyright, "Copyright was't set");
    QVERIFY2(spy.count() == 1, "Copyright changed signals wasn't emitted");

    m_scorePropertiesItem->setCopyright(copyright);
    QVERIFY2(spy.count() == 1, "Copyright changed signal was emitted despite same Copyright");
}

void AbstractScorePropertiesItemTest::testTimesignature()
{
    TimeSignature timeSig(TimeSignature::_9_8);
    QSignalSpy spy(m_scorePropertiesItem, SIGNAL(timeSignatureChanged(TimeSignature)));

    m_scorePropertiesItem->setTimeSignature(timeSig);
    QVERIFY2(m_scorePropertiesItem->timeSignature() == timeSig, "TimeSignature was't set");
    QVERIFY2(spy.count() == 1, "TimeSignature changed signals wasn't emitted");

    m_scorePropertiesItem->setTimeSignature(timeSig);
    QVERIFY2(spy.count() == 1, "TimeSignature changed signal was emitted despite same TimeSignature");
}

void AbstractScorePropertiesItemTest::testLinkWithItem()
{
    ScorePropertiesItem *item1 = new ScorePropertiesItem(this);
    ScorePropertiesItem *item2 = new ScorePropertiesItem(this);
    QSignalSpy spySetTitle12(item2, SIGNAL(titleChanged(QString)));
    QSignalSpy spySetTitle21(item1, SIGNAL(titleChanged(QString)));
    QSignalSpy spySetComposer12(item2, SIGNAL(composerChanged(QString)));
    QSignalSpy spySetComposer21(item1, SIGNAL(composerChanged(QString)));
    QSignalSpy spySetArranger12(item2, SIGNAL(arrangerChanged(QString)));
    QSignalSpy spySetArranger21(item1, SIGNAL(arrangerChanged(QString)));
    QSignalSpy spySetYear12(item2, SIGNAL(yearChanged(QString)));
    QSignalSpy spySetYear21(item1, SIGNAL(yearChanged(QString)));
    QSignalSpy spySetCopyright12(item2, SIGNAL(copyrightChanged(QString)));
    QSignalSpy spySetCopyright21(item1, SIGNAL(copyrightChanged(QString)));
    QSignalSpy spySetTimesignature12(item2, SIGNAL(timeSignatureChanged(TimeSignature)));
    QSignalSpy spySetTimesignature21(item1, SIGNAL(timeSignatureChanged(TimeSignature)));

    item1->linkWithItem(item2);

    // Set Title 1 -> 2
    item1->setTitle("testtitle");
    QVERIFY2(spySetTitle12.count() == 1, "Set new title wasn't called on item 2");

    // Set Title 2 -> 1
    item2->setTitle("testtitle2");
    QVERIFY2(spySetTitle21.count() == 2, "Set new title wasn't called on item 1");

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

    // Set TimeSignature 1 -> 2
    item1->setTimeSignature(TimeSignature(TimeSignature::_3_8));
    QVERIFY2(spySetTimesignature12.count() == 1, "Set new timesignature wasn't called on item2");

    // Set TimeSignature 2 -> 1
    item2->setTimeSignature(TimeSignature(TimeSignature::_2_2));
    QVERIFY2(spySetTimesignature21.count() == 2, "Set new timesignature wasn't called on item1");
}

QTEST_APPLESS_MAIN(AbstractScorePropertiesItemTest)

#include "tst_scorepropertiesitemtest.moc"