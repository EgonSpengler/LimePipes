/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class TimeSignature
  * Time signature data for @ref MusicItem "MusicItems".
  */

#include "timesignature.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

QString TimeSignature::s_xmlTagName = QString("TIMESIG");

TimeSignature::TimeSignature()
    : m_type(_2_2)
{
}

TimeSignature::TimeSignature(TimeSignature::Type type)
    : m_type(type)
{
}

int TimeSignature::beatCount(TimeSignature::Type type)
{
    switch (type) {
    case _2_2:
    case _2_4:
        return 2;
    case _3_4:
    case _3_8:
        return 3;
    case _4_4:
        return 4;
    case _6_8:
        return 6;
    case _9_8:
        return 9;
    case _12_8:
        return 12;
    default:
        qWarning("type not supported in TimeSignature::beatCount");
        return 0;
    }
}

int TimeSignature::beatUnit(TimeSignature::Type type)
{
    switch (type) {
    case _2_2:
        return 2;
    case _2_4:
    case _3_4:
    case _4_4:
        return 4;
    case _3_8:
    case _6_8:
    case _9_8:
    case _12_8:
        return 8;
    default:
        qWarning("type not supported in TimeSignature::beatUnit");
        return 0;
    }
}

int TimeSignature::beatCount() const
{
    return TimeSignature::beatCount(m_type);
}

int TimeSignature::beatUnit() const
{
    return TimeSignature::beatUnit(m_type);
}

void TimeSignature::setSignature(int beatCount, int beatUnit)
{
    if (beatCount != 2 &&
        beatCount != 3 &&
        beatCount != 4 &&
        beatCount != 6 &&
        beatCount != 9 &&
        beatCount != 12)
        return;

    if (beatUnit != 2 &&
        beatUnit != 4 &&
        beatUnit != 8)
        return;

    if (beatCount ==  2 && beatUnit == 2) m_type = _2_2;
    if (beatCount ==  2 && beatUnit == 4) m_type = _2_4;
    if (beatCount ==  3 && beatUnit == 4) m_type = _3_4;
    if (beatCount ==  4 && beatUnit == 4) m_type = _4_4;
    if (beatCount ==  3 && beatUnit == 8) m_type = _3_8;
    if (beatCount ==  6 && beatUnit == 8) m_type = _6_8;
    if (beatCount ==  9 && beatUnit == 8) m_type =  _9_8;
    if (beatCount == 12 && beatUnit == 8) m_type = _12_8;
}

void TimeSignature::writeToXmlStream(QXmlStreamWriter *writer)
{
    writer->writeStartElement(s_xmlTagName);
    writer->writeTextElement("BEATCOUNT", QString::number(beatCount(m_type)));
    writer->writeTextElement("BEATUNIT", QString::number(beatUnit(m_type)));
    writer->writeEndElement();
}

void TimeSignature::readFromXmlStream(QXmlStreamReader *reader)
{
    int beatCount = 0;
    int beatUnit = 0;

    while (reader->readNext()) {
        if (reader->isStartElement()) {
            if (reader->name() == "BEATCOUNT") {
                QString beatCountText = QString().append(reader->readElementText());
                beatCount = beatCountText.toInt();
            }
            else if (reader->name() == "BEATUNIT") {
                QString beatUnitText = QString().append(reader->readElementText());
                beatUnit = beatUnitText.toInt();
            }
            else
                break;
        }

        if (reader->isEndElement()) {
            if (reader->name() == s_xmlTagName ||
                (beatCount != 0 && beatUnit != 0))
            break;
        }

        if (reader->hasError())
            break;
    }

    if (beatCount != 0 &&
        beatUnit != 0) {
        setSignature(beatCount, beatUnit);
    }
}
