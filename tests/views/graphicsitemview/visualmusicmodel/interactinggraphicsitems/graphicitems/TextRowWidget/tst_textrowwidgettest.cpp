/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <graphicsitemview/visualmusicmodel/interactinggraphicsitems/graphicitems/textrowwidget.h>

class TextRowWidgetTest : public QObject
{
    Q_OBJECT

public:
    TextRowWidgetTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetText();

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

QTEST_MAIN(TextRowWidgetTest)

#include "tst_textrowwidgettest.moc"
