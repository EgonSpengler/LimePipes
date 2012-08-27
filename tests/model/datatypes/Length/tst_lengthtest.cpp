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
    void testCreateLength();
    void testSetLength();
    void testSetLengthAsVariant();
};

LengthTest::LengthTest()
{
}

void LengthTest::testCreateLength()
{
    Length length(Length::_32);
    QVERIFY2(length.length() == Length::_32, "Failed to set length through constructor");
}

void LengthTest::testSetLength()
{
    Length length(Length::_16);
    length.setLength(Length::_32);
    QVERIFY2(length.length() == Length::_32, "Failed to set length");
}

void LengthTest::testSetLengthAsVariant()
{
    QVariant var;
    var.setValue(Length(Length::_4));
    QVERIFY2(var.value<Length>().length() == Length::_4, "Failed to set as QVariant");
}

QTEST_APPLESS_MAIN(LengthTest)

#include "tst_lengthtest.moc"
