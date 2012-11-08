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
#include <QXmlStreamWriter>

Symbol::Symbol(MusicItem *parent)
    : MusicItem(MusicItem::SymbolType, MusicItem::NoItemType, parent),
      m_graphicBuilder(0)
{
    setDefaultSymbolOptions();
    initData(LP::NoSymbolType, LP::symbolType);
    initData( tr("No name symbol"), LP::symbolName);
}

Symbol::Symbol(int type, const QString &name)
    : MusicItem(MusicItem::SymbolType, MusicItem::NoItemType),
      m_graphicBuilder(0)
{
    setDefaultSymbolOptions();
    initData(type, LP::symbolType);
    initData(name, LP::symbolName);
}

Symbol::~Symbol()
{
    if (m_graphicBuilder != 0) {
        delete m_graphicBuilder;
    }
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

bool Symbol::hasGraphic() const
{
    if (m_graphicBuilder == 0)
        return false;
    return true;
}

void Symbol::setSymbolGraphicBuilder(SymbolGraphicBuilder *builder)
{
    if (m_graphicBuilder != 0) {
        delete m_graphicBuilder;
    }

    m_graphicBuilder = builder;

    if (m_graphicBuilder != 0) {
        SymbolGraphicPtr symbolGraphic = m_graphicBuilder->symbolGraphic();
        initData(QVariant::fromValue<SymbolGraphicPtr>(symbolGraphic), LP::symbolGraphic);
        m_graphicBuilder->updateSymbolGraphic();
    }
}

void Symbol::afterWritingData(int role)
{
    if (m_graphicBuilder != 0 &&
            m_graphicBuilder->isSymbolGraphicAffectedByDataRole(role))
    {
        m_graphicBuilder->updateSymbolGraphic();
    }
}

void Symbol::createSymbolPixmaps(int lineHeight)
{
    if (m_graphicBuilder != 0) {
        m_graphicBuilder->setLineHeight(lineHeight);
        m_graphicBuilder->createPixmaps(lineHeight);
    }
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
            setData(QVariant::fromValue<Length::Value>((Length::Value)length), LP::symbolLength);
        }
    }
}

void Symbol::writePitch(QXmlStreamWriter *writer)
{
    QVariant pitchVar = data(LP::symbolPitch);
    if (pitchVar.isValid() &&
            pitchVar.canConvert<PitchPtr>()) {
        PitchPtr pitch = pitchVar.value<PitchPtr>();
        writer->writeTextElement("PITCH", pitch->name());
    }
}

void Symbol::writeLength(QXmlStreamWriter *writer)
{
    QVariant lengthVar = data(LP::symbolLength);
    if (lengthVar.isValid() &&
            lengthVar.canConvert<Length::Value>()) {
        Length::Value length = lengthVar.value<Length::Value>();
        writer->writeTextElement("LENGTH", QString::number(length, 10));
    }
}

void Symbol::setSymbolOptions(Symbol::Options options)
{
    m_symbolOptions = options;
}
