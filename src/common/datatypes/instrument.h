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
#include <common/defines.h>

class InstrumentMetaData
{
public:
    InstrumentMetaData() {}
    virtual ~InstrumentMetaData() {}

    bool isValid() const { return !m_name.isEmpty(); }
    QString name() const;
    void setName(const QString &name);

    bool supportsSymbol(int type) const;
    QList<int> supportedSymbols() const;
    void setSupportedSymbols(const QList<int> &supportedSymbols);

    StaffType staffType() const;
    ClefType defaultClef() const;

    PitchContextPtr pitchContext() const;
    void setPitchContext(const PitchContextPtr &pitchContext);

private:
    QString m_name;
    PitchContextPtr m_pitchContext;
    QList<int> m_supportedSymbols;
};

class Instrument
{
public:
    explicit Instrument();
    explicit Instrument(LP::InstrumentType type,
                        const QString &name,
                        PitchContextPtr pitchContext = PitchContextPtr(new PitchContext()));
    Instrument(const Instrument& other);
    virtual ~Instrument() {}

    LP::InstrumentType type() const { return m_type; }
    QString name() const { return m_name; }

    const PitchContextPtr pitchContext() const { return m_pitchContext; }
    QStringList pitchNames() const { return m_pitchContext->pitchNames(); }
    virtual bool supportsSymbolType(int type) const = 0;

    StaffType staffType() const;
    ClefType defaultClef() const;

private:
    LP::InstrumentType m_type;
    QString m_name;
    PitchContextPtr m_pitchContext;
};

class NullInstrument : public Instrument
{
public:
    NullInstrument() : Instrument() {}
    bool supportsSymbolType(int type) const { Q_UNUSED(type) return false; }
};

#endif // INSTRUMENT_H
