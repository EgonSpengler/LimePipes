/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "tst_symbolgraphicbuildertest.h"

void SymbolGraphicBuilderTest::init()
{
    m_musicItem = new TestMusicItem();
    m_builder = new TestGraphicBuilder(m_musicItem);
}

void SymbolGraphicBuilderTest::cleanup()
{
    delete m_builder;
    delete m_musicItem;
}

void SymbolGraphicBuilderTest::testSymbolGraphic()
{
    SymbolGraphicPtr symbolGraphic = m_builder->symbolGraphic();
    QVERIFY2(symbolGraphic->pixmap().isNull() == true, "SymbolGraphics pixmap was initially set");
}

void SymbolGraphicBuilderTest::testItemData()
{
    QVariant initialData = m_builder->getItemData(TestMusicItem::initialDataRole);
    QVERIFY2(initialData.isValid(), "Failed getting item data in subclass");
}

void SymbolGraphicBuilderTest::testSetPixmap()
{
    m_builder->setGraphicPixmap(QPixmap(30, 10));
    SymbolGraphicPtr symbolGraphic = m_builder->symbolGraphic();
    QVERIFY2(symbolGraphic->pixmap().width() == 30, "Failed setting pixmap");
}

void SymbolGraphicBuilderTest::testSetYOffset()
{
    m_builder->setGraphicYOffset(23.56);
    SymbolGraphicPtr symbolGraphic = m_builder->symbolGraphic();
    QVERIFY2(symbolGraphic->yOffset() == 23.56, "Failed setting y offset");
}

QTEST_MAIN(SymbolGraphicBuilderTest)

#include "tst_symbolgraphicbuildertest.moc"
