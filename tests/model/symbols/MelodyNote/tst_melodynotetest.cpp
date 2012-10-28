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
    MelodyNoteTest()
        : m_melody(0) {}

private Q_SLOTS:
    void init();
    void cleanup();
    void testDefaultConstructor();
    void testTypeAndNameConstructor();
    void testDots();

private:
    MelodyNote *m_melody;
};

void MelodyNoteTest::init()
{
    m_melody = new MelodyNote();
}

void MelodyNoteTest::cleanup()
{
    delete m_melody;
}

void MelodyNoteTest::testDefaultConstructor()
{
    QVERIFY2(m_melody->symbolType() == LP::MelodyNote, "Melody Note doesn't return right symbol type in default constructor");
    QVERIFY2(m_melody->data(LP::symbolName) == "Melody Note", "MelodyNote doesn't return symbol name data in default constructor");
    QVERIFY2(m_melody->hasPitch(), "Melody note has no pitch");
    QVERIFY2(m_melody->hasLength(), "Melody note has no length");
    QVERIFY2(m_melody->hasGraphic(), "Melody note has no graphic");
    QVERIFY2(m_melody->data(LP::melodyNoteDots).isValid(), "No default value for dots");
}

void MelodyNoteTest::testTypeAndNameConstructor()
{
    delete m_melody;
    m_melody = new MelodyNote(LP::Bar, "testtest");

    QVERIFY2(m_melody->symbolType() == LP::Bar, "Melody Note doesn't return right symbol type if set through constructor");
    QVERIFY2(m_melody->data(LP::symbolName) == "testtest", "MelodyNote doesn't return symbol name data if set through constructor");
    QVERIFY2(m_melody->hasPitch(), "Melody note has no pitch");
    QVERIFY2(m_melody->hasLength(), "Melody note has no length");
    QVERIFY2(m_melody->hasGraphic(), "Melody note has no graphic");
}

void MelodyNoteTest::testDots()
{
    QVERIFY2(m_melody->itemSupportsWritingOfData(LP::melodyNoteDots), "Melody note doesn't support writing of Dots data");

    m_melody->setData(1, LP::melodyNoteDots);
    QVERIFY2(m_melody->data(LP::melodyNoteDots) == 1, "Failed setting dots");

    m_melody->setData(MelodyNote::MaxDots, LP::melodyNoteDots);
    QVERIFY2(m_melody->data(LP::melodyNoteDots) == MelodyNote::MaxDots, "Failed setting maximum dots");

    m_melody->setData(-1, LP::melodyNoteDots);
    QVERIFY2(m_melody->data(LP::melodyNoteDots) == 0, "Setting less than zero dots should result in zero dots");

    m_melody->setData(MelodyNote::MaxDots + 1, LP::melodyNoteDots);
    QVERIFY2(m_melody->data(LP::melodyNoteDots) == MelodyNote::MaxDots, "Setting more than maximum of dots doesn't result in maximum");
}

QTEST_MAIN(MelodyNoteTest)

#include "tst_melodynotetest.moc"
