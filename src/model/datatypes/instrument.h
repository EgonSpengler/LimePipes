/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QMetaType>
#include <QString>
#include "../../interfaces/interfaceglobals.h"

class Instrument
{
public:
    Instrument() : m_type(LP::NoInstrument), m_name(QString("No Instrument")) {}

    Instrument(LP::InstrumentType type, const QString &name )
        : m_type(type), m_name(name) {}
    Instrument(const Instrument& other)
        { this->m_type = other.m_type;
          this->m_name = other.m_name; }
    ~Instrument() {}

    QString name() const
        { return m_name; }
    LP::InstrumentType type() const
        { return m_type; }
    virtual bool supportsSymbolType(int type) const
        { Q_UNUSED(type) return false; }

private:
    LP::InstrumentType m_type;
    QString m_name;
};

Q_DECLARE_METATYPE(Instrument*)

#endif // INSTRUMENT_H
