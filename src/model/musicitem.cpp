/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class MusicItem musicitem.h
  * @brief MusicItem builds the hierarchic data, which represents a music sheet.
  *
  * @fn bool MusicItem::okToInsertChild(const MusicItem *item)
  * @brief By overwriting this member function, subclasses can restrict the insertion of child items.
  *     E.g. a Tune supports not all available Symbol types to be inserted.
  *     It can check the type and return false if the Symbol is not supported.
  * @param item The item to be inserted.
  * @return True by default.
  *
  * @fn void initData(const QVariant &value, int role)
  * @brief Subclasses can initialize read only data with this method.
  */

#include "musicitem.h"


MusicItem::MusicItem(Type type, Type childType, MusicItem *parent)
    : m_type(type), m_childType(childType), m_parent(parent)
{
    if (m_parent)
        m_parent->addChild(this);
}

bool MusicItem::insertChild(int row, MusicItem *item)
{
    if (m_childType == NoItemType)
        return false;

    if (m_childType == item->type()) {
        item->m_parent = this;
        m_children.insert(row, item);
        return true;
    }
    return false;
}

bool MusicItem::addChild(MusicItem *item)
{
    if (m_childType == NoItemType)
        return false;

    if (m_childType == item->type()) {
        item->m_parent = this;
        m_children << item;
        return true;
    }
    return false;
}

QVariant MusicItem::data(int role) const
{
    return m_data.value(role, QVariant());
}

bool MusicItem::setData(const QVariant &value, int role)
{
    if (itemSupportsWritingOfData(role)) {
        writeData(value, role);
        return true;
    }
    return false;
}

void MusicItem::beforeWritingData(QVariant &value, int role)
{
    Q_UNUSED(value)
    Q_UNUSED(role);
}

void MusicItem::afterWritingData(int role)
{
    Q_UNUSED(role);
}

void MusicItem::writeData(const QVariant &value, int role)
{
    QVariant insertValue(value);
    beforeWritingData(insertValue, role);
    m_data.insert(role, insertValue);
    afterWritingData(role);
}
