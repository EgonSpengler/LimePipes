/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOL_H
#define SYMBOL_H

#include <QCoreApplication>
#include <QScopedPointer>
#include <musicitem.h>
#include <itemdatatypes.h>
#include <datapolicycollection.h>
#include <datatypes/pitch.h>
#include <datatypes/length.h>
#include "../interfaces/interfaceglobals.h"

class Symbol : public MusicItem
{
    Q_DECLARE_TR_FUNCTIONS(MusicItem)
public:
    enum PitchUsage {
        HasPitch,
        HasNoPitch
    };

    enum LengthUsage {
        HasLength,
        HasNoLength
    };

    explicit Symbol();
    explicit Symbol(int type, const QString &name,
                    PitchUsage pitchUsage = HasNoPitch, LengthUsage lengthUsage = HasNoLength);
    virtual ~Symbol() {}
    int symbolType() const
        { return data(LP::symbolType).toInt(); }
    const DataPolicy dataPolicyForRole(int role) const;
    bool hasPitch() const;
    PitchPtr pitch() const;
    bool hasLength() const;
    Length::Value length() const;

private:
    static DataPolicyCollection *initPolicies();
    void setPitchIsUsed(PitchUsage pitchUsage);
    void setLengthIsUsed(LengthUsage lengthUsage);
    bool canRoleBeUsedInSubclass(int role) const;
    bool isRoleUsedInSubclass(int role) const;
    bool isPolicyReadable(int role) const;
    const static QScopedPointer<DataPolicyCollection> m_policies;
    bool m_pitchIsUsed;
    bool m_lengthIsUsed;
};

#endif // SYMBOL_H
