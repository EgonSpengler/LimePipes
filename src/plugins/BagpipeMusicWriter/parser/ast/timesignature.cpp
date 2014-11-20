/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QStringList>

#include "AstDefines.h"
#include "timesignature.h"

TimeSignature::TimeSignature(const QString &bwwCode, MusicItem *parent)
    : Symbol(T_TimeSignature, parent),
      m_beatCount(4),
      m_beatUnit(4),
      m_showAsSymbol(false)
{
    if (bwwCode == QStringLiteral("C")) {
        m_beatCount = 4;
        m_beatUnit = 4;
        m_showAsSymbol = true;
        return;
    }

    if (bwwCode == QStringLiteral("C_")) {
        m_beatCount = 2;
        m_beatUnit = 2;
        m_showAsSymbol = true;
        return;
    }

    QStringList timeSigParts(bwwCode.split(QLatin1Char('_')));

    if (timeSigParts.count() != 2) {
        return;
    }

    m_showAsSymbol = false;
    m_beatCount = timeSigParts.at(0).toInt();
    m_beatUnit = timeSigParts.at(1).toInt();

    if (m_beatCount == 0 ||
            m_beatUnit == 0) {
        m_beatCount = 4;
        m_beatUnit = 4;
    }
}

quint8 TimeSignature::beatCount() const
{
    return m_beatCount;
}

void TimeSignature::setBeatCount(const quint8 &beatCount)
{
    m_beatCount = beatCount;
}
quint8 TimeSignature::beatUnit() const
{
    return m_beatUnit;
}

void TimeSignature::setBeatUnit(const quint8 &beatUnit)
{
    m_beatUnit = beatUnit;
}
bool TimeSignature::showAsSymbol() const
{
    return m_showAsSymbol;
}

void TimeSignature::setShowAsSymbol(bool showAsSymbol)
{
    m_showAsSymbol = showAsSymbol;
}



