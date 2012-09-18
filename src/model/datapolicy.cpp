/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "datapolicy.h"

bool DataPolicy::isReadable() const
{
    if (m_access == ReadWrite ||
        m_access == Read) {
        return true;
    }
    return false;
}

bool DataPolicy::isWritable() const
{
    if (m_access == ReadWrite ||
        m_access == Write) {
        return true;
    }
    return false;
}

bool DataPolicy::hasProxyRole() const
{
    if (m_proxyDataRole != -1) {
        return true;
    }
    return false;
}

int DataPolicy::proxyRole() const
{
    return m_proxyDataRole;
}
