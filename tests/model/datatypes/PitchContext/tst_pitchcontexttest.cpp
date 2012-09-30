/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <pitchcontext.h>

#include <QDebug>

class PitchContextTest : public QObject
{
    Q_OBJECT
    
public:
    PitchContextTest()
        :m_context(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testDefaultConstructor();
    void testLowestStaffPos();
    void testHighestStaffPos();
    void testPitchNames();
    void testPitchForName();
    void testPitchForStaffPos();

private:
    PitchContext *m_context;
};

void PitchContextTest::init()
{
    m_context = new PitchContext();
    m_context->insertPitch(0, "pitch zero");
    m_context->insertPitch(1, "pitch one");
    m_context->insertPitch(2, "pitch two");
    m_context->insertPitch(3, "pitch three");
    m_context->insertPitch(-2, "pitch minus two");
    m_context->insertPitch(-1, "pitch minus one");

}

void PitchContextTest::cleanup()
{
    delete m_context;
}

void PitchContextTest::testDefaultConstructor()
{
    delete m_context;
    m_context = new PitchContext();
    QVERIFY2(m_context->lowestStaffPos() == 0, "Fail, default lowest staff position should be 0");
    QVERIFY2(m_context->highestStaffPos() == 0, "Fail, default highest staff position should be 0");
    QVERIFY2(m_context->pitchNames().count() == 1, "Fail, after default constructor it hasn't exactly one item");
    QVERIFY2(m_context->pitchNames().at(0) == "No pitch", "Fail, after default constructor, the existing item hasn't the right name");
    QVERIFY2(m_context->pitchForName("No pitch")->staffPos() == 0, "Fail, the default staff pos should be 0");
    QVERIFY2(m_context->pitchForName("invalid name")->staffPos() == 0, "Fail, invalid staff pos should be 0");
}

void PitchContextTest::testLowestStaffPos()
{
    QVERIFY2(m_context->lowestStaffPos() == -2, "Fail, wrong lowest position");
}

void PitchContextTest::testHighestStaffPos()
{
    QVERIFY2(m_context->highestStaffPos() == 3, "Fail, wrong highest position");
}

void PitchContextTest::testPitchNames()
{
    int lowest = m_context->lowestStaffPos();
    int highest = m_context->highestStaffPos();
    int pitchCount = highest - lowest +1;
    QVERIFY2(m_context->pitchNames().count() == pitchCount, "Count of pitch names doesn't fit with calculated pitches between lowest and highest");
}

void PitchContextTest::testPitchForName()
{
    PitchPtr testPitch = m_context->pitchForName("pitch two");
    QVERIFY2(testPitch->name() == "pitch two", "Failed getting right pitch name");
    QVERIFY2(testPitch->staffPos() == 2, "Failed getting right pitch pos");
}

void PitchContextTest::testPitchForStaffPos()
{
    PitchPtr testPitch = m_context->pitchForStaffPos(2);
    QVERIFY2(testPitch->name() == "pitch two", "Failed getting right pitch name");
    QVERIFY2(testPitch->staffPos() == 2, "Failed getting right pitch pos");
}

QTEST_APPLESS_MAIN(PitchContextTest)

#include "tst_pitchcontexttest.moc"
