/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTINSTRUMENTGHB_H
#define TESTINSTRUMENTGHB_H

#include <instrumentinterface.h>
#include <QString>
#include <datatypes/instrument.h>

/*
 * This Instrument is needed for testing the InstrumentManager.
 * It should have a name, the same as a loaded static plugin.
 * The InstrumentManager should load it only once.
 */

class TestInstrumentGHB  :  public QObject,
                            public InstrumentInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID InstrumentInterfaceIID)
    Q_INTERFACES(InstrumentInterface)

public:
    TestInstrumentGHB()
        : m_instrument(InstrumentPtr(new TestInstrument())) {}
    QString name() const
        { return QString("Great Highland Bagpipe"); }
    InstrumentPtr instrument() const
        { return m_instrument; }

private:
    class TestInstrument : public Instrument
    {
    public:
        TestInstrument()
            : Instrument(LP::GreatHighlandBagpipe, QString("Great Highland Bagpipe")) {}
        bool supportsSymbolType(int type) const
            { Q_UNUSED(type) return false; }
    };

    InstrumentPtr m_instrument;
};

#endif // TESTINSTRUMENTGHB_H
