/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class Score
  * A Score represents a container for one or more @ref Tune "Tunes" and has at least a title.
  */

#include "score.h"

void Score::setTitle(const QString &title)
{
    setData(title, LP::scoreTitle);
}

QVariant Score::data(int role) const
{
    if (isRoleAccepted(role)) {
        role = mergeDoubleRoles(role);
        return m_data.value(role);
    }
    return QVariant();
}

void Score::setData(const QVariant &value, int role)
{
    if (isRoleAccepted(role)) {
        role = mergeDoubleRoles(role);
        m_data.insert(role, value);
    }
}

int Score::mergeDoubleRoles(int role) const
{
    if (role == Qt::DisplayRole)
        role = LP::scoreTitle;
    return role;
}

bool Score::isRoleAccepted(int role) const
{
    switch (role) {
    case Qt::DisplayRole:
    case LP::scoreTitle:
    case LP::scoreArranger:
    case LP::scoreComposer:
    case LP::scoreCopyright:
    case LP::scoreTimeSignature:
    case LP::scoreYear:
        return true;
    }
    return false;
}
