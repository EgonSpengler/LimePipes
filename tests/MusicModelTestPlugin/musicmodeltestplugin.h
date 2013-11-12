/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICMODELTESTPLUGIN_H
#define MUSICMODELTESTPLUGIN_H

#include "testinstrument.h"
#include <QObject>
#include <QStringList>
#include <instrumentinterface.h>
#include <symbolinterface.h>

namespace {

const char *symbolNameWithPitchAndLength = "Testsymbol with pitch and length";

class TestsymbolWithPitchAndLength : public Symbol
{
public:
    TestsymbolWithPitchAndLength(PitchPtr pitch)
        : Symbol(LP::MelodyNote, symbolNameWithPitchAndLength)
    {
        setSymbolOptions(Symbol::HasPitch | Symbol::HasLength);

        initData(QVariant::fromValue<PitchPtr>(pitch), LP::SymbolPitch);
        initData(QVariant::fromValue<Length::Value>(Length::_16), LP::SymbolLength);
    }
};

}

class MusicModelTestPlugin :    public QObject,
                                public InstrumentInterface,
                                public SymbolInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID InstrumentInterfaceIID)
    Q_INTERFACES(InstrumentInterface SymbolInterface)

public:
    MusicModelTestPlugin()
        : m_instrument(InstrumentPtr(new TestInstrument())) {}

    // Instrument interface
    InstrumentPtr instrument() const { return m_instrument; }
    QString name() const { return m_instrument->name(); }

    // Symbol interface
    QStringList symbols() const { return QStringList() << "Testsymbol" << symbolNameWithPitchAndLength; }
    Symbol *getSymbol(const QString &symbol);

private:
    InstrumentPtr m_instrument;
};

#endif // MUSICMODELTESTPLUGIN_H
