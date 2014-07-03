/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */
#include <QDebug>

#include <common/itemdataroles.h>

#include "datakeys.h"
#include "itembehavior.h"

ItemBehavior::ItemBehavior(LP::ItemType type)
    : m_type(type)
{
}

QVariant ItemBehavior::data(int role) const
{
    return m_data.value(role);
}

void ItemBehavior::setData(const QVariant &value, int role)
{
    if (!value.isValid()) {
        m_data.remove(role);
        return;
    }

    m_data.insert(role, value);
}

QJsonObject ItemBehavior::toJson() const
{
    QJsonObject json;
    json.insert(DataKey::ItemType, static_cast<int>(type()));

    return json;
}

void ItemBehavior::fromJson(const QJsonObject &json)
{
}

QList<int> ItemBehavior::supportedData() const
{
    return m_supportedData;
}

void ItemBehavior::setSupportedData(const QList<int> &supportedData)
{
    m_supportedData = supportedData;
}

bool ItemBehavior::supportsData(int data) const
{
    return m_supportedData.contains(data);
}

LP::ItemType ItemBehavior::type() const
{
    return m_type;
}

void ItemBehavior::setType(const LP::ItemType &type)
{
    m_type = type;
}
