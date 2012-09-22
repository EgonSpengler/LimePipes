/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTINSTRUMENTFORMANAGER_H
#define TESTINSTRUMENTFORMANAGER_H

#include <instrumentinterface.h>
#include <QString>
#include <instrument.h>

class TestInstrumentForManager :  public QObject,
                                  public InstrumentInterface
{
    Q_OBJECT
    Q_INTERFACES(InstrumentInterface)
public:
    QString name() const
        { return QString("Test instrument"); }
    Instrument *instrument() const
    { return new Instrument(LP::BassDrum, QString("Test instrument")); }
};

#endif // TESTINSTRUMENTFORMANAGER_H
