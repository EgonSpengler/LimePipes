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
    void testSetPitchAsQVariant();
};

PitchTest::PitchTest()
{
}

void PitchTest::testCreatePitch()
{
    Pitch();
}

void PitchTest::testSetPitchAsQVariant()
{
    QVariant var = QVariant::fromValue<Pitch>(Pitch());
    QVERIFY2(var.isValid(), "Failed setting Pitch as QVariant");
}

QTEST_APPLESS_MAIN(PitchTest)

#include "tst_pitchtest.moc"
