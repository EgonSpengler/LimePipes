/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "testmusicitem.h"

const char *TestMusicItem::dataForReadDataReimplementation = "read data reimplementation";
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
    case readDataReimplementationRole:
        return DataPolicy(DataPolicy::ReadWrite);
    }
    return DataPolicy(DataPolicy::NoAccess);
}

QVariant TestMusicItem::readData(int role) const
{
    if (role == readDataReimplementationRole) {
        return QVariant(dataForReadDataReimplementation);
    }
    return MusicItem::readData(role);
}
