/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <QCoreApplication>

class VisualRootItemTest : public QObject
{
    Q_OBJECT

public:
    VisualRootItemTest();

private Q_SLOTS:
    void testCase1();
};

VisualRootItemTest::VisualRootItemTest()
{
}

void VisualRootItemTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(VisualRootItemTest)

#include "tst_visualrootitemtest.moc"
