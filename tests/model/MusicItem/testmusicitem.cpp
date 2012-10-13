/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "testmusicitem.h"

const char *TestMusicItem::dataForInitDataRole = "init data";

TestMusicItem::TestMusicItem()
    : MusicItem()
{
    initData(dataForInitDataRole, initDataRole);
}

const DataPolicy TestMusicItem::dataPolicyForRole(int role) const
{
    switch (role) {
    case initDataRole:
        return DataPolicy(DataPolicy::Read);
    case defaultDataRole:
        return DataPolicy(DataPolicy::ReadWrite, defaultProxyDataRole);
    }
    return DataPolicy(DataPolicy::NoAccess);
}
