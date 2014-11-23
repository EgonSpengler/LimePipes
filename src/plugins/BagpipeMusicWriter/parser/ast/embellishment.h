/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef EMBELLISHMENT_H
#define EMBELLISHMENT_H

#include "AstDefines.h"
#include "symbol.h"

class Embellishment : public Symbol
{
public:
    enum Type {
        SINGLE_GRACE,
        DOUBLING_REG,
        DOUBLING_HALF,
        DOUBLING_THUMB
    };

    explicit Embellishment(Embellishment::Type type, MusicItem *parent=0);
    explicit Embellishment(Embellishment::Type type, SymbolPitch pitchHint, MusicItem *parent=0);

    Type embellishmentType() const;
    void setEmbellishmentType(const Type &embellishmentType);

    SymbolPitch precedingPitch() const;
    void setPrecedingPitch(const SymbolPitch &precedingPitch);

    SymbolPitch followingPitch() const;
    void setFollowingPitch(const SymbolPitch &followingPitch);

    SymbolPitch pitchHint() const;
    void setPitchHint(const SymbolPitch &pitchHint);

private:
    Type m_embellishmentType;
    SymbolPitch m_precedingPitch;  //!< see m_followingPitch
    SymbolPitch m_followingPitch;  //!< The pitch of the following melody note. This has to be set explicitly,
                                   //! because it does depend on the real pitch that is following this embellishment,
                                   //! not the pitch, that is written for this embellishment.
    SymbolPitch m_pitchHint;    //!< The pitch as it is read from parser (e.g. dbla with pitch low a).
                                //!< If no preceding pitch and/or following pitch is set, this hint will be used.
                                //!< Also, if this embellishment doesn't depend on the preceding or following pitch
                                //!< like single grace notes for example, the pitch hint must be set.
};

#endif // EMBELLISHMENT_H
