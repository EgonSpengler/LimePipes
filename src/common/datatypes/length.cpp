/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class Length
  * Definition of the length data for symbols.
  */

#include <QDebug>
#include <QStringList>
#include "length.h"

const QMap<Length::Value, QString>Length::s_lengths(initLengths());

QMap<Length::Value, QString> Length::initLengths()
{
    QMap<Length::Value, QString> lengths;
    lengths.insert(_1, QString(tr("whole")));
    lengths.insert(_2, QString(tr("half")));
    lengths.insert(_4, QString(tr("quarter")));
    lengths.insert(_8, QString(tr("eighth")));
    lengths.insert(_16, QString(tr("sixteenth")));
    lengths.insert(_32, QString(tr("thirty-second")));
    lengths.insert(_64, QString(tr("sixty-fourth")));
    return lengths;
}

Length::Value Length::valueForName(const QString &name)
{
    if (s_lengths.values().contains(name)) {
        return s_lengths.key(name);
    }
    else {
        qWarning() << "There is no length value named " << name;
        return Length::_1;
    }
}

QString Length::nameForValue(Length::Value value)
{
    return s_lengths.value(value, QString(tr("no length for this value")));
}

QStringList Length::lengthNames()
{
    return QStringList(s_lengths.values());
}

int Length::toInt(Length::Value length)
{
    return static_cast<int>(length);
}

QList<int> Length::lengthValues()
{
    return QList<int>() << _1 << _2 << _4 << _8 <<
                           _16 << _32 << _64;
}
