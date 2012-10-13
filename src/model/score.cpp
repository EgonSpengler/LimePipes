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

const QScopedPointer<DataPolicyCollection> Score::m_policies(initPolicies());

void Score::setTitle(const QString &title)
{
    setData(title, LP::scoreTitle);
}

bool Score::itemSupportsWritingOfData(int role) const
{
    switch (role) {
    case LP::scoreArranger:
    case LP::scoreComposer:
    case LP::scoreCopyright:
    case LP::scoreTimeSignature:
    case LP::scoreTitle:
    case LP::scoreYear:
        return true;
    default:
        return false;
    }
}

DataPolicyCollection *Score::initPolicies()
{
    DataPolicyCollection *collection = new DataPolicyCollection();
    collection->setPolicy(Qt::DisplayRole, DataPolicy(DataPolicy::ReadWrite, LP::scoreTitle));
    collection->setPolicy(LP::scoreTitle, DataPolicy(DataPolicy::ReadWrite));
    collection->setPolicy(LP::scoreArranger, DataPolicy(DataPolicy::ReadWrite));
    collection->setPolicy(LP::scoreComposer, DataPolicy(DataPolicy::ReadWrite));
    collection->setPolicy(LP::scoreCopyright, DataPolicy(DataPolicy::ReadWrite));
    collection->setPolicy(LP::scoreTimeSignature, DataPolicy(DataPolicy::ReadWrite));
    collection->setPolicy(LP::scoreYear, DataPolicy(DataPolicy::ReadWrite));
    return collection;
}
