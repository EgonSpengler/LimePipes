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
    InstrumentTest();
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testCreateInstrument();
    void testDefaultValues();
    void testQVariant();
    void testCopyConstructor();

private:
    Instrument *m_instrument;
};

InstrumentTest::InstrumentTest()
{
}

void InstrumentTest::init()
{
    m_instrument = new Instrument();
}

void InstrumentTest::cleanup()
{
    delete m_instrument;
}

void InstrumentTest::testCreateInstrument()
{
    delete m_instrument;
    m_instrument = new Instrument(LP::GreatHighlandBagpipe, QString("TestInstrument"));
    QVERIFY2(m_instrument->name() == "TestInstrument", "Failed to set instrument name in constructor");
    QVERIFY2(m_instrument->type() == LP::GreatHighlandBagpipe, "Failed to set instrument type in constructor");
}

void InstrumentTest::testDefaultValues()
{
    Instrument instrument;
    QVERIFY2(instrument.type() == LP::NoInstrument, "Empty instrument doesn't return NoInstrument type");
    QVERIFY2(instrument.name() == "No Instrument", "Empty instrument doesn't return No Instrument as name");

}

void InstrumentTest::testQVariant()
{
    delete m_instrument;
    m_instrument = new Instrument(LP::GreatHighlandBagpipe, QString("TestInstrument"));
    QVariant var = QVariant::fromValue<Instrument*>(m_instrument);
    QVERIFY2(var.value<Instrument*>()->name().isEmpty() != true, "Failed using Instrument as QVariant");
}

void InstrumentTest::testCopyConstructor()
{
    Instrument instrument1(LP::BassDrum, QString("TestInstrument"));
    Instrument instrument2(instrument1);
    QVERIFY2(instrument2.type() == LP::BassDrum, "Failed copy constructor");
}

QTEST_APPLESS_MAIN(InstrumentTest)

#include "tst_instrumenttest.moc"
