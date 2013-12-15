/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <QSignalSpy>
#include <QFocusEvent>
#include <graphicsitemview/visualmusicmodel/interactinggraphicsitems/graphicitems/textrowwidget.h>
#include <graphicsitemview/visualmusicmodel/interactinggraphicsitems/graphicitems/textwidget.h>

class TextRowWidgetTest : public QObject
{
    Q_OBJECT

public:
    TextRowWidgetTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetText();
    void testSetGetFont();
    void testSetGetColor();
    void testSetGetTextVisible();
    void testTextWidget();
    void testTextChanged();

private:
    TextRowWidget *m_textRowWidget;
};

TextRowWidgetTest::TextRowWidgetTest()
{
}

void TextRowWidgetTest::init()
{
    m_textRowWidget = new TextRowWidget();
}

void TextRowWidgetTest::cleanup()
{
    delete m_textRowWidget;
}

void TextRowWidgetTest::testSetGetText()
{
    QString testText("hello test 1... 2... 3...");
    m_textRowWidget->setText(Settings::TextAlignment::Left, testText);
    QVERIFY2(m_textRowWidget->text(Settings::TextAlignment::Left) == testText,
             "Can't set text and get it back");

    testText = "hello test 2... 1... 3...";
    m_textRowWidget->setText(Settings::TextAlignment::Center, testText);
    QVERIFY2(m_textRowWidget->text(Settings::TextAlignment::Center) == testText,
             "Can't set text and get it back");

    testText = "hello test 3... 2... 1...";
    m_textRowWidget->setText(Settings::TextAlignment::Right, testText);
    QVERIFY2(m_textRowWidget->text(Settings::TextAlignment::Right) == testText,
             "Can't set text and get it back");
}

void TextRowWidgetTest::testSetGetFont()
{
    QFont testFont("Arial", 33);
    m_textRowWidget->setFont(Settings::TextAlignment::Left, testFont);
    QVERIFY2(m_textRowWidget->font(Settings::TextAlignment::Left) == testFont,
             "Can't set font and get it back");

    m_textRowWidget->setFont(Settings::TextAlignment::Center, testFont);
    QVERIFY2(m_textRowWidget->font(Settings::TextAlignment::Center) == testFont,
             "Can't set font and get it back");

    m_textRowWidget->setFont(Settings::TextAlignment::Right, testFont);
    QVERIFY2(m_textRowWidget->font(Settings::TextAlignment::Right) == testFont,
             "Can't set font and get it back");
}

void TextRowWidgetTest::testSetGetColor()
{
    QColor testColor(Qt::lightGray);
    m_textRowWidget->setColor(Settings::TextAlignment::Left, testColor);
    QVERIFY2(m_textRowWidget->color(Settings::TextAlignment::Left) == testColor,
             "Can't set color and get it back");

    m_textRowWidget->setColor(Settings::TextAlignment::Center, testColor);
    QVERIFY2(m_textRowWidget->color(Settings::TextAlignment::Center) == testColor,
             "Can't set color and get it back");

    m_textRowWidget->setColor(Settings::TextAlignment::Right, testColor);
    QVERIFY2(m_textRowWidget->color(Settings::TextAlignment::Right) == testColor,
             "Can't set color and get it back");
}

void TextRowWidgetTest::testSetGetTextVisible()
{
    bool visible = m_textRowWidget->isTextVisible(Settings::TextAlignment::Left);
    m_textRowWidget->setTextVisible(Settings::TextAlignment::Left, !visible);
    QVERIFY2(m_textRowWidget->isTextVisible(Settings::TextAlignment::Left) != visible,
             "Can't set visible state of text and get it back");

    visible = m_textRowWidget->isTextVisible(Settings::TextAlignment::Center);
    m_textRowWidget->setTextVisible(Settings::TextAlignment::Center, !visible);
    QVERIFY2(m_textRowWidget->isTextVisible(Settings::TextAlignment::Center) != visible,
             "Can't set visible state of text and get it back");

    visible = m_textRowWidget->isTextVisible(Settings::TextAlignment::Right);
    m_textRowWidget->setTextVisible(Settings::TextAlignment::Right, !visible);
    QVERIFY2(m_textRowWidget->isTextVisible(Settings::TextAlignment::Right) != visible,
             "Can't set visible state of text and get it back");
}

