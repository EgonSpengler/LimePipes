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
    void testSymbolType();
};

MelodyNoteTest::MelodyNoteTest()
{
}

void MelodyNoteTest::testSymbolType()
{
    MelodyNote note;
    QVERIFY2(note.symbolType() == LP::MelodyNote, "Failed getting Symbol type from bar");
}

QTEST_APPLESS_MAIN(MelodyNoteTest)

#include "tst_melodynotetest.moc"
