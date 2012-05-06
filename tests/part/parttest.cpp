/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "parttest.h"
#include "model/part.h"

void PartTest::testType()
{
    Part part;
    QVERIFY2( part.type() == Model::PartType, "Part returns the wrong type" );
}
