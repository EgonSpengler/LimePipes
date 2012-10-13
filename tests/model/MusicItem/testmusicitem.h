/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTMUSICITEM_H
#define TESTMUSICITEM_H

#include <musicitem.h>

class TestMusicItem : public MusicItem
{
public:
    static const char *dataForInitDataRole;

    enum testDataRoles {
        initDataRole = 10000,
        defaultDataRole,
        defaultProxyDataRole,
        notWritableRole
    };

    explicit TestMusicItem();

    const DataPolicy dataPolicyForRole(int role) const;
    bool itemSupportsWritingOfData(int role) const
    {
        if (role == notWritableRole)
            return false;
        return true;
    }
};

#endif // TESTMUSICITEM_H
