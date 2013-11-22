/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>

class GraphicsTextItemTest : public QObject
{
    Q_OBJECT

public:
    GraphicsTextItemTest();

private Q_SLOTS:
    void testCase1();
};

GraphicsTextItemTest::GraphicsTextItemTest()
{
}

void GraphicsTextItemTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(GraphicsTextItemTest)

#include "tst_graphicstextitemtest.moc"
