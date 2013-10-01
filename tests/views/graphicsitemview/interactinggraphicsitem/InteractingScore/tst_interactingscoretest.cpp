/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <graphicsitemview/interactinggraphicsitems/interactingscore.h>

class InteractingScoreTest : public QObject
{
    Q_OBJECT

public:
    InteractingScoreTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testCase1();

private:
    InteractingScore *m_interactingScore;
};

InteractingScoreTest::InteractingScoreTest()
{
}

void InteractingScoreTest::init()
{
    m_interactingScore = new InteractingScore(this);
}

void InteractingScoreTest::cleanup()
{
    delete m_interactingScore;
}

void InteractingScoreTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(InteractingScoreTest)

#include "tst_interactingscoretest.moc"
