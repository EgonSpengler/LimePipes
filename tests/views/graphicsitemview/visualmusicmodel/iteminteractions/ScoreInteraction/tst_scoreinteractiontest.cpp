/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <QGraphicsSceneContextMenuEvent>
#include <graphicsitemview/visualmusicmodel/iteminteractions/scoreinteraction.h>
#include <graphicsitemview/visualmusicmodel/interactinggraphicsitems/scoregraphicsitem.h>
#include <graphicsitemview/visualmusicmodel/iteminteractions/dialogs/scorepropertiesdialog.h>
#include <graphicsitemview/visualmusicmodel/iteminteractions/dialogs/textpropertyeditwidget.h>

class ScoreInteractionTest : public QObject
{
    Q_OBJECT
public:
    ScoreInteractionTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testContextMenuEvent();
    void testSetData();
    void testDataChangedSignalDirect();
    void testDataChangedSignalDialog();

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

void ScoreInteractionTest::testContextMenuEvent()
{
    QGraphicsSceneContextMenuEvent contextEvent;
    QVERIFY2(m_scoreInteraction->m_scorePropertiesDialog->isVisible() == false,
             "Failed, dialog should be hidden");
    m_scoreInteraction->contextMenuEvent(&contextEvent);
    QVERIFY2(m_scoreInteraction->m_scorePropertiesDialog->isVisible() == true,
             "Dialog is not visible after context menu event");
}

void ScoreInteractionTest::testSetData()
{
    LP::ScoreDataRole testDataRole = LP::ScoreArranger;
    QString testString("arranger");

    m_scoreInteraction->setData(testString, testDataRole);

    QVERIFY2(m_scoreInteraction->m_scorePropertiesDialog->propertyText(testDataRole) == testString,
             "Data wasn't set on dialog");
}

void ScoreInteractionTest::testDataChangedSignalDirect()
{
    QSignalSpy spy(m_scoreInteraction, SIGNAL(dataChanged(QVariant,int)));
    LP::ScoreDataRole dataRole = LP::ScoreArranger;
    QString testString("test string");

    // text changed
    m_scoreInteraction->propertyTextChanged(dataRole, testString);
    QVERIFY2(spy.count() == 1, "dataChanged signal wasn't emitted for text");
}

void ScoreInteractionTest::testDataChangedSignalDialog()
{
    QSignalSpy spy(m_scoreInteraction, SIGNAL(dataChanged(QVariant,int)));
    LP::ScoreDataRole dataRole = LP::ScoreArranger;
    QString testString("test string");

    ScorePropertiesDialog *dialog = m_scoreInteraction->m_scorePropertiesDialog;
    TextPropertyEditWidget *editWidget = dialog->lineEditForRole(dataRole);

    // Change text through dialog
    editWidget->changeText(testString);
    QVERIFY2(spy.count() == 1, "dataChanged signal wasn't emitted when changing text through dialog");
}

QTEST_MAIN(ScoreInteractionTest)

#include "tst_scoreinteractiontest.moc"
