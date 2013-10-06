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
#include "abstractscorepropertiesitemdummy.h"

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
    AbstractScorePropertiesItem *m_scorePropertiesItem;
};

AbstractScorePropertiesItemTest::AbstractScorePropertiesItemTest()
{
}

void AbstractScorePropertiesItemTest::init()
{
    m_scorePropertiesItem = new AbstractScorePropertiesItemDummy(this);
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
    AbstractScorePropertiesItemDummy *item1 = new AbstractScorePropertiesItemDummy(this);
    AbstractScorePropertiesItemDummy *item2 = new AbstractScorePropertiesItemDummy(this);
    QSignalSpy spySetTitle12(item2, SIGNAL(setNewTitleCalled()));
    QSignalSpy spySetTitle21(item1, SIGNAL(setNewTitleCalled()));

    item1->linkWithItem(item2);

    // Set Title 1 -> 2
    item1->setTitle("testtitle");
    QVERIFY2(spySetTitle12.count() == 1, "Set new title wasn't called on item 2");

    // Set Title 2 -> 1
    item2->setTitle("testtitle");
    QVERIFY2(spySetTitle21.count() == 1, "Set new title wasn't called on item 1");
}

QTEST_APPLESS_MAIN(AbstractScorePropertiesItemTest)

#include "tst_abstractscorepropertiesitemtest.moc"
