/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICITEMFACTORY_H
#define MUSICITEMFACTORY_H

#include <musicitem.h>

class MusicItemFactory
{
public:
    MusicItemFactory() {}
    static MusicItem *getMusicItem(MusicItem::Type type);
private:
    class EmptyMusicItem : public MusicItem
    {
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
};

#endif // MUSICITEMFACTORY_H
