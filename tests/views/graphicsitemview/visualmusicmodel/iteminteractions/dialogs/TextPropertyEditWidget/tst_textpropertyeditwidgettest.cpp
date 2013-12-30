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
#include <graphicsitemview/visualmusicmodel/iteminteractions/dialogs/textpropertyeditwidget.h>
#include "ui_textpropertyeditwidget.h"

class TextPropertyEditWidgetTest : public QObject
{
    Q_OBJECT

public:
    TextPropertyEditWidgetTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetText();
    void testChangeText();

private:
    TextPropertyEditWidget *m_editWidget;
};

TextPropertyEditWidgetTest::TextPropertyEditWidgetTest()
{
}

void TextPropertyEditWidgetTest::init()
{
    m_editWidget = new TextPropertyEditWidget();
}

void TextPropertyEditWidgetTest::cleanup()
{
    delete m_editWidget;
}

void TextPropertyEditWidgetTest::testSetGetText()
{
    QSignalSpy spy(m_editWidget, SIGNAL(textChanged(QString)));
    QString testText("Test text");

    m_editWidget->setText(testText);
    QVERIFY2(m_editWidget->text() == testText, "Can't get text from widget");
    QVERIFY2(m_editWidget->ui->lineEdit->text() == testText,
             "Text wasn't set on line edit");
    QVERIFY2(spy.count() == 0, "Signal must not be sent by setting text");
}

void TextPropertyEditWidgetTest::testChangeText()
{
    QSignalSpy spy(m_editWidget, SIGNAL(textChanged(QString)));
    QString testText("Test text");
    QString testTextUi("kdkdidkdifdjosf f");

    m_editWidget->changeText(testText);
    QVERIFY2(spy.count() == 1, "Signal must be sent when changing text");

    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY2(arguments.count() == 1, "Wrong argument count");
    QVERIFY2(arguments.at(0).toString() == testText,
             "New text wasn't emitted");

    m_editWidget->ui->lineEdit->setText(testTextUi);
    arguments = spy.takeFirst();
    QVERIFY2(arguments.count() == 1, "Wrong argument count");
    QVERIFY2(arguments.at(0).toString() == testTextUi,
             "New text wasn't emitted");
}

QTEST_MAIN(TextPropertyEditWidgetTest)

#include "tst_textpropertyeditwidgettest.moc"
