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

class ItemBehavior
{
public:
    ItemBehavior();
    virtual ~ItemBehavior() {}

    QVariant data(int role = Qt::UserRole) const;
    void setData(const QVariant &value, int role);

    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject &json);

    QList<int> supportedData() const;
    void setSupportedData(const QList<int> &supportedData);
    bool supportsData(int data) const;

private:
    QHash<int, QVariant> m_data;
    QList<int> m_supportedData;
};

#endif // ITEMBEHAVIOR_H
