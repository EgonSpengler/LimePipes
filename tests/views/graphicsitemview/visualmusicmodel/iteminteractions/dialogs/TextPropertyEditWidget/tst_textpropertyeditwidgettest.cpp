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
    void testSetGetFont();
    void testChangeFont();
    void testSetGetColor();
    void testChangeColor();

private:
    TextPropertyEditWidget *editWidget;
};

TextPropertyEditWidgetTest::TextPropertyEditWidgetTest()
{
}

void TextPropertyEditWidgetTest::init()
{
    editWidget = new TextPropertyEditWidget();
}

void TextPropertyEditWidgetTest::cleanup()
{
    delete editWidget;
}

void TextPropertyEditWidgetTest::testSetGetText()
{
    QSignalSpy spy(editWidget, SIGNAL(textChanged(QString)));
    QString testText("Test text");

    editWidget->setText(testText);
    QVERIFY2(editWidget->text() == testText, "Can't get text from widget");
    QVERIFY2(editWidget->ui->lineEdit->text() == testText,
             "Text wasn't set on line edit");
    QVERIFY2(spy.count() == 0, "Signal must not be sent by setting text");
}

void TextPropertyEditWidgetTest::testChangeText()
{
    QSignalSpy spy(editWidget, SIGNAL(textChanged(QString)));
    QString testText("Test text");

    editWidget->changeText(testText);
    QVERIFY2(spy.count() == 1, "Signal must be sent when changing text");
}

void TextPropertyEditWidgetTest::testSetGetFont()
{
    QSignalSpy spy(editWidget, SIGNAL(fontChanged(QFont)));
    QFont testFont("Comic Sans", 23);

    editWidget->setFont(testFont);
    QVERIFY2(editWidget->font() == testFont, "Can't get font from widget");
    QVERIFY2(spy.count() == 0, "Signal must not be sent by setting font");
}

void TextPropertyEditWidgetTest::testChangeFont()
{
    QSignalSpy spy(editWidget, SIGNAL(fontChanged(QFont)));
    QFont testFont("Comic Sans", 23);

    editWidget->changeFont(testFont);
    QVERIFY2(spy.count() == 1, "Signal must be sent when changing font");
}

void TextPropertyEditWidgetTest::testSetGetColor()
{
    QSignalSpy spy(editWidget, SIGNAL(colorChanged(QColor)));
    QColor testColor(Qt::darkCyan);

    editWidget->setColor(testColor);
    QVERIFY2(editWidget->color() == testColor, "Can't get color from widget");
    QVERIFY2(spy.count() == 0, "Signal must not be sent by setting color");
}

void TextPropertyEditWidgetTest::testChangeColor()
{
    QSignalSpy spy(editWidget, SIGNAL(colorChanged(QColor)));
    QColor testColor(Qt::darkCyan);

    editWidget->changeColor(testColor);
    QVERIFY2(spy.count() == 1, "Signal must be sent when changing color");
}

QTEST_MAIN(TextPropertyEditWidgetTest)

#include "tst_textpropertyeditwidgettest.moc"
