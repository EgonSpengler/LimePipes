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

Q_DECLARE_METATYPE(LP::ScoreDataRole)

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
    QString testTextChange("test test blablabla");
    LP::ScoreDataRole testDataRole = LP::ScoreArranger;

    dialog->setPropertyText(testDataRole, testText);
    QVERIFY2(dialog->propertyText(testDataRole) == testText,
             "Can't get right property text");
    QVERIFY2(spy.count() == 0, "Signal was emitted when setting text");
    dialog->textEditWidgetForRole(testDataRole)->changeText(testTextChange);
    QVERIFY2(spy.count() == 1, "Signal wasn't emitted when changing text");
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY2(arguments.count() == 2, "Wrong count of arguments emitted");
    QVERIFY2(arguments.at(0).value<LP::ScoreDataRole>() == testDataRole,
             "Wrong data role emitted");
    QVERIFY2(arguments.at(1).toString() == testTextChange,
             "Wrong text emitted for text change");
}

QTEST_MAIN(ScorePropertiesDialogTest)

#include "tst_scorepropertiesdialogtest.moc"
