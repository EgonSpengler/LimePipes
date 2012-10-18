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

Pitch::Pitch()
    : m_staffPos(0),
      m_name("no name")
{
}

Pitch::Pitch(int staffPos, const QString &name)
    : m_staffPos(staffPos), m_name(name)
{
}

Pitch::Pitch(const Pitch &other)
{
    this->m_name = other.name();
    this->m_staffPos = other.staffPos();
}
