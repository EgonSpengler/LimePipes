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
  * @fn void MusicItem::initData(const QVariant &value, int role)
  * @brief Subclasses can initialize read only data with this method.
  */

#include <QDebug>

#include "musicitem.h"

using namespace LP;

MusicItem::MusicItem(LP::ItemType type, LP::ItemType childType, MusicItem *parent)
    : m_type(type), m_childType(childType), m_parent(parent)
{
    if (m_parent)
        m_parent->addChild(this);
    else
        m_parent = 0;
}

MusicItem::~MusicItem()
{
    qDeleteAll(m_children);
}

void MusicItem::setParent(MusicItem *parent)
{
    Q_ASSERT(parent);

    if (m_parent != 0) {
        int rowOfThisItemInParent = m_parent->rowOfChild(this);
        Q_ASSERT(rowOfThisItemInParent != -1);
        MusicItem *thisItem = m_parent->takeChild(rowOfThisItemInParent);
        Q_ASSERT(thisItem == this);
        Q_ASSERT(m_parent == 0);
        Q_UNUSED(thisItem)
    }

    m_parent = parent;
}

bool MusicItem::insertChild(int row, MusicItem *item)
{
    if (m_childType == ItemType::NoItemType)
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
    if (!item) {
        qWarning() << "Can't add 0 child music item";
        return false;
    }

    if (m_childType == ItemType::NoItemType)
        return false;

    if (m_childType == item->type()) {
        item->m_parent = this;
        m_children << item;
        return true;
    }
    return false;
}

MusicItem *MusicItem::takeChild(int row)
{
    MusicItem *item = m_children.takeAt(row);
    Q_ASSERT(item);
    item->m_parent = 0;
    return item;
}

void MusicItem::visitChildren(AstVisitorInterface *visitor)
{
    foreach (MusicItem *childItem, m_children) {
        childItem->accept(visitor);
    }
}
