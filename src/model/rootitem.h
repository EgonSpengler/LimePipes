/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ROOTITEM_H
#define ROOTITEM_H

#include <musicitem.h>

class RootItem : public MusicItem
{
public:
    explicit RootItem()
        : MusicItem(MusicItem::RootItemType, MusicItem::ScoreType) {}
    const DataPolicy dataPolicyForRole(int role) const
    { Q_UNUSED(role) return DataPolicy(DataPolicy::NoAccess); }
};

#endif // ROOTITEM_H
