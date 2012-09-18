/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCORE_H
#define SCORE_H

#include <QScopedPointer>
#include <musicitem.h>
#include <itemdatatypes.h>
#include <datapolicycollection.h>

#include <QDebug>

class Score : public MusicItem
{
public:
    explicit Score()
        : MusicItem(MusicItem::ScoreType, MusicItem::TuneType) {}
    explicit Score(const QString &title)
        : MusicItem(MusicItem::ScoreType, MusicItem::TuneType)
        { setTitle(title); }
    const DataPolicy dataPolicyForRole(int role) const
        { return m_policies->policyForRole(role); }

    void setTitle(const QString &title);
    QString title() const
        { return data(LP::scoreTitle).toString(); }  

private:
    const static QScopedPointer<DataPolicyCollection> m_policies;
    static DataPolicyCollection *initPolicies();
};

#endif // SCORE_H
