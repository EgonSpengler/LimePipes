/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef EMBELLISHMENTRULE_H
#define EMBELLISHMENTRULE_H

#include <QHash>
#include <QString>

#include "ast/embellishment.h"
#include "ast/AstDefines.h"
#include "PitchRange.h"

/*!
 * \brief The EmbellishmentRule class
 * An embellishment rule consists of a defined appearance of the embellishment.
 * Because the embellishment normally stands between two melody notes, this appearance can only be
 * valid for some combinations of the preceeding pitch and the following pitch.
 */
class EmbellishmentRule
{
public:
    EmbellishmentRule();

    bool isEmpty() const;

    QString name() const;
    void setName(const QString &name);

    QList<SymbolPitch> appearance() const;
    void setAppearance(const QList<SymbolPitch> &appearance);

    /*!
     * \brief isValidFor Check, if this embellishment appearance is valid, if the embellishment is
     * between a preceeding melody note with preceedingPitch and a following melody note with
     * followingPitch.
     * \param preceedingPitch
     * \param followingPitch
     * \return true, if this appearance is valid between the given pitches.
     */
    bool isValidFor(SymbolPitch preceedingPitch, SymbolPitch followingPitch) const;

    void addValidCombination(const PitchRange &rangePreceding, const PitchRange &followingRange);

private:
    QString m_name;
    QList<SymbolPitch> m_appearance;
    QHash<PitchRange, PitchRange> m_validCombinations;
};

QDebug operator<<(QDebug dbg, const EmbellishmentRule &rule);

#endif // EMBELLISHMENTRULE_H
