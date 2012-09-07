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
#include <musicitem.h>
#include <itemdatatypes.h>
#include "../interfaces/interfaceglobals.h"

class Symbol : public MusicItem
{
    Q_DECLARE_TR_FUNCTIONS(MusicItem)
public:
    explicit Symbol();
    Symbol(int type, const QString &name);
    int symbolType() const
        { return data(LP::symbolType).toInt(); }
    QVariant data(int role) const;
    void setData(const QVariant &value, int role);

private:
    int mergeDoubleRoles(int role) const;
    bool isRoleAccepted(int role) const;
};

#endif // SYMBOL_H
