/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "tst_symbolgraphictest.h"

SymbolGraphicTest::SymbolGraphicTest()
{
}

void SymbolGraphicTest::testDefaultConstructor()
{
    SymbolGraphic graphic;
    QVERIFY2(graphic.yOffset() == 0, "wrong default offset");
    QVERIFY2(graphic.pixmap().isNull() == true, "wrong default pixmap");
}

void SymbolGraphicTest::testConstructor()
{
    QPixmap pixmap(20, 10);
    SymbolGraphic graphic(2.0, pixmap);
    QVERIFY2(graphic.yOffset() == 2.0, "Failed setting yOffset");
    QVERIFY2(graphic.pixmap().width() == 20, "Failed setting pixmap");
}

void SymbolGraphicTest::testQVariant()
{
    SymbolGraphicPtr symbolGraphic;
    QVariant graphicVariant = QVariant::fromValue<SymbolGraphicPtr>(symbolGraphic);
    Q_UNUSED(graphicVariant)
}

QTEST_MAIN(SymbolGraphicTest)

#include "tst_symbolgraphictest.moc"
