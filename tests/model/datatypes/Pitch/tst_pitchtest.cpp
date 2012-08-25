/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <pitch.h>

class PitchTest : public QObject
{
    Q_OBJECT
    
public:
    PitchTest();
    
private Q_SLOTS:
    void testCreatePitch();
};

PitchTest::PitchTest()
{
}

void PitchTest::testCreatePitch()
{
    Pitch();
}

QTEST_APPLESS_MAIN(PitchTest)

#include "tst_pitchtest.moc"
