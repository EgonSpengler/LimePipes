/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <instrument_ids.h>

#include <greathighlandbagpipe.h>

class GreatHighlandBagpipeTest : public QObject
{
    Q_OBJECT
    
public:
    GreatHighlandBagpipeTest();
    
private Q_SLOTS:
    void testCreate();
    void testName();
    void testInstrumentID();
};

GreatHighlandBagpipeTest::GreatHighlandBagpipeTest()
{
}

void GreatHighlandBagpipeTest::testCreate()
{
    GreatHighlandBagpipe bagpipe;
    Q_UNUSED(bagpipe)
}

void GreatHighlandBagpipeTest::testName()
{
    GreatHighlandBagpipe bagpipe;
    QVERIFY2( bagpipe.name().isEmpty() == false, "Got empty string as Instrument name" );
}

void GreatHighlandBagpipeTest::testInstrumentID()
{
    GreatHighlandBagpipe bagpipe;
    QVERIFY2( bagpipe.instrumentId() == LP::GreatHighlandBagpipe, "Failed getting the right instrument ID for the Great Highland Bagpipe");
}

QTEST_APPLESS_MAIN(GreatHighlandBagpipeTest)

#include "tst_greathighlandbagpipetest.moc"
