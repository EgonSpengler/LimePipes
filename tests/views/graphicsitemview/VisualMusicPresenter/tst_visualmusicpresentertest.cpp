/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>

class VisualMusicPresenterTest : public QObject
{
    Q_OBJECT

public:
    VisualMusicPresenterTest();

private Q_SLOTS:
    void testCase1();
};

VisualMusicPresenterTest::VisualMusicPresenterTest()
{
}

void VisualMusicPresenterTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(VisualMusicPresenterTest)

#include "tst_visualmusicpresentertest.moc"
