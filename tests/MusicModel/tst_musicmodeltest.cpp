/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "qt_modeltest/modeltest.h"
#include <musicmodel.h>

class MusicModelTest : public QObject
{
    Q_OBJECT
    
public:
    MusicModelTest();
    
private Q_SLOTS:
    void testQAbstractItemModelImplementation();
};

MusicModelTest::MusicModelTest()
{
}

void MusicModelTest::testQAbstractItemModelImplementation()
{
    MusicModel *musicModel = new MusicModel(this);
    new ModelTest(musicModel, this);
}

QTEST_APPLESS_MAIN(MusicModelTest)

#include "tst_musicmodeltest.moc"
