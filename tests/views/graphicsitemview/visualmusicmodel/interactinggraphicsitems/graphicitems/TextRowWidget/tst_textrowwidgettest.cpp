/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>

class TextRowWidgetTest : public QObject
{
    Q_OBJECT

public:
    TextRowWidgetTest();

private Q_SLOTS:
    void testCase1();
};

TextRowWidgetTest::TextRowWidgetTest()
{
}

void TextRowWidgetTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(TextRowWidgetTest)

#include "tst_textrowwidgettest.moc"
