/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>

class TextPropertyEditWidgetTest : public QObject
{
    Q_OBJECT

public:
    TextPropertyEditWidgetTest();

private Q_SLOTS:
    void testCase1();
};

TextPropertyEditWidgetTest::TextPropertyEditWidgetTest()
{
}

void TextPropertyEditWidgetTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TextPropertyEditWidgetTest)

#include "tst_textpropertyeditwidgettest.moc"
