/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musicmodeltest.h"
#include "qt_modeltest/modeltest.h"
#include "model/musicmodel.h"

void MusicModelTest::testQAbstractItemModelImplementation()
{
    MusicModel *musicModel = new MusicModel(this);
    new ModelTest(musicModel, this);
}
