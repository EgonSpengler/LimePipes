/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOL_H
#define SYMBOL_H

#include <QCoreApplication>
#include <musicitem.h>
#include <itemdatatypes.h>
#include <datatypes/pitch.h>
#include <datatypes/length.h>
#include "../interfaces/interfaceglobals.h"

class Symbol : public MusicItem
{
    Q_DECLARE_TR_FUNCTIONS(MusicItem)
public:
    enum Option {
        NoOption =     0x00,
        HasPitch =     0x01,
        HasLength =    0x02
    };
    Q_DECLARE_FLAGS(Options, Option)

    explicit Symbol();
    explicit Symbol(int type, const QString &name);
    virtual ~Symbol() {}
    int symbolType() const
        { return data(LP::symbolType).toInt(); }
    bool hasPitch() const;
    PitchPtr pitch() const;
    bool hasLength() const;
    Length::Value length() const;
    bool itemSupportsWritingOfData(int role) const;

protected:
    void setSymbolOptions(Symbol::Options options);

private:
    void setDefaultSymbolOptions();
    Symbol::Options m_symbolOptions;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Symbol::Options)

#endif // SYMBOL_H
