/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musicitem.h"

MusicItem::MusicItem(MusicItem *parent) :
    m_parent(parent)
{
    if(m_parent){
        m_parent->addChild(this);
    }
}

QVariant MusicItem::data(int role)
{
    if(role == Qt::DisplayRole){
        return m_name;
    }
    return QVariant();
}