void TextRowWidgetTest::testTextWidget()
{
    QString text("text left");
    TextWidget *textWidget = m_textRowWidget->textWidget(Settings::TextAlignment::Left);
    QVERIFY2(textWidget, "0 pointer returned for text widget");
    m_textRowWidget->setText(Settings::TextAlignment::Left, text);
    QVERIFY2(textWidget->text() == text, "Wrong text widget was returned");

    text = "text center";
    textWidget = m_textRowWidget->textWidget(Settings::TextAlignment::Center);
    QVERIFY2(textWidget, "0 pointer returned for text widget");
    m_textRowWidget->setText(Settings::TextAlignment::Center, text);
    QVERIFY2(textWidget->text() == text, "Wrong text widget was returned");

    text = "text right";
    textWidget = m_textRowWidget->textWidget(Settings::TextAlignment::Right);
    QVERIFY2(textWidget, "0 pointer returned for text widget");
    m_textRowWidget->setText(Settings::TextAlignment::Right, text);
    QVERIFY2(textWidget->text() == text, "Wrong text widget was returned");
}

void TextRowWidgetTest::testTextChanged()
{
    QSignalSpy spy(m_textRowWidget, SIGNAL(textChanged(Settings::TextAlignment,QString)));

    QString testText("Test text left");
    TextWidget *textWidget = m_textRowWidget->textWidget(Settings::TextAlignment::Left);
    Q_ASSERT(textWidget);
    textWidget->setText(testText);
    QVERIFY2(spy.count() == 0, "Text changed signal must not be emitted when setting text");

    textWidget->textItemFocusOut();
    QVERIFY2(spy.count() == 1, "Text changed signal wasn't emitted");
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY2(arguments.count() == 2, "Signal has not correct arguments count");

    // Getting row alignment parameter
    Settings::TextAlignment rowAlignment = arguments.at(0).value<Settings::TextAlignment>();
    QVERIFY2(rowAlignment == Settings::TextAlignment::Left, "Signal emitted with wrong row alignment");
    // Getting new text parameter
    QVERIFY2(arguments.at(1).toString() == testText, "Signal emitted wrong text");

    testText = "Test text center";
    textWidget = m_textRowWidget->textWidget(Settings::TextAlignment::Center);
    Q_ASSERT(textWidget);
    textWidget->setText(testText);
    QVERIFY2(spy.count() == 0, "Text changed signal must not be emitted when setting text");

    textWidget->textItemFocusOut();
    QVERIFY2(spy.count() == 1, "Text changed signal wasn't emitted");
    arguments = spy.takeFirst();
    QVERIFY2(arguments.count() == 2, "Signal has not correct arguments count");

    // Getting row alignment parameter
    rowAlignment = arguments.at(0).value<Settings::TextAlignment>();
    QVERIFY2(rowAlignment == Settings::TextAlignment::Center, "Signal emitted with wrong row alignment");
    // Getting new text parameter
    QVERIFY2(arguments.at(1).toString() == testText, "Signal emitted wrong text");

    testText = "Test text right";
    textWidget = m_textRowWidget->textWidget(Settings::TextAlignment::Right);
    Q_ASSERT(textWidget);
    textWidget->setText(testText);
    QVERIFY2(spy.count() == 0, "Text changed signal must not be emitted when setting text");

    textWidget->textItemFocusOut();
    QVERIFY2(spy.count() == 1, "Text changed signal wasn't emitted");
    arguments = spy.takeFirst();
    QVERIFY2(arguments.count() == 2, "Signal has not correct arguments count");

    // Getting row alignment parameter
    rowAlignment = arguments.at(0).value<Settings::TextAlignment>();
    QVERIFY2(rowAlignment == Settings::TextAlignment::Right, "Signal emitted with wrong row alignment");
    // Getting new text parameter
    QVERIFY2(arguments.at(1).toString() == testText, "Signal emitted wrong text");
}

QTEST_MAIN(TextRowWidgetTest)

#include "tst_textrowwidgettest.moc"
