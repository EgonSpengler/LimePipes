/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ITEMBEHAVIOR_H
#define ITEMBEHAVIOR_H

#include <QHash>
#include <QList>
#include <QVariant>
#include <QJsonObject>

#include "common/defines.h"

class ItemBehavior
{
public:
    ItemBehavior(LP::ItemType type);
    virtual ~ItemBehavior() {}

    QVariant data(int role = Qt::UserRole) const;
    void setData(const QVariant &value, int role);

    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject &json);

    QList<int> supportedData() const;
    void setSupportedData(const QList<int> &supportedData);
    bool supportsData(int data) const;

    LP::ItemType type() const;
    void setType(const LP::ItemType &type);

private:
    LP::ItemType m_type;
    QHash<int, QVariant> m_data;
    QList<int> m_supportedData;
};

#endif // ITEMBEHAVIOR_H
