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

QTEST_MAIN(SymbolGraphicBuilderTest)

#include "tst_symbolgraphicbuildertest.moc"
