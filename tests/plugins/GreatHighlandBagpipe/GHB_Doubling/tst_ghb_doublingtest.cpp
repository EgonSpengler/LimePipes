/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "tst_ghb_doublingtest.h"

void GHB_DoublingTest::init()
{
    m_doubling = new GHB_Doubling;
}

void GHB_DoublingTest::cleanup()
{
    delete m_doubling;
}

void GHB_DoublingTest::testDefaultConstructor()
{
    QVERIFY2(m_doubling->symbolType() == GHB::Doubling, "Doubling has wrong type");
    QVERIFY2(m_doubling->data(LP::symbolName) == "Doubling", "Doubling has wrong name");
}

QTEST_APPLESS_MAIN(GHB_DoublingTest)

#include "tst_ghb_doublingtest.moc"
