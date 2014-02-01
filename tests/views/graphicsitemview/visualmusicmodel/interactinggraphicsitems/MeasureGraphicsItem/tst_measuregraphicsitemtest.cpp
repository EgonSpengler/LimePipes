/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <QCoreApplication>

class MeasureGraphicsItemTest : public QObject
{
    Q_OBJECT

public:
    MeasureGraphicsItemTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

MeasureGraphicsItemTest::MeasureGraphicsItemTest()
{
}

void MeasureGraphicsItemTest::initTestCase()
{
}

void MeasureGraphicsItemTest::cleanupTestCase()
{
}

void MeasureGraphicsItemTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(MeasureGraphicsItemTest)

#include "tst_measuregraphicsitemtest.moc"
