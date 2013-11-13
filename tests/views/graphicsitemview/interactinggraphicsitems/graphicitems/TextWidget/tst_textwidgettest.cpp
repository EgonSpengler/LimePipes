/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <graphicsitemview/interactinggraphicsitems/graphicitems/textwidget.h>
#include <QGraphicsScene>
#include <QtTest/QSignalSpy>
#include <QtTest/QtTest>

class TextWidgetTest : public QObject
{
    Q_OBJECT

public:
    TextWidgetTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetText();

private:
    TextWidget *m_textWidget;
};

TextWidgetTest::TextWidgetTest()
{
}

void TextWidgetTest::init()
{
    m_textWidget = new TextWidget();
}

void TextWidgetTest::cleanup()
{
    delete m_textWidget;
}

void TextWidgetTest::testSetGetText()
{
    QString text("New text");
    Q_ASSERT(m_textWidget->text() != text);

    m_textWidget->setText(text);
    QVERIFY2(m_textWidget->text() == text, "Text wasn't set or can't get back after setting");
}

QTEST_MAIN(TextWidgetTest)

#include "tst_textwidgettest.moc"
