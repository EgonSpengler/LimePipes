/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class Symbol
  * A Tune consists of Symbols.
  */

#include "symbol.h"
#include <datatypes/pitch.h>

Symbol::Symbol()
    : MusicItem(MusicItem::SymbolType, MusicItem::NoItemType)
{
    setDefaultSymbolOptions();
    initData(LP::NoSymbolType, LP::symbolType);
    initData( tr("No name symbol"), LP::symbolName);
}

Symbol::Symbol(int type, const QString &name)
    : MusicItem(MusicItem::SymbolType, MusicItem::NoItemType)
{
    setDefaultSymbolOptions();
    initData(type, LP::symbolType);
    initData(name, LP::symbolName);
}

void Symbol::setDefaultSymbolOptions()
{
    m_symbolOptions = Symbol::Options(Symbol::NoOption);
}

bool Symbol::hasPitch() const
{
    return m_symbolOptions.testFlag(Symbol::HasPitch);
}

PitchPtr Symbol::pitch() const
{
    if (data(LP::symbolPitch).canConvert<PitchPtr>()) {
        return data(LP::symbolPitch).value<PitchPtr>();
    }
    return PitchPtr(new Pitch());
}

bool Symbol::hasLength() const
{
    return m_symbolOptions.testFlag(Symbol::HasPitch);
}

Length::Value Symbol::length() const
{
    if (data(LP::symbolLength).canConvert<Length::Value>()) {
        return data(LP::symbolLength).value<Length::Value>();
    }
    return Length::_4;
}

bool Symbol::itemSupportsWritingOfData(int role) const
{
    switch (role) {
    case LP::symbolPitch:
        if (this->hasPitch())
        return true;
    case LP::symbolLength:
        if (this->hasLength())
            return true;
    default:
        return false;
    }
}

void Symbol::setSymbolOptions(Symbol::Options options)
{
    m_symbolOptions = options;
}
