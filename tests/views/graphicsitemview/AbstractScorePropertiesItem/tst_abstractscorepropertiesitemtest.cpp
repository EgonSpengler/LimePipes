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

QTEST_APPLESS_MAIN(AbstractScorePropertiesItemTest)

#include "tst_abstractscorepropertiesitemtest.moc"
