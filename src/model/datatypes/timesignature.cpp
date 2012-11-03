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

void TimeSignature::writeToXmlStream(QXmlStreamWriter *writer)
{
    writer->writeStartElement(s_xmlTagName);
    writer->writeTextElement("BEATCOUNT", QString::number(beatCount(m_type)));
    writer->writeTextElement("BEATUNIT", QString::number(beatUnit(m_type)));
    writer->writeEndElement();
}
