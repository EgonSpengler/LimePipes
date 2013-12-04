/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <graphicsitemview/visualmusicmodel/iteminteractions/scoreinteraction.h>
#include <graphicsitemview/visualmusicmodel/interactinggraphicsitems/scoregraphicsitem.h>

class ScoreInteractionTest : public QObject
{
    Q_OBJECT
public:
    ScoreInteractionTest();

private Q_SLOTS:
    void init();
    void cleanup();

private:
    ScoreInteraction *m_scoreInteraction;
};

ScoreInteractionTest::ScoreInteractionTest()
{
}

void ScoreInteractionTest::init()
{
    m_scoreInteraction = new ScoreInteraction(this);
}

void ScoreInteractionTest::cleanup()
{
    delete m_scoreInteraction;
}

QTEST_MAIN(ScoreInteractionTest)

#include "tst_scoreinteractiontest.moc"
