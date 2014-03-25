/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <common/itemdataroles.h>
#include "tst_symbolgraphicbuildertest.h"

void SymbolGraphicBuilderTest::init()
{
    m_builder = new TestSymbolGraphicBuilder();
}

void SymbolGraphicBuilderTest::cleanup()
{
    m_builder->deleteLater();
}

void SymbolGraphicBuilderTest::testConstructor()
{
    SymbolGraphicPtr symbolGraphic = m_builder->symbolGraphic();
    QVERIFY2(symbolGraphic->pixmap().isNull() == true, "SymbolGraphics pixmap was initially set");
    QVERIFY2(!m_builder->s_musicFont.isNull(), "Music font wasn't set");
    QVERIFY2(m_builder->s_musicFont->staffLineHeight() > 0, "No initial staff line height was set");
}

void SymbolGraphicBuilderTest::testSetGetData()
{
    QVector<int> graphicDataRoles;
    graphicDataRoles.append(LP::SymbolType);
    m_builder->setGraphicDataRoles(graphicDataRoles);
    QVERIFY2(m_builder->graphicDataRoles() == graphicDataRoles,
             "Graphic data roles where not set in TestGraphicBuilder");

    int testData = 12;
    m_builder->setData(testData, LP::SymbolType);
    int builderData = m_builder->data(LP::SymbolType).toInt();
    QVERIFY2(builderData == testData, "Failed setting/getting data that has a graphic data role");

    m_builder->setData(33, LP::SymbolPitch);
    QVERIFY2(!m_builder->data(LP::SymbolPitch).isValid(), "A non graphic data role was set in builder");
}

void SymbolGraphicBuilderTest::testSetGetStaffLineHeight()
{
    int testLineHeight = 89;
    m_builder->setStaffLineHeight(testLineHeight);
    QVERIFY2(m_builder->staffLineHeight() == testLineHeight,
             "Failed setting/getting staff line height");
    QVERIFY2(m_builder->s_musicFont->staffLineHeight() == testLineHeight,
             "Staff line height of music font wasn't set");
}

void SymbolGraphicBuilderTest::testUpdateSymbolGrapicCall()
{
    int testData = 8934;
    int testDataRole = LP::SymbolCategory;

    QVector<int> graphicDataRoles{ testDataRole };
    m_builder->setGraphicDataRoles(graphicDataRoles);
    QSignalSpy spy(m_builder, SIGNAL(updateSymbolGraphicCalled()));
    m_builder->setData(testData, testDataRole);
    QVERIFY2(spy.count() == 1, "updateSymbolGraphic was not called on the builder");
}

void SymbolGraphicBuilderTest::testUpdateSymbolGraphicCallOnNonDependentBuilder()
{
    QSignalSpy spy(m_builder, SIGNAL(updateSymbolGraphicCalled()));
    m_builder->setData(123, LP::SymbolCategory);
    QVERIFY2(spy.count() == 0, "updateSymbolGraphic was called despite the builder depends on "
             "no data role");
}

void SymbolGraphicBuilderTest::testSetGetPixmap()
{
    m_builder->setSymbolGraphicPixmap(QPixmap(30, 10));
    SymbolGraphicPtr symbolGraphic = m_builder->symbolGraphic();
    QVERIFY2(symbolGraphic->pixmap().width() == 30, "Failed setting pixmap");
}

void SymbolGraphicBuilderTest::testSetYOffset()
{
    m_builder->setSymbolGraphicYOffset(23.56);
    SymbolGraphicPtr symbolGraphic = m_builder->symbolGraphic();
    QVERIFY2(symbolGraphic->yOffset() == 23.56, "Failed setting y offset");
}

QTEST_MAIN(SymbolGraphicBuilderTest)

#include "tst_symbolgraphicbuildertest.moc"
