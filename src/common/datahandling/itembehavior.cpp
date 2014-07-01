/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */
#include <QDebug>

#include <common/itemdataroles.h>

#include "itembehavior.h"

ItemBehavior::ItemBehavior()
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
    return QJsonObject();
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

