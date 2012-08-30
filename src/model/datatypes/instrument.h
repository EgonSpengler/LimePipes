/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <instrumentinterface.h>
#include <plugins/GreatHighlandBagpipe/greathighlandbagpipe.h>
#include <QMetaType>
#include <QString>

class Instrument : public InstrumentInterface
{
public:
    Instrument() : m_instrument(new GreatHighlandBagpipe) {}
    Instrument(InstrumentInterface *instrument)
        :m_instrument(instrument) {}
    ~Instrument() {}
    Instrument(const Instrument& other)
        { this->m_instrument = other.instrument(); }

    void setInstrument(InstrumentInterface *instrument)
        { m_instrument = instrument; }
    InstrumentInterface *instrument() const
        { return m_instrument; }

    QString name() const
        { return m_instrument->name(); }
    LP::InstrumentId instrumentId() const
        { return m_instrument->instrumentId(); }

private:
    InstrumentInterface *m_instrument;
};

Q_DECLARE_METATYPE(Instrument)

#endif // INSTRUMENT_H
