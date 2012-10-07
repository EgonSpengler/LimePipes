/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QVariant>
#include <length.h>

class LengthTest : public QObject
{
    Q_OBJECT
    
public:
    LengthTest();
    
private Q_SLOTS:
    void testValues();
    void testValueForName();
    void testNameForValue();
    void testSetLengthAsVariant();
    void testLengthNames();
    void testLengthValues();
};

LengthTest::LengthTest()
{
}

void LengthTest::testValues()
{
    QVERIFY2(Length::_1 == 1, "Failed, note value _1");
    QVERIFY2(Length::_2 == 2, "Failed, note value _2");
    QVERIFY2(Length::_4 == 4, "Failed, note value _4");
    QVERIFY2(Length::_8 == 8, "Failed, note value _8");
    QVERIFY2(Length::_16 == 16, "Failed, note value _16");
    QVERIFY2(Length::_32 == 32, "Failed, note value _32");
    QVERIFY2(Length::_64 == 64, "Failed, note value _64");
}

void LengthTest::testValueForName()
{
    QVERIFY2(Length::valueForName("half") == Length::_2, "Failed getting value for name");
    // default value is whole note if no valid name is given
    QVERIFY2(Length::valueForName("uga-uga") == Length::_1, "Failed getting value for non existing name");
}

void LengthTest::testNameForValue()
{
    QVERIFY2(Length::nameForValue(Length::_16) == "sixteenth", "Failed getting name for value");
}

void LengthTest::testSetLengthAsVariant()
{
    QVariant var;
    var.setValue(Length::_4);
    QVERIFY2(var.value<Length::Value>() == Length::_4, "Failed to set as QVariant");
}

void LengthTest::testLengthNames()
{
    QStringList names = Length::lengthNames();
    QVERIFY2(names.count() == 7, "Failed getting length names");
    QVERIFY2(names.at(0) == "whole", "Failed whole note");
    QVERIFY2(names.at(1) == "half", "Failed half note");
    QVERIFY2(names.at(2) == "quarter", "Failed quarter note");
    QVERIFY2(names.at(3) == "eighth", "Failed eighth note");
    QVERIFY2(names.at(4) == "sixteenth", "Failed sixteenth note");
    QVERIFY2(names.at(5) == "thirty-second", "Failed thirty-second note");
    QVERIFY2(names.at(6) == "sixty-fourth", "Failed sixty-fourth note");
}

void LengthTest::testLengthValues()
{
    QVERIFY2(Length::lengthValues().count() == 7, "Failed getting all length values");
    QVERIFY2(Length::lengthValues().at(0) == Length::_1, "Failed whole note");
    QVERIFY2(Length::lengthValues().at(1) == Length::_2, "Failed half note");
    QVERIFY2(Length::lengthValues().at(2) == Length::_4, "Failed quarter note");
    QVERIFY2(Length::lengthValues().at(3) == Length::_8, "Failed eightn note");
    QVERIFY2(Length::lengthValues().at(4) == Length::_16, "Failed sixteenth note");
    QVERIFY2(Length::lengthValues().at(5) == Length::_32, "Failed thirty-second note");
    QVERIFY2(Length::lengthValues().at(6) == Length::_64, "Failed sixty-fourth note");
}

QTEST_APPLESS_MAIN(LengthTest)

#include "tst_lengthtest.moc"
