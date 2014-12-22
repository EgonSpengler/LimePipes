/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef EMBELLISHMENTRULE_H
#define EMBELLISHMENTRULE_H

#include <QString>

#include "ast/embellishment.h"
#include "ast/AstDefines.h"

class EmbellishmentRule
{
public:
    EmbellishmentRule();

    bool isEmpty() const;

    QString name() const;
    void setName(const QString &name);

    QList<SymbolPitch> appearance() const;
    void setAppearance(const QList<SymbolPitch> &appearance);

private:
    QString m_name;
    QList<SymbolPitch> m_appearance;
};

#endif // EMBELLISHMENTRULE_H
