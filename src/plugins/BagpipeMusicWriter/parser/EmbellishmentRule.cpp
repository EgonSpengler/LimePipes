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

bool EmbellishmentRule::isValidFor(SymbolPitch preceedingPitch, SymbolPitch followingPitch) const
{
    bool isValid = false;
    auto it = m_validCombinations.constBegin();
    while (it != m_validCombinations.constEnd()) {
        if (it.key().contains(preceedingPitch) &&
                it.value().contains(followingPitch)) {
            isValid = true;
            break;
        }
        ++it;
    }

    return isValid;
}

void EmbellishmentRule::addValidCombination(const PitchRange &rangePreceding, const PitchRange &followingRange)
{
    if (!rangePreceding.isValid()) {
        qWarning() << "Can't add invalid range " << rangePreceding << " as preceding range to rule " << name();
        return;
    }

    if (!rangePreceding.isValid()) {
        qWarning() << "Can't add invalid range " << followingRange << " as following range to rule " << name();
        return;
    }

    m_validCombinations.insert(rangePreceding, followingRange);
}


QDebug operator<<(QDebug dbg, const EmbellishmentRule &rule)
{
    dbg.nospace() << "EmbellishmentRule (" << rule.name() << ", [";
    foreach (SymbolPitch pitch, rule.appearance()) {
        dbg.nospace() << pitchToString(pitch);
    }

    dbg.nospace() <<  "])";;

    return dbg.space();
}
