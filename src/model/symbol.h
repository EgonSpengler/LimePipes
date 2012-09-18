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
#include "../interfaces/interfaceglobals.h"

class Symbol : public MusicItem
{
    Q_DECLARE_TR_FUNCTIONS(MusicItem)
public:
    explicit Symbol();
    explicit Symbol(int type, const QString &name);
    virtual ~Symbol() {}
    int symbolType() const
        { return data(LP::symbolType).toInt(); }
    const DataPolicy dataPolicyForRole(int role) const
        { return m_policies->policyForRole(role); }

private:
    const static QScopedPointer<DataPolicyCollection> m_policies;
    static DataPolicyCollection *initPolicies();
};

#endif // SYMBOL_H
