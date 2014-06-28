/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "instrument.h"

/*! @class Instrument
    @brief A class which provides a Instrument.
*/

Instrument::Instrument()
    : m_type(LP::NoInstrument),
      m_name(QString("No Instrument")),
      m_pitchContext(PitchContextPtr(new PitchContext()))
{
}

Instrument::Instrument(LP::InstrumentType type, const QString &name, PitchContextPtr pitchContext)
    : m_type(type),
      m_name(name),
      m_pitchContext(pitchContext)
{
}

Instrument::Instrument(const Instrument &other)
{
    this->m_type = other.m_type;
    this->m_name = other.m_name;
    this->m_pitchContext = other.m_pitchContext;
}

StaffType Instrument::staffType() const
{
    return m_pitchContext->staffType();
}

ClefType Instrument::defaultClef() const
{
    return m_pitchContext->defaultClef();
}

QString InstrumentMetaData::name() const
{
    return m_name;
}

void InstrumentMetaData::setName(const QString &name)
{
    m_name = name;
}

bool InstrumentMetaData::supportsSymbol(int type) const
{
    return m_supportedSymbols.contains(type);
}

QList<int> InstrumentMetaData::supportedSymbols() const
{
    return m_supportedSymbols;
}

void InstrumentMetaData::setSupportedSymbols(const QList<int> &supportedSymbols)
{
    m_supportedSymbols = supportedSymbols;
}

StaffType InstrumentMetaData::staffType() const
{
    if (!m_pitchContext.isNull())
        return m_pitchContext->staffType();

    return StaffType::None;
}

ClefType InstrumentMetaData::defaultClef() const
{
    if (!m_pitchContext.isNull())
        return m_pitchContext->defaultClef();

    return ClefType::G;
}

PitchContextPtr InstrumentMetaData::pitchContext() const
{
    return m_pitchContext;
}

void InstrumentMetaData::setPitchContext(const PitchContextPtr &pitchContext)
{
    m_pitchContext = pitchContext;
}



