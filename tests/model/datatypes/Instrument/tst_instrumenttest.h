/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef __INSTRUMENTTEST_H__
#define __INSTRUMENTTEST_H__

#include <QObject>
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
    void testSetGetStaffType();

private:
    class TestInstrument : public Instrument
    {
    public:
        TestInstrument()
            : Instrument() {}
        TestInstrument(LP::InstrumentType type, const QString &name, PitchContextPtr pitchContext = PitchContextPtr(new PitchContext()))
            : Instrument(type, name, pitchContext) {}
        bool supportsSymbolType(int type) const
        { Q_UNUSED(type) return false; }
    };

    InstrumentPtr m_instrument;
};

#endif
