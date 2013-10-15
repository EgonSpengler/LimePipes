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
#include <graphicsitemview/interactinggraphicsitems/graphicalscoreitem.h>

class InteractingScoreTest : public QObject
{
    Q_OBJECT

public:
    InteractingScoreTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testInteractingItemSet();
    void testSetTitle();

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

void InteractingScoreTest::testInteractingItemSet()
{
    QVERIFY2(m_interactingScore->m_headerItem->interactingItem() == m_interactingScore,
             "Interacting Item of header item wasn't set");
    QVERIFY2(m_interactingScore->m_footerItem->interactingItem() == m_interactingScore,
             "Interacting Item of footer item wasn't set");
}

void InteractingScoreTest::testSetTitle()
{
    QString newTitle("new title");
    m_interactingScore->setTitle(newTitle);

    QVERIFY2(m_interactingScore->title() == newTitle, "setTitle of ScorePropertiesItem wasn't called");
    QVERIFY2(m_interactingScore->m_headerItem->title() == newTitle, "Title of header item wasn't set");
    QVERIFY2(m_interactingScore->m_footerItem->title() == newTitle, "Title of footer item wasn't set");
}

QTEST_MAIN(InteractingScoreTest)

#include "tst_interactingscoretest.moc"
