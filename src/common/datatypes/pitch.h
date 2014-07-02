/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PITCH_H
#define PITCH_H

#include <QMetaType>
#include <QJsonObject>

class QString;

class Pitch
{
public:
    explicit Pitch();
    explicit Pitch(int staffPos, const QString &name);
    Pitch(const Pitch &other);

    QString name() const { return m_name; }
    int staffPos() const { return m_staffPos; }

    bool operator ==(const Pitch &other) { return m_staffPos == other.m_staffPos; }

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

private:
    int m_staffPos;
    QString m_name;
};

Q_DECLARE_METATYPE(Pitch)

#endif // PITCH_H
