/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include "scorepropertiesholderdummy.h"
#include <graphicsitemview/scorepropertiesitem.h>
#include <graphicsitemview/abstractscorepropertiesholder.h>

class AbstractScorePropertiesHolderTest : public QObject
{
    Q_OBJECT

public:
    AbstractScorePropertiesHolderTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetScoreProperties();

private:
    AbstractScorePropertiesHolder *m_scorePropertiesHolder;
};

AbstractScorePropertiesHolderTest::AbstractScorePropertiesHolderTest()
{
}

void AbstractScorePropertiesHolderTest::init()
{
    m_scorePropertiesHolder = new ScorePropertiesHolderDummy();
}

void AbstractScorePropertiesHolderTest::cleanup()
{
    delete m_scorePropertiesHolder;
}

void AbstractScorePropertiesHolderTest::testSetGetScoreProperties()
{
    ScorePropertiesInterface *scoreProperties = new ScorePropertiesItem(this);
    m_scorePropertiesHolder->setScoreProperties(scoreProperties);
    QVERIFY2(scoreProperties == m_scorePropertiesHolder->scoreProperties(),
             "Can't get the same score properties back");

    QVERIFY2(true, "Failure");

    delete scoreProperties;
}

QTEST_APPLESS_MAIN(AbstractScorePropertiesHolderTest)

#include "tst_abstractscorepropertiesholdertest.moc"
