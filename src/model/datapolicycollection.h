/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef DATAPOLICYCOLLECTION_H
#define DATAPOLICYCOLLECTION_H

#include <QMap>
#include <datapolicy.h>

class DataPolicyCollection
{
public:
    explicit DataPolicyCollection();
    void setPolicy(int dataRole, const DataPolicy& policy);
    const DataPolicy policyForRole(int dataRole) const;

private:
    QMap<int, DataPolicy> m_policies;
};

#endif // DATAPOLICYCOLLECTION_H
