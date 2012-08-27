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

class Length
{
public:
    enum Type {
        _1 = 1,
        _2 = 2,
        _4 = 4,
        _8 = 8,
        _16 = 16,
        _32 = 32
    };

    explicit Length()
        : m_length(_1) {}
    Length(Type len)
        :m_length(len) {}
    Length(const Length &len)
        { m_length = len.length(); }
    Type length() const
        { return m_length; }
    void setLength( Type len )
        { m_length = len; }

private:
    Type m_length;
};

Q_DECLARE_METATYPE(Length)

#endif // LENGTH_H
