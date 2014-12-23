/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "embellishment.h"

Embellishment::Embellishment(Embellishment::Type type, MusicItem *parent)
    : Symbol(T_Embellishment, parent),
      m_embellishmentType(type),
      m_precedingPitch(NoPitch),
      m_followingPitch(NoPitch),
      m_pitchHint(NoPitch)
{

}

Embellishment::Embellishment(Type type, SymbolPitch pitchHint, MusicItem *parent)
    : Symbol(T_Embellishment, parent),
      m_embellishmentType(type),
      m_precedingPitch(NoPitch),
      m_followingPitch(NoPitch),
      m_pitchHint(pitchHint)
{
}

Embellishment::Type Embellishment::embellishmentType() const
{
    return m_embellishmentType;
}

void Embellishment::setEmbellishmentType(const Type &embellishmentType)
{
    m_embellishmentType = embellishmentType;
}

SymbolPitch Embellishment::precedingPitch() const
{
    return m_precedingPitch;
}

void Embellishment::setPrecedingPitch(const SymbolPitch &precedingPitch)
{
    m_precedingPitch = precedingPitch;
}

SymbolPitch Embellishment::followingPitch() const
{
    return m_followingPitch;
}

void Embellishment::setFollowingPitch(const SymbolPitch &followingPitch)
{
    m_followingPitch = followingPitch;
}
SymbolPitch Embellishment::pitchHint() const
{
    return m_pitchHint;
}

void Embellishment::setPitchHint(const SymbolPitch &pitchHint)
{
    m_pitchHint = pitchHint;
}

QDebug operator<<(QDebug dbg, const Embellishment &embellishment)
{
    dbg.nospace() << "Embellishment (Type[" << static_cast<quint32>(embellishment.embellishmentType()) << "], "
                  << "Pitch Hint [" << pitchToString(embellishment.pitchHint()) << "], "
                  << "Preceeding Pitch [" << pitchToString(embellishment.precedingPitch()) << "] ,"
                  << "Following Pitch ["<< pitchToString(embellishment.followingPitch()) << "])";

    dbg.nospace() <<  "])";;

    return dbg.space();
}
