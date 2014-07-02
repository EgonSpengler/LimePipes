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
#include <QJsonArray>
#include "musicitem.h"

static const QString childItemsKey("child items");

MusicItem::MusicItem(Type type, Type childType, MusicItem *parent)
    : m_type(type), m_childType(childType), m_parent(parent),
      m_itemBehavior(0)
{
    if (m_parent)
        m_parent->addChild(this);
    else
        m_parent = 0;
}

MusicItem::~MusicItem()
{
    qDeleteAll(m_children);
    delete m_itemBehavior;
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
    if (!item) {
        qWarning() << "Can't add 0 child music item";
        return false;
    }

    if (m_childType == NoItemType)
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

QVariant MusicItem::data(int role) const
{
    if (!m_itemBehavior)
        return QVariant();

    return m_itemBehavior->data(role);
}

bool MusicItem::setData(const QVariant &value, int role)
{
    if (!m_itemBehavior)
        return false;

    if (itemSupportsWritingOfData(role) ||
            m_itemBehavior->supportsData(role)) {
        writeData(value, role);
        return true;
    }
    return false;
}

QJsonObject MusicItem::toJson() const
{
    if (!m_itemBehavior)
        return QJsonObject();

    QJsonObject json(m_itemBehavior->toJson());
    QJsonArray childArray;
    foreach (const MusicItem *childItem, m_children) {
        QJsonObject childObject(childItem->toJson());
        if (childObject.isEmpty())
            continue;
        childArray.append(childObject);
    }

    if (childArray.count()) {
        json.insert(childItemsKey, childArray);
    }

    return json;
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
    if (!m_itemBehavior)
        return;

    QVariant insertValue(value);
    beforeWritingData(insertValue, role);
    m_itemBehavior->setData(value, role);
    afterWritingData(role);
}

ItemBehavior *MusicItem::itemBehavior() const
{
    return m_itemBehavior;
}

void MusicItem::setItemBehavior(ItemBehavior *itemBehavior)
{
    m_itemBehavior = itemBehavior;
}

