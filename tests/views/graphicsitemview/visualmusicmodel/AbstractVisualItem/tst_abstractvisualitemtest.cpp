/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include "testabstractvisualitem.h"
#include <QtTest/QtTest>

class AbstractVisualItemTest : public QObject
{
    Q_OBJECT
    
public:
    AbstractVisualItemTest();
    
private Q_SLOTS: void testCase1();
};

AbstractVisualItemTest::AbstractVisualItemTest()
{
}

void AbstractVisualItemTest::testCase1()
{
    TestAbstractVisualItem item;
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(AbstractVisualItemTest)

#include "tst_abstractvisualitemtest.moc"
