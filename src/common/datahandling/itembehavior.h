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
#include <QVariant>
#include <QJsonObject>

class ItemBehavior
{
public:
    ItemBehavior();
    virtual ~ItemBehavior() {}

    QVariant data(int role = Qt::UserRole) const;
    void setData(const QVariant &value, int role);

    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject &json);

private:
    QHash<int, QVariant> m_data;
};

#endif // ITEMBEHAVIOR_H
