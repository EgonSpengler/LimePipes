/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <QtTest/QSignalSpy>
#include <graphicsitemview/visualmusicmodel/iteminteractions/dialogs/scorepropertiesdialog.h>
#include <graphicsitemview/visualmusicmodel/iteminteractions/dialogs/textpropertyeditwidget.h>

class ScorePropertiesDialogTest : public QObject
{
    Q_OBJECT

public:
    ScorePropertiesDialogTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testTextEditWidgetForRole();
    void testSetGetPropertyText();
    void testSetGetPropertyFont();
    void testSetGetPropertyColor();

private:
    ScorePropertiesDialog *dialog;
};

ScorePropertiesDialogTest::ScorePropertiesDialogTest()
{
}

void ScorePropertiesDialogTest::init()
{
    dialog = new ScorePropertiesDialog();
}

void ScorePropertiesDialogTest::cleanup()
{
    delete dialog;
}

void ScorePropertiesDialogTest::testTextEditWidgetForRole()
{
    QVERIFY2(dialog->textEditWidgetForRole(LP::ScoreArranger),
             "No text edit widget for role");
    QVERIFY2(dialog->textEditWidgetForRole(LP::ScoreComposer),
             "No text edit widget for role");
    QVERIFY2(dialog->textEditWidgetForRole(LP::ScoreCopyright),
             "No text edit widget for role");
    QVERIFY2(dialog->textEditWidgetForRole(LP::ScoreTitle),
             "No text edit widget for role");
    QVERIFY2(dialog->textEditWidgetForRole(LP::ScoreType),
             "No text edit widget for role");
    QVERIFY2(dialog->textEditWidgetForRole(LP::ScoreYear),
             "No text edit widget for role");
}

void ScorePropertiesDialogTest::testSetGetPropertyText()
{
    QSignalSpy spy(dialog, SIGNAL(propertyTextChanged(LP::ScoreDataRole,QString)));
    QString testText("test text");
    LP::ScoreDataRole testDataRole = LP::ScoreArranger;

    dialog->setPropertyText(testDataRole, testText);
    QVERIFY2(dialog->propertyText(testDataRole) == testText,
             "Can't get right property text");
    QVERIFY2(spy.count() == 0, "Signal was emitted when setting text");
    dialog->textEditWidgetForRole(testDataRole)->changeText(testText + "bla");
    QVERIFY2(spy.count() == 1, "Signal wasn't emitted when changing text");
}

void ScorePropertiesDialogTest::testSetGetPropertyFont()
{
    QSignalSpy spy(dialog, SIGNAL(propertyFontChanged(LP::ScoreDataRole,QFont)));
    LP::ScoreDataRole testDataRole = LP::ScoreArranger;
    QFont testFont("Arial", 33);

    dialog->setPropertyFont(testDataRole, testFont);

    QVERIFY2(dialog->propertyFont(testDataRole) == testFont,
             "Can't get right property font");
    QVERIFY2(spy.count() == 0, "Signal was emitted when setting font");

    testFont = QFont("Helvetica", 43);
    dialog->textEditWidgetForRole(testDataRole)->changeFont(testFont);
    QVERIFY2(spy.count() == 1, "Signal wasn't emitted when changing font");
}

void ScorePropertiesDialogTest::testSetGetPropertyColor()
{
    QSignalSpy spy(dialog, SIGNAL(propertyColorChanged(LP::ScoreDataRole,QColor)));
    LP::ScoreDataRole testDataRole = LP::ScoreArranger;
    QColor testColor(Qt::darkBlue);

    dialog->setPropertyColor(testDataRole, testColor);

    QVERIFY2(dialog->propertyColor(testDataRole) == testColor,
             "Can't get right property color");
    QVERIFY2(spy.count() == 0, "Signal was emitted when setting color");

    testColor = QColor(Qt::darkRed);
    dialog->textEditWidgetForRole(testDataRole)->changeColor(testColor);
    QVERIFY2(spy.count() == 1, "Signal wasn't emitted when changing color");
}

QTEST_MAIN(ScorePropertiesDialogTest)

#include "tst_scorepropertiesdialogtest.moc"
