/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef DATAPOLICY_H
#define DATAPOLICY_H

#include <QMetaType>

class DataPolicy
{
public:
    enum accessType {
        NoAccess,
        ReadWrite,
        Read,
        Write
    };
    const static int NoProxyRole = -1;

    explicit DataPolicy()
        : m_access(NoAccess), m_proxyDataRole(NoProxyRole) {}
    explicit DataPolicy( accessType access, int proxyDataRole = NoProxyRole )
        : m_access(access), m_proxyDataRole(proxyDataRole) {}

    bool isReadable() const;
    bool isWritable() const;
    bool hasProxyRole() const;
    int proxyRole() const;

private:
    accessType m_access;
    int m_proxyDataRole;
};

Q_DECLARE_METATYPE(DataPolicy)

#endif // DATAPOLICY_H
