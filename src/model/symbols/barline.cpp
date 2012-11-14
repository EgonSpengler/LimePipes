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
    setSymbolName();
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
        setSymbolName();
    }
}

void BarLine::afterWritingData(int role)
{
    if (role == LP::barLineRepeat)
        setSymbolName();
}

void BarLine::setSymbolName()
{
    Type type = data(LP::barLineType).value<BarLine::Type>();
    QString name = SymbolName;
        if (type == StartPart) {
            name += " ";
            name += tr("start of part");
        }
        if (type == EndPart) {
            name += " ";
            name += tr("end of part");
        }
        if (data(LP::barLineRepeat).toBool()) {
            name += " ";
            name += tr("with repeat");
        }
        initData(name, LP::symbolName);
}
