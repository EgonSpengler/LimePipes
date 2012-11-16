/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class BarLine
  * A @ref The BarLine symbol represents the vertical bar line in a Staff.
  */

#include "barline.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

const QString BarLine::SymbolName(tr("Barline"));

BarLine::BarLine(Type type, MusicItem *parent)
    : Symbol(LP::BarLine,  BarLine::SymbolName, parent)
{
    initData(QVariant::fromValue<BarLine::Type>(type), LP::barLineType);
    initData(QVariant(false), LP::barLineRepeat);
}

bool BarLine::itemSupportsWritingOfData(int role) const
{
    if (role == LP::barLineRepeat)
        return true;
    return Symbol::itemSupportsWritingOfData(role);
}

void BarLine::beforeWritingData(QVariant &value, int role)
{
    if (role == LP::barLineRepeat) {
        Type barLineType = data(LP::barLineType).value<BarLine::Type>();
        if (barLineType == Normal)
            value.setValue<bool>(false);
    }
}

void BarLine::writeItemDataToXmlStream(QXmlStreamWriter *writer)
{
    Symbol::writeItemDataToXmlStream(writer);

    QVariant typeVar = data(LP::barLineType);
    QVariant repeatVar = data(LP::barLineRepeat);
    if (typeVar.isValid() &&
            typeVar.canConvert<BarLine::Type>()) {
        Type barType = typeVar.value<BarLine::Type>();
        if (barType != Normal) {
            writer->writeTextElement("TYPE", typeName(barType));
            if (repeatVar.isValid() &&
                    repeatVar.canConvert<bool>()) {
                bool repeat = repeatVar.value<bool>();
                if (repeat) {
                    writer->writeStartElement("REPEAT");
                    writer->writeEndElement();
                }
            }
        }
    }
}

void BarLine::readCurrentElementFromXmlStream(QXmlStreamReader *reader)
{
    if (QString("TYPE").compare(reader->name(), Qt::CaseInsensitive) == 0) {
        BarLine::Type readType = typeForName(reader->readElementText());
        initData(QVariant::fromValue<BarLine::Type>(readType), LP::barLineType);
    }
    if (QString("REPEAT").compare(reader->name(), Qt::CaseInsensitive) == 0) {
        QVariant typeVar = data(LP::barLineType);
        if (typeVar.isValid() &&
                typeVar.canConvert<BarLine::Type>()) {
            BarLine::Type barType = typeVar.value<BarLine::Type>();
            if (barType == Normal)
                return;
            setData(true, LP::barLineRepeat);
        }
        BarLine::Type readType = typeForName(reader->readElementText());
        initData(QVariant::fromValue<BarLine::Type>(readType), LP::barLineType);
    }
    Symbol::readCurrentElementFromXmlStream(reader);
}

QString BarLine::typeName(Type barType)
{
    switch (barType) {
    case StartPart:
        return QString("Start");
    case EndPart:
        return QString("End");
    default:
        return QString("Normal");
    }
}

BarLine::Type BarLine::typeForName(const QString &typeName)
{
    if (typeName.compare("Start", Qt::CaseInsensitive) == 0)
        return StartPart;
    else if (typeName.compare("End", Qt::CaseInsensitive) == 0)
        return EndPart;
    else
        return Normal;
}
