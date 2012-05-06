/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "sheetmusictest.h"
#include "model/sheetmusic.h"

void SheetMusicTest::testType()
{
    SheetMusic sheet;
    QVERIFY2( sheet.type() == Model::SheetMusicType, "SheetMusic returns the wrong type");
}
