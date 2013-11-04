/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "tst_ghb_melodynotetest.h"

void GHB_MelodyNoteTest::init()
{
    m_melody = new GHB_MelodyNote(PitchPtr(new Pitch(0, "Low A")), Length::_4);
}

void GHB_MelodyNoteTest::cleanup()
{
    delete m_melody;
}

void GHB_MelodyNoteTest::testDefaultConstructor()
{
    QVERIFY2(m_melody->data(LP::SymbolType) == GHB::MelodyNote, "Melody Note has wrong type");
    QVERIFY2(m_melody->data(LP::SymbolName) == "Melody Note", "Melody note has wrong name");
    QVERIFY2(m_melody->data(LP::SymbolPitch).value<PitchPtr>()->name() == "Low A", "Failed setting pitch in constructor");
    QVERIFY2(m_melody->data(LP::SymbolLength).value<Length::Value>() == Length::_4, "Failed setting length in constructor");
}

QTEST_MAIN(GHB_MelodyNoteTest)

#include "tst_ghb_melodynotetest.moc"
