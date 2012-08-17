/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "tune.h"

class TuneTest : public QObject
{
    Q_OBJECT
    
public:
    TuneTest();
    
private Q_SLOTS:
    void testType();
};

TuneTest::TuneTest()
{
}

void TuneTest::testType()
{
    Tune tune;
    QVERIFY2( tune.type() == TuneType, "Tune returns the wrong type");
}

QTEST_APPLESS_MAIN(TuneTest)

#include "tst_tunetest.moc"
