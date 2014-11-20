/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TIMESIGNATURE_H
#define TIMESIGNATURE_H


#include "symbol.h"

class TimeSignature : public Symbol
{
public:
    explicit TimeSignature(const QString &bwwCode, MusicItem *parent=0);

    quint8 beatCount() const;
    void setBeatCount(const quint8 &beatCount);

    quint8 beatUnit() const;
    void setBeatUnit(const quint8 &beatUnit);

    bool showAsSymbol() const;
    void setShowAsSymbol(bool showAsSymbol);

private:
    quint8 m_beatCount;
    quint8 m_beatUnit;
    bool m_showAsSymbol; //!< Show 4/4 as C or 2/4 as cut-common symbol
};

#endif // TIMESIGNATURE_H
