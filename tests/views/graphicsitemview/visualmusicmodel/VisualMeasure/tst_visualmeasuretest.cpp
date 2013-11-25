/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <views/graphicsitemview/visualmusicmodel/visualmeasure.h>

class VisualMeasureTest : public QObject
{
    Q_OBJECT

public:
    VisualMeasureTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testType();
    void testGraphicalType();

private:
    VisualMeasure *m_visualMeasure;
};

VisualMeasureTest::VisualMeasureTest()
    : m_visualMeasure(0)
{
}

void VisualMeasureTest::init()
{
    m_visualMeasure = new VisualMeasure();
}

void VisualMeasureTest::cleanup()
{
    delete m_visualMeasure;
}

void VisualMeasureTest::testType()
{
    QVERIFY2(m_visualMeasure->itemType() == VisualItem::VisualMeasureItem,
             "Visual measure returned wrong type");
}

void VisualMeasureTest::testGraphicalType()
{
    QVERIFY2(m_visualMeasure->graphicalType() == VisualItem::GraphicalInlineType,
             "Returned wrong graphical type");
}

QTEST_APPLESS_MAIN(VisualMeasureTest)

#include "tst_visualmeasuretest.moc"
