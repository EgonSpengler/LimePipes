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
#include <instrumentinterface.h>

class InstrumentTest : public QObject
{
    Q_OBJECT
    
public:
    InstrumentTest();
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testCreateInstrument();
    void testQVariant();
    void testSetInstrument();
    void testInstrumentDefaultValues();
    void testInstrumentInterfaceImplementation();

private:
    Instrument *m_instrument;
    InstrumentInterface *m_interface;

    class TestInstrument : public InstrumentInterface
    {
        QString name() const
            { return QString("TestInstrument"); }
        LP::InstrumentId instrumentId() const
            { return LP::BassDrum; }
    };
};

InstrumentTest::InstrumentTest()
{
}

void InstrumentTest::init()
{
    m_instrument = new Instrument();
    m_interface = new TestInstrument();
}

void InstrumentTest::cleanup()
{
    delete m_instrument;
    delete m_interface;
}

void InstrumentTest::testCreateInstrument()
{
    delete m_instrument;
    m_instrument = new Instrument(m_interface);
    QVERIFY2(m_instrument->name() == m_interface->name(), "Failed to set InstrumentInterface in constructor");
}

void InstrumentTest::testQVariant()
{
    QVariant var = QVariant::fromValue(Instrument());
    QVERIFY2(var.value<Instrument>().name().isEmpty() != true, "Failed using Instrument as QVariant");
}

void InstrumentTest::testSetInstrument()
{
    m_instrument->setInstrument(m_interface);
    QVERIFY2(m_instrument->name() == m_interface->name(), "Failed to set instrument");
    QVERIFY2(m_instrument->instrument() == m_interface, "Failed to get the instrument");
}

void InstrumentTest::testInstrumentDefaultValues()
{
    QVERIFY2(m_instrument->name() == "Great Highland Bagpipe", "Failed default value name");
    QVERIFY2(m_instrument->instrumentId() == LP::GreatHighlandBagpipe, "Failed default value id");
}

void InstrumentTest::testInstrumentInterfaceImplementation()
{
    m_instrument->setInstrument(m_interface);

    QVERIFY2(m_instrument->name() == m_interface->name(), "Failed to get the name");
    QVERIFY2(m_instrument->instrumentId() == m_interface->instrumentId(), "Failed to get the ID");
}

QTEST_APPLESS_MAIN(InstrumentTest)

#include "tst_instrumenttest.moc"
