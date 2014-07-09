/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class Pitch
  * Pitch data for Symbols with a pitch.
  */

#include "pitch.h"
#include <QString>

static const QString StaffPosKey("staff pos");
static const QString NameKey("name");

Pitch::Pitch()
    : m_staffPos(0)
{
}

Pitch::Pitch(int staffPos, const QString &name)
    : m_staffPos(staffPos),
      m_name(name)
{
}

Pitch::Pitch(const Pitch &other)
{
    this->m_name = other.name();
    this->m_staffPos = other.staffPos();
}

QJsonObject Pitch::toJson() const
{
    QJsonObject json;
    json.insert(StaffPosKey, m_staffPos);
    json.insert(NameKey, m_name);

    return json;
}

void Pitch::fromJson(const QJsonObject &json)
{
    m_staffPos = json.value(StaffPosKey).toInt();
    m_name = json.value(NameKey).toString();
}
