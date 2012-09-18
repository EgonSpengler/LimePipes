/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "datapolicycollection.h"

DataPolicyCollection::DataPolicyCollection()
{
}

void DataPolicyCollection::setPolicy(int dataRole, const DataPolicy &policy)
{
    m_policies.insert(dataRole, policy);
}

const DataPolicy DataPolicyCollection::policyForRole(int dataRole) const
{
    return m_policies.value(dataRole, DataPolicy());
}
