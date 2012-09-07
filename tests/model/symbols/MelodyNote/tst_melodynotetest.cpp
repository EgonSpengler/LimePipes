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
    void init();
    void cleanup();
    void testDefaultConstructor();
    void testTypeAndNameConstructor();

private:
    MelodyNote *m_melody;
};

MelodyNoteTest::MelodyNoteTest()
{
}

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
}

void MelodyNoteTest::testTypeAndNameConstructor()
{
    delete m_melody;
    m_melody = new MelodyNote(LP::Bar, "testtest");

    QVERIFY2(m_melody->symbolType() == LP::Bar, "Melody Note doesn't return right symbol type if set through constructor");
    QVERIFY2(m_melody->data(LP::symbolName) == "testtest", "MelodyNote doesn't return symbol name data if set through constructor");
}
QTEST_APPLESS_MAIN(MelodyNoteTest)

#include "tst_melodynotetest.moc"
