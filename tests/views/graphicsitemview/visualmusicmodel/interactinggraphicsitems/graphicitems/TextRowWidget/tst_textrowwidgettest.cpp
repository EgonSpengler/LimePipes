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
    m_textRowWidget->setText(TextRowWidget::Left, testText);
    QVERIFY2(m_textRowWidget->text(TextRowWidget::Left) == testText,
             "Can't set text and get it back");

    testText = "hello test 2... 1... 3...";
    m_textRowWidget->setText(TextRowWidget::Center, testText);
    QVERIFY2(m_textRowWidget->text(TextRowWidget::Center) == testText,
             "Can't set text and get it back");

    testText = "hello test 3... 2... 1...";
    m_textRowWidget->setText(TextRowWidget::Right, testText);
    QVERIFY2(m_textRowWidget->text(TextRowWidget::Right) == testText,
             "Can't set text and get it back");
}

void TextRowWidgetTest::testSetGetFont()
{
    QFont testFont("Arial", 33);
    m_textRowWidget->setFont(TextRowWidget::Left, testFont);
    QVERIFY2(m_textRowWidget->font(TextRowWidget::Left) == testFont,
             "Can't set font and get it back");

    m_textRowWidget->setFont(TextRowWidget::Center, testFont);
    QVERIFY2(m_textRowWidget->font(TextRowWidget::Center) == testFont,
             "Can't set font and get it back");

    m_textRowWidget->setFont(TextRowWidget::Right, testFont);
    QVERIFY2(m_textRowWidget->font(TextRowWidget::Right) == testFont,
             "Can't set font and get it back");
}

void TextRowWidgetTest::testSetGetColor()
{
    QColor testColor(Qt::lightGray);
    m_textRowWidget->setColor(TextRowWidget::Left, testColor);
    QVERIFY2(m_textRowWidget->color(TextRowWidget::Left) == testColor,
             "Can't set color and get it back");

    m_textRowWidget->setColor(TextRowWidget::Center, testColor);
    QVERIFY2(m_textRowWidget->color(TextRowWidget::Center) == testColor,
             "Can't set color and get it back");

    m_textRowWidget->setColor(TextRowWidget::Right, testColor);
    QVERIFY2(m_textRowWidget->color(TextRowWidget::Right) == testColor,
             "Can't set color and get it back");
}

void TextRowWidgetTest::testSetGetTextVisible()
{
    bool visible = m_textRowWidget->isTextVisible(TextRowWidget::Left);
    m_textRowWidget->setTextVisible(TextRowWidget::Left, !visible);
    QVERIFY2(m_textRowWidget->isTextVisible(TextRowWidget::Left) != visible,
             "Can't set visible state of text and get it back");

    visible = m_textRowWidget->isTextVisible(TextRowWidget::Center);
    m_textRowWidget->setTextVisible(TextRowWidget::Center, !visible);
    QVERIFY2(m_textRowWidget->isTextVisible(TextRowWidget::Center) != visible,
             "Can't set visible state of text and get it back");

    visible = m_textRowWidget->isTextVisible(TextRowWidget::Right);
    m_textRowWidget->setTextVisible(TextRowWidget::Right, !visible);
    QVERIFY2(m_textRowWidget->isTextVisible(TextRowWidget::Right) != visible,
             "Can't set visible state of text and get it back");
}

void TextRowWidgetTest::testTextWidget()
{
    QString text("text left");
    TextWidget *textWidget = m_textRowWidget->textWidget(TextRowWidget::Left);
    QVERIFY2(textWidget, "0 pointer returned for text widget");
    m_textRowWidget->setText(TextRowWidget::Left, text);
    QVERIFY2(textWidget->text() == text, "Wrong text widget was returned");

    text = "text center";
    textWidget = m_textRowWidget->textWidget(TextRowWidget::Center);
    QVERIFY2(textWidget, "0 pointer returned for text widget");
    m_textRowWidget->setText(TextRowWidget::Center, text);
    QVERIFY2(textWidget->text() == text, "Wrong text widget was returned");

    text = "text right";
    textWidget = m_textRowWidget->textWidget(TextRowWidget::Right);
    QVERIFY2(textWidget, "0 pointer returned for text widget");
    m_textRowWidget->setText(TextRowWidget::Right, text);
    QVERIFY2(textWidget->text() == text, "Wrong text widget was returned");
}

QTEST_MAIN(TextRowWidgetTest)

#include "tst_textrowwidgettest.moc"
