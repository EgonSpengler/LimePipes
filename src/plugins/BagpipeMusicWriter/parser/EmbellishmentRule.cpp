/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "EmbellishmentRule.h"

EmbellishmentRule::EmbellishmentRule()
{
}

bool EmbellishmentRule::isEmpty() const
{
    if (m_name.isEmpty()) {
        return true;
    }

    if (m_appearance.isEmpty()) {
        return true;
    }

    return false;
}

QString EmbellishmentRule::name() const
{
    return m_name;
}

void EmbellishmentRule::setName(const QString &name)
{
    m_name = name;
}

QList<SymbolPitch> EmbellishmentRule::appearance() const
{
    return m_appearance;
}

void EmbellishmentRule::setAppearance(const QList<SymbolPitch> &appearance)
{
    m_appearance = appearance;
}
