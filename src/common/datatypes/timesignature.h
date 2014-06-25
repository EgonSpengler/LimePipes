/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TIMESIGNATURE_H
#define TIMESIGNATURE_H

#include <QDebug>
#include <QString>
#include <QMetaType>

class QXmlStreamWriter;
class QXmlStreamReader;

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

    explicit TimeSignature();
    explicit TimeSignature(Type type);
    ~TimeSignature() {}
    TimeSignature(const TimeSignature& timeSig) { m_type = timeSig.type(); }

    static int beatCount(Type type);
    static int beatUnit(Type type);

    int beatCount() const;
    int beatUnit() const;

    void setSignature(Type type) { m_type = type; }

    void setSignature(int beatCount, int beatUnit);
    Type type() const { return m_type; }

    void writeToXmlStream(QXmlStreamWriter *writer);
    void readFromXmlStream(QXmlStreamReader *reader);
    static QString xmlTagName() { return s_xmlTagName; }

    QString toString() const;
    static TimeSignature fromString(const QString& string);

    bool operator ==(const TimeSignature& other);

private:
    static QString s_xmlTagName;
    Type m_type;
};

QDebug operator <<(QDebug dbg, const TimeSignature &timeSig);

Q_DECLARE_METATYPE(TimeSignature)

#endif // TIMESIGNATURE_H
