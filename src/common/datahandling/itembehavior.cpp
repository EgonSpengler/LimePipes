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
    m_data.insert(role, value);
    if (role == LP::SymbolType) {
        qDebug() << "Now data has " << m_data.count();
    }
}

QJsonObject ItemBehavior::toJson() const
{
    return QJsonObject();
}

void ItemBehavior::fromJson(const QJsonObject &json)
{
}
