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
#include <QSharedPointer>
#include "pitchcontext.h"
#include "../../interfaces/interfaceglobals.h"

class Instrument
{
public:
    explicit Instrument()
        : m_type(LP::NoInstrument), m_name(QString("No Instrument")), m_pitchContext(PitchContextPtr(new PitchContext())) {}

    explicit Instrument(LP::InstrumentType type,
                        const QString &name,
                        PitchContextPtr pitchContext = PitchContextPtr(new PitchContext()))
        : m_type(type), m_name(name), m_pitchContext(pitchContext) {}
    Instrument(const Instrument& other);
    virtual ~Instrument() {}

    QString name() const
        { return m_name; }
    LP::InstrumentType type() const
        { return m_type; }
    const PitchContextPtr pitchContext() const
        { return m_pitchContext; }
    virtual bool supportsSymbolType(int type) const
        { Q_UNUSED(type) return false; }
    QStringList pitchNames() const
        { return m_pitchContext->pitchNames(); }

private:
    LP::InstrumentType m_type;
    QString m_name;
    PitchContextPtr m_pitchContext;
};

typedef QSharedPointer<Instrument> InstrumentPtr;

Q_DECLARE_METATYPE(InstrumentPtr)

#endif // INSTRUMENT_H
