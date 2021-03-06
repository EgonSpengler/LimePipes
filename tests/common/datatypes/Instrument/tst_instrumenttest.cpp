/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "tst_instrumenttest.h"

void InstrumentTest::init()
{
    m_instrument = InstrumentPtr(new TestInstrument());
}

void InstrumentTest::cleanup()
{
}

void InstrumentTest::testCreateInstrument()
{
    m_instrument = InstrumentPtr(new TestInstrument(LP::GreatHighlandBagpipe, "Test Instrument"));
    QVERIFY2(m_instrument->name() == "Test Instrument", "Failed to set instrument name in constructor");
    QVERIFY2(m_instrument->type() == LP::GreatHighlandBagpipe, "Failed to set instrument type in constructor");
}

void InstrumentTest::testDefaultValues()
{
    QVERIFY2(m_instrument->type() == LP::NoInstrument, "Empty instrument doesn't return NoInstrument type");
    QVERIFY2(m_instrument->name() == "No Instrument", "Empty instrument doesn't return No Instrument as name");
    QVERIFY2(m_instrument->pitchContext()->highestStaffPos() == 0, "Failed, default pitch context highest staff pos");
    QVERIFY2(m_instrument->pitchContext()->lowestStaffPos() == 0, "Failed, default pitch context lowest staff pos");
    QVERIFY2(m_instrument->staffType() == StaffType::None, "Returned wrong default staff type");
}

void InstrumentTest::testQVariant()
{
    m_instrument = InstrumentPtr(new TestInstrument());
    QVariant var = QVariant::fromValue<InstrumentPtr>(m_instrument);
    QVERIFY2(var.value<InstrumentPtr>()->name().isEmpty() != true, "Failed using Instrument as QVariant");
}

void InstrumentTest::testCopyConstructor()
{
    PitchContextPtr pitchContext = PitchContextPtr(new PitchContext());
    pitchContext->insertPitch(0, "testpitch");

    TestInstrument instrument1(LP::BassDrum, QString("TestInstrument"), pitchContext);
    TestInstrument instrument2(instrument1);
    QVERIFY2(instrument2.type() == LP::BassDrum, "Failed copy constructor");
    QVERIFY2(instrument2.pitchContext().isNull() == false, "Failed, there is no pitch context");
    QVERIFY2(instrument2.pitchContext()->pitchForStaffPos(0)->name() == "testpitch", "Failed getting pitchcontext from copy constructor");
    QVERIFY2(instrument2.name() == "TestInstrument", "Failed getting instrument name");
}

void InstrumentTest::testPitchContext()
{
    PitchContextPtr pitchContext = PitchContextPtr(new PitchContext());
    pitchContext->insertPitch(0, "pitch zero");
    pitchContext->insertPitch(1, "pitch one");
    pitchContext->insertPitch(2, "pitch two");
    pitchContext->insertPitch(-1, "pitch minus one");

    m_instrument = InstrumentPtr(new TestInstrument(LP::BassDrum, "Bass drum", pitchContext));
    QVERIFY2(m_instrument->pitchContext()->pitchNames().count() == pitchContext->pitchNames().count(),
             "Failed setting pitch context in constructor");
}

void InstrumentTest::testSetGetStaffType()
{
    StaffType testStaffType = StaffType::Standard;
    m_instrument->setStaffType(testStaffType);
    QVERIFY2(m_instrument->staffType() == testStaffType,
             "Failed setting/getting staff type");
}

QTEST_APPLESS_MAIN(InstrumentTest)

#include "tst_instrumenttest.moc"
