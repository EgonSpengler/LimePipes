/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <textwidget.h>
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
    QSignalSpy spy(m_textWidget, SIGNAL(textChanged(QString)));
    QString text("New text");

    m_textWidget->setText(text);
    QVERIFY2(spy.count() == 1, "Text changed signal wasn't emitted");

    m_textWidget->setText(text);
    QVERIFY2(spy.count() == 1, "Text changed signal was emitted a second time, after setting same text");
}

QTEST_MAIN(TextWidgetTest)

#include "tst_textwidgettest.moc"
