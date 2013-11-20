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
    QVERIFY2(m_interactingScore->m_headerItem->itemInteraction() == m_interactingScore,
             "Interacting Item of header item wasn't set");
    QVERIFY2(m_interactingScore->m_footerItem->itemInteraction() == m_interactingScore,
             "Interacting Item of footer item wasn't set");
}

void InteractingScoreTest::testSetTitle()
{
    QString title("title 1");
    QString newHeaderTitle("title set by header item");
    QString newFooterTitle("title set by footer");
    QString newPropertiesTitle("title set by properties item");

    if (!m_interactingScore->m_headerItem->hasItemPositionForDataRole(LP::ScoreTitle)) {
        m_interactingScore->m_headerItem->setItemPosition(LP::ScoreTitle, 0, TextRowWidget::Center);
    }
    if (!m_interactingScore->m_footerItem->hasItemPositionForDataRole(LP::ScoreTitle)) {
        m_interactingScore->m_footerItem->setItemPosition(LP::ScoreTitle, 0, TextRowWidget::Center);
    }
    m_interactingScore->setTitle(title);
    QVERIFY2(m_interactingScore->scorePropertiesItem()->title() == title,
             "setTitle of ScorePropertiesItem wasn't called after interacting score setTitle");
    QVERIFY2(m_interactingScore->m_headerItem->itemText(LP::ScoreTitle) == title,
             "Title of header item wasn't set after interacting score setTitle");
    QVERIFY2(m_interactingScore->m_footerItem->itemText(LP::ScoreTitle) == title,
             "Title of footer item wasn't set after interacting score setTitle");

    m_interactingScore->scorePropertiesItem()->setTitle(newPropertiesTitle);
    QVERIFY2(m_interactingScore->scorePropertiesItem()->title() == newPropertiesTitle,
             "setTitle of ScorePropertiesItem wasn't called after score properties item setTitle");
    QVERIFY2(m_interactingScore->m_headerItem->itemText(LP::ScoreTitle) == newPropertiesTitle,
             "Title of header item wasn't set after score properties item setTitle");
    QVERIFY2(m_interactingScore->m_footerItem->itemText(LP::ScoreTitle) == newPropertiesTitle,
             "Title of footer item wasn't set after score properties item setTitle");
}

QTEST_MAIN(InteractingScoreTest)

#include "tst_interactingscoretest.moc"
