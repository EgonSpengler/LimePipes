/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCOREBEHAVIOR_H
#define SCOREBEHAVIOR_H

#include <QJsonObject>

#include "itembehavior.h"

class ScoreBehavior : public ItemBehavior
{
public:
    ScoreBehavior();

    // ItemBehavior interface
public:
    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

private:
    void insertScoreData(QJsonObject &json, int dataRole, const QString &key) const;
};

#endif // SCOREBEHAVIOR_H
