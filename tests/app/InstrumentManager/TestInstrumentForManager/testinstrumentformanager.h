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
    TestInstrumentForManager()
        : m_instrument(InstrumentPtr(new Instrument(LP::BassDrum, QString("Test instrument")))) {}
    QString name() const
        { return QString("Test instrument"); }
    InstrumentPtr instrument() const
    { return m_instrument; }

private:
    InstrumentPtr m_instrument;
};

#endif // TESTINSTRUMENTFORMANAGER_H
