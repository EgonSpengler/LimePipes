/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MELODYNOTEBEHAVIOR_H
#define MELODYNOTEBEHAVIOR_H

#include <common/datahandling/symbolbehavior.h>

class MelodyNoteBehavior : public SymbolBehavior
{
public:
    MelodyNoteBehavior();

    // ItemBehavior interface
public:
    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);
};

#endif // MELODYNOTEBEHAVIOR_H
