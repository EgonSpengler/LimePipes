/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SHEETMUSICTEST_H
#define SHEETMUSICTEST_H

#include <QObject>
#include "../autotest.h"

class SheetMusicTest : public QObject
{
    Q_OBJECT
private slots:
    void testType();

};

DECLARE_TEST( SheetMusicTest )

#endif // SHEETMUSICTEST_H
