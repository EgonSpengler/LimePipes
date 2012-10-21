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
#include <QObject>

class TestMusicItem :   public QObject,
                        public MusicItem
{
    Q_OBJECT
public:
    static const char *dataForInitDataRole;

    enum testDataRoles {
        initDataRole = 10000,
        notWritableRole
    };

    explicit TestMusicItem();

    bool itemSupportsWritingOfData(int role) const
    {
        if (role == notWritableRole)
            return false;
        return true;
    }

    void afterWritingData(int role) { Q_UNUSED(role) emit afterWritingDataCalled(); }

    void testInitData(){
        initData(123, 123);
    }

signals:
    void afterWritingDataCalled();
};

#endif // TESTMUSICITEM_H
