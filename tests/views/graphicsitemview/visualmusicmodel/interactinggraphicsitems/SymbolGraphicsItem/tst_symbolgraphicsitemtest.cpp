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

class SymbolGraphicsItemTest : public QObject
{
    Q_OBJECT

public:
    SymbolGraphicsItemTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

SymbolGraphicsItemTest::SymbolGraphicsItemTest()
{
}

void SymbolGraphicsItemTest::initTestCase()
{
}

void SymbolGraphicsItemTest::cleanupTestCase()
{
}

void SymbolGraphicsItemTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(SymbolGraphicsItemTest)

#include "tst_symbolgraphicsitemtest.moc"
