/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TUNE_H
#define TUNE_H

#include <QScopedPointer>
#include <musicitem.h>
#include <symbol.h>
#include <itemdatatypes.h>
#include <datatypes/instrument.h>
#include <datapolicycollection.h>

class Tune : public MusicItem
{
public:
    explicit Tune()
        : MusicItem(MusicItem::TuneType, MusicItem::SymbolType)
        { setInstrument(new Instrument()); }
    explicit Tune(Instrument *instrument)
        : MusicItem(MusicItem::TuneType, MusicItem::SymbolType)
        { setInstrument(instrument); }

    Instrument *instrument() const
        { return data(LP::tuneInstrument).value<Instrument*>(); }
    bool okToInsertChild(const MusicItem *item);
    const DataPolicy dataPolicyForRole(int role) const
        { return m_policies->policyForRole(role); }
    QVariant readData(int role) const;

private:
    bool hasInstrument() const
        { return data(LP::tuneInstrument).isValid(); }
    void setInstrument(Instrument *instrument);
    const Symbol *symbolFromMusicItem(const MusicItem *item)
        { return static_cast<const Symbol*>(item); }
    const static QScopedPointer<DataPolicyCollection> m_policies;
    static DataPolicyCollection *initPolicies();
};

#endif // TUNE_H
