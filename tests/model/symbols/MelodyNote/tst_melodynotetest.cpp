/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <melodynote.h>

class MelodyNoteTest : public QObject
{
    Q_OBJECT
    
public:
    MelodyNoteTest();
    
private Q_SLOTS:
    void testCase1();
};

MelodyNoteTest::MelodyNoteTest()
{
}

void MelodyNoteTest::testCase1()
{
    MelodyNote note;
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(MelodyNoteTest)

#include "tst_melodynotetest.moc"
