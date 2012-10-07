/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef LENGTH_H
#define LENGTH_H

#include <QMetaType>
#include <QHash>
#include <QString>
#include <QList>
#include <QCoreApplication>

class Length
{
    Q_DECLARE_TR_FUNCTIONS(LengthValues)
public:
    enum Value {
        _1 = 1,
        _2 = 2,
        _4 = 4,
        _8 = 8,
        _16 = 16,
        _32 = 32,
        _64 = 64
    };
    static Value valueForName(const QString &name);
    static QString nameForValue(Length::Value value);
    static QStringList lengthNames();
    static QList<int> lengthValues();

private:
    explicit Length();
    static QMap<Length::Value, QString> initLengths();
    const static QMap<Length::Value, QString>s_lengths;
};

Q_DECLARE_METATYPE(Length::Value)

#endif // LENGTH_H
