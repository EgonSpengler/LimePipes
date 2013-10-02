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

void InteractingScoreTest::testSetTitle()
{
    QString newTitle("new title");
    m_interactingScore->setNewTitle(newTitle);

    QVERIFY2(m_interactingScore->headerItem()->title() == newTitle, "Title of header item wasn't set");
    QVERIFY2(m_interactingScore->footerItem()->title() == newTitle, "Title of footer item wasn't set");
}

QTEST_MAIN(InteractingScoreTest)

#include "tst_interactingscoretest.moc"
