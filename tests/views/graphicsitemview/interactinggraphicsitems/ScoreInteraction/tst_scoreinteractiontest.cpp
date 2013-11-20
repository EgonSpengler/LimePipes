/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <graphicsitemview/interactinggraphicsitems/scoreinteraction.h>
#include <graphicsitemview/interactinggraphicsitems/scoregraphicsitem.h>

class ScoreInteractionTest : public QObject
{
    Q_OBJECT

public:
    ScoreInteractionTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testInteractingItemSet();
    void testSetTitle();

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

void ScoreInteractionTest::testInteractingItemSet()
{
    QVERIFY2(m_scoreInteraction->m_headerItem->itemInteraction() == m_scoreInteraction,
             "Interacting Item of header item wasn't set");
    QVERIFY2(m_scoreInteraction->m_footerItem->itemInteraction() == m_scoreInteraction,
             "Interacting Item of footer item wasn't set");
}

void ScoreInteractionTest::testSetTitle()
{
    QString title("title 1");
    QString newHeaderTitle("title set by header item");
    QString newFooterTitle("title set by footer");
    QString newPropertiesTitle("title set by properties item");

    if (!m_scoreInteraction->m_headerItem->hasItemPositionForDataRole(LP::ScoreTitle)) {
        m_scoreInteraction->m_headerItem->setItemPosition(LP::ScoreTitle, 0, TextRowWidget::Center);
    }
    if (!m_scoreInteraction->m_footerItem->hasItemPositionForDataRole(LP::ScoreTitle)) {
        m_scoreInteraction->m_footerItem->setItemPosition(LP::ScoreTitle, 0, TextRowWidget::Center);
    }
    m_scoreInteraction->setTitle(title);
    QVERIFY2(m_scoreInteraction->m_headerItem->itemText(LP::ScoreTitle) == title,
             "Title of header item wasn't set after interacting score setTitle");
    QVERIFY2(m_scoreInteraction->m_footerItem->itemText(LP::ScoreTitle) == title,
             "Title of footer item wasn't set after interacting score setTitle");
}

QTEST_MAIN(ScoreInteractionTest)

#include "tst_scoreinteractiontest.moc"
