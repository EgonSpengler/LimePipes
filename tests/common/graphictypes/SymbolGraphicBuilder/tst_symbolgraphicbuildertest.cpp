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

void SymbolGraphicBuilderTest::testIsGraphicValid()
{
    QVERIFY2(m_builder->isGraphicValid() == true,
             "A graphic builder which depends on no data roles should be valid");

    int role1 = LP::SymbolType;
    int role2 = LP::SymbolLength;
    QVector<int> graphicDataRoles{role1, role2};
    m_builder->setGraphicDataRoles(graphicDataRoles);
    QVERIFY2(m_builder->isGraphicValid() == false,
             "Graphic is valid despite no data was set");

    m_builder->setData(1234, role1);
    QVERIFY2(m_builder->isGraphicValid() == false,
             "Graphic is valid despite not all data was set");

    m_builder->setData(1234, role2);
    QVERIFY2(m_builder->isGraphicValid() == true,
             "Graphic is not valid despite all data was set");
}

void SymbolGraphicBuilderTest::testInitSymbolGraphicCall()
{
    int role1 = LP::SymbolType;
    int role2 = LP::SymbolLength;
    QVector<int> graphicDataRoles{role1, role2};
    m_builder->setGraphicDataRoles(graphicDataRoles);

    QSignalSpy initSpy(m_builder, SIGNAL(initSymbolGraphicCalled()));
    QSignalSpy updateSpy(m_builder, SIGNAL(updateSymbolGraphicCalled()));
    m_builder->setData(8483, role1);
    QVERIFY2(initSpy.count() == 0, "init was called too early on builder");
    QVERIFY2(updateSpy.count() == 0, "Update should be called after initialize");

    m_builder->setData(QVariant(), role2);
    QVERIFY2(initSpy.count() == 0, "init was called on builder despite invalid data was set");
    QVERIFY2(updateSpy.count() == 0, "Update should be called after initialize");

    m_builder->setData(86747, role2);
    QVERIFY2(initSpy.count()   == 1, "init wasn't called on builder after all data has been set with valid values");
    QVERIFY2(updateSpy.count() == 0, "Update should be called after initialize but not with initialize");

    m_builder->setData(573927, role2);
    QVERIFY2(updateSpy.count() == 1, "Update should be called after initialize was called");
}

void SymbolGraphicBuilderTest::testUpdateSymbolGraphicCallOnNonDependentBuilder()
{
    int testData = 8934;
    int testDataRole = LP::SymbolCategory;

    QVector<int> graphicDataRoles{ testDataRole };
    m_builder->setGraphicDataRoles(graphicDataRoles);
    QSignalSpy spy(m_builder, SIGNAL(updateSymbolGraphicCalled()));
    m_builder->setData(testData, testDataRole);

    // set data for update
    m_builder->setData(testData + 1, testDataRole);
    QVERIFY2(spy.count() == 1, "updateSymbolGraphic was not called on the builder");
}

void SymbolGraphicBuilderTest::testUpdateSymbolGraphicCall()
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
