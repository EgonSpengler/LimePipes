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
#include <common/datatypes/pitch.h>
#include <common/defines.h>
#include <QXmlStreamWriter>

Symbol::Symbol(MusicItem *parent)
    : MusicItem(MusicItem::SymbolType, MusicItem::NoItemType, parent)
{
    setDefaultSymbolOptions();
    initData(LP::NoSymbolType, LP::SymbolType);
    initData( tr("No name symbol"), LP::SymbolName);
}

Symbol::Symbol(int type, const QString &name, MusicItem *parent)
    : MusicItem(MusicItem::SymbolType, MusicItem::NoItemType)
{
    Q_UNUSED(parent)
    setDefaultSymbolOptions();
    initData(type, LP::SymbolType);
    initData(name, LP::SymbolName);
}

Symbol::~Symbol()
{
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
    if (data(LP::SymbolPitch).canConvert<PitchPtr>()) {
        return data(LP::SymbolPitch).value<PitchPtr>();
    }
    return PitchPtr(new Pitch());
}

bool Symbol::hasLength() const
{
    return m_symbolOptions.testFlag(Symbol::HasPitch);
}

Length::Value Symbol::length() const
{
    if (data(LP::SymbolLength).canConvert<Length::Value>()) {
        return data(LP::SymbolLength).value<Length::Value>();
    }
    return Length::_4;
}

bool Symbol::itemSupportsWritingOfData(int role) const
{
    switch (role) {
    case LP::SymbolPitch:
        if (this->hasPitch())
            return true;
    case LP::SymbolPitchContext:
        if (this->hasPitch())
            return true;
    case LP::SymbolLength:
        if (this->hasLength())
            return true;
    default:
        return false;
    }
}

void Symbol::writeItemDataToXmlStream(QXmlStreamWriter *writer)
{
    if (this->hasPitch())
        writePitch(writer);
    if (this->hasLength())
        writeLength(writer);
}

void Symbol::readCurrentElementFromXmlStream(QXmlStreamReader *reader)
{
    if (QString("LENGTH").compare(reader->name(), Qt::CaseInsensitive) == 0) {
        int length = reader->readElementText().toInt();
        if (Length::lengthValues().contains(length)) {
            setData(QVariant::fromValue<Length::Value>((Length::Value)length), LP::SymbolLength);
        }
    }
}

void Symbol::writePitch(QXmlStreamWriter *writer)
{
    QVariant pitchVar = data(LP::SymbolPitch);
    if (pitchVar.isValid() &&
            pitchVar.canConvert<PitchPtr>()) {
        PitchPtr pitch = pitchVar.value<PitchPtr>();
        writer->writeTextElement("PITCH", pitch->name());
    }
}

void Symbol::writeLength(QXmlStreamWriter *writer)
{
    QVariant lengthVar = data(LP::SymbolLength);
    if (lengthVar.isValid() &&
            lengthVar.canConvert<Length::Value>()) {
        Length::Value length = lengthVar.value<Length::Value>();
        writer->writeTextElement("LENGTH", QString::number(length, 10));
    }
}

void Symbol::setSymbolOptions(Symbol::Options options)
{
    m_symbolOptions = options;

    if (options & HasLength) {
        initData(QVariant::fromValue<Length::Value>(Length::_8), LP::SymbolLength);
    }
    if (options & HasPitch) {
        Pitch *pitch = new Pitch(0, QStringLiteral("Default pitch"));
        m_defaultPitch.reset(pitch);
        initData(QVariant::fromValue<PitchPtr>(m_defaultPitch), LP::SymbolPitch);
    }
}
