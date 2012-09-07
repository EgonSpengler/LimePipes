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
    RootItem()
        : MusicItem(MusicItem::RootItemType, MusicItem::ScoreType) {}
    QVariant data(int role) const
    {
        Q_UNUSED(role);
        return QVariant();
    }
    void setData(const QVariant &value, int role)
    {
        Q_UNUSED(value);
        Q_UNUSED(role);
    }
};

#endif // ROOTITEM_H
