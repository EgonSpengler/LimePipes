/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef DOUBLINGBEHAVIOR_H
#define DOUBLINGBEHAVIOR_H

#include <common/datahandling/symbolbehavior.h>

class DoublingBehavior : public SymbolBehavior
{
public:
    DoublingBehavior();

    // ItemBehavior interface
public:
    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);
};

#endif // DOUBLINGBEHAVIOR_H
