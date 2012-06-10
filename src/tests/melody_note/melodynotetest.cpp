#include <QTest>
#include "melodynotetest.h"
#include "model/melodynote.h"

void MelodyNoteTest::testType()
{
    MelodyNote melNote;
    QVERIFY2( melNote.type() == MelodyNoteType, "MelodyNote returns the wrong type");
}

void MelodyNoteTest::testDots()
{
    MelodyNote note;
    note.setDots(1);
    QVERIFY2( note.dots() == 1, "Dots can't be set");

    note.addDot();
    QVERIFY2( note.dots() == 2, "Dots can't be added");

    note.addDot();
    QVERIFY2( note.dots() == 0, "Dots aren't 0 when adding one dot to MelodyNote with 2 dots");

    note.setDots(5);
    QVERIFY2( note.dots() == 2, "Dots aren't 2 when setDots is called with number greater than 2");

    note.setDots(-3);
    QVERIFY2( note.dots() == 0, "Dots aren't 0 when setDots is called with number lesser than 0");
}
