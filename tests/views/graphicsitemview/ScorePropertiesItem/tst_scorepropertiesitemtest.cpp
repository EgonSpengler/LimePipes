#include <QString>
#include <QtTest/QtTest>

class ScorePropertiesItemTest : public QObject
{
    Q_OBJECT

public:
    ScorePropertiesItemTest();

private Q_SLOTS:
    void testCase1();
};

ScorePropertiesItemTest::ScorePropertiesItemTest()
{
}

void ScorePropertiesItemTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(ScorePropertiesItemTest)

#include "tst_scorepropertiesitemtest.moc"
