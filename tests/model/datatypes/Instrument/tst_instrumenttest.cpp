/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <instrument.h>

class InstrumentTest : public QObject
{
    Q_OBJECT
    
public:
    InstrumentTest()
        : m_instrument(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testCreateInstrument();
    void testDefaultValues();
    void testQVariant();
    void testCopyConstructor();
    void testPitchContext();

private:
    InstrumentPtr m_instrument;
};

void InstrumentTest::init()
{
    m_instrument = InstrumentPtr(new Instrument());
}

void InstrumentTest::cleanup()
{
}

void InstrumentTest::testCreateInstrument()
{
    m_instrument = InstrumentPtr(new Instrument(LP::GreatHighlandBagpipe, QString("TestInstrument")));
    QVERIFY2(m_instrument->name() == "TestInstrument", "Failed to set instrument name in constructor");
    QVERIFY2(m_instrument->type() == LP::GreatHighlandBagpipe, "Failed to set instrument type in constructor");
}

void InstrumentTest::testDefaultValues()
{
    QVERIFY2(m_instrument->type() == LP::NoInstrument, "Empty instrument doesn't return NoInstrument type");
    QVERIFY2(m_instrument->name() == "No Instrument", "Empty instrument doesn't return No Instrument as name");
    QVERIFY2(m_instrument->pitchContext()->highestStaffPos() == 0, "Failed, default pitch context highest staff pos");
    QVERIFY2(m_instrument->pitchContext()->lowestStaffPos() == 0, "Failed, default pitch context lowest staff pos");
}

void InstrumentTest::testQVariant()
{
    m_instrument = InstrumentPtr(new Instrument(LP::GreatHighlandBagpipe, QString("TestInstrument")));
    QVariant var = QVariant::fromValue<InstrumentPtr>(m_instrument);
    QVERIFY2(var.value<InstrumentPtr>()->name().isEmpty() != true, "Failed using Instrument as QVariant");
}

void InstrumentTest::testCopyConstructor()
{
    Instrument instrument1(LP::BassDrum, QString("TestInstrument"));
    Instrument instrument2(instrument1);
    QVERIFY2(instrument2.type() == LP::BassDrum, "Failed copy constructor");
}

void InstrumentTest::testPitchContext()
{
    PitchContextPtr pitchContext = PitchContextPtr(new PitchContext());
    pitchContext->insertPitch(0, "pitch zero");
    pitchContext->insertPitch(1, "pitch one");
    pitchContext->insertPitch(2, "pitch two");
    pitchContext->insertPitch(-1, "pitch minus one");

    m_instrument = InstrumentPtr(new Instrument(LP::BassDrum, "Bass drum", pitchContext));
    QVERIFY2(m_instrument->pitchContext()->pitchNames().count() == pitchContext->pitchNames().count(),
             "Failed setting pitch context in constructor");
}

QTEST_APPLESS_MAIN(InstrumentTest)

#include "tst_instrumenttest.moc"
