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
