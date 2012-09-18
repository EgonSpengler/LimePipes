/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TIMESIGNATURE_H
#define TIMESIGNATURE_H

#include <QMetaType>

class TimeSignature
{
public:
    enum Type {
        _2_2,
        _2_4,
        _3_4,
        _4_4,
        _3_8,
        _6_8,
        _9_8,
        _12_8
    };

    static int beatCount(Type type);
    static int beatUnit(Type type);

    explicit TimeSignature()
        : m_type(_2_2) {}
    explicit TimeSignature(Type type)
        : m_type(type) {}
    ~TimeSignature() {}
    TimeSignature(const TimeSignature& timeSig)
    { m_type = timeSig.signature(); }

    void setSignature(Type type)
        { m_type = type; }
    Type signature() const
        { return m_type; }

private:
    Type m_type;
};

Q_DECLARE_METATYPE(TimeSignature)

#endif // TIMESIGNATURE_H
