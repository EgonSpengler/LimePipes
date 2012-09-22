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
#include <instrument.h>

/* This Instrument is needed for testing the InstrumentManager.
   It should have a name, the same as a loaded static plugin.
   The InstrumentManager should load it only once.
   */

class TestInstrumentGHB  :  public QObject,
                            public InstrumentInterface
{
    Q_OBJECT
    Q_INTERFACES(InstrumentInterface)
public:
    QString name() const
        { return QString("Great Highland Bagpipe"); }
    Instrument *instrument() const
    { return new Instrument(LP::GreatHighlandBagpipe, QString("Great Highland Bagpipe")); }
};

#endif // TESTINSTRUMENTGHB_H
