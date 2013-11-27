/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <QString>
#include <QGraphicsScene>
#include <QFocusEvent>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <graphicsitemview/visualmusicmodel/interactinggraphicsitems/graphicitems/textwidget.h>
#include <graphicsitemview/visualmusicmodel/interactinggraphicsitems/graphicitems/graphicstextitem.h>

class TextWidgetTest : public QObject
{
    Q_OBJECT

public:
    TextWidgetTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetText();
    void testSetGetFont();
    void testSetGetColor();
    void testSetGetAlignment();
    void testTextChangedSignal();
    void testSizeChangedSignal();

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
    Q_ASSERT(m_textWidget->text() != text);

    m_textWidget->setText(text);
    QVERIFY2(m_textWidget->text() == text, "Text wasn't set or can't get back after setting");
    QVERIFY2(spy.count() == 0,
             "textChanged signal was emitted. This signal should only be emitted, if text was edited in the gui (e.g. mouse)");
}

void TextWidgetTest::testSetGetFont()
{
    QFont font("Arial");
    font.setPointSize(33);
    Q_ASSERT(m_textWidget->font() != font);

    m_textWidget->setFont(font);
    QVERIFY2(m_textWidget->font() == font, "Font wasn't set or can't get back");
}

void TextWidgetTest::testSetGetColor()
{
    QColor color(Qt::lightGray);
    Q_ASSERT(m_textWidget->color() != color);

    m_textWidget->setColor(color);
    QVERIFY2(m_textWidget->color() == color, "Color wasn't set or can't get back");
}

void TextWidgetTest::testSetGetAlignment()
{
    Qt::Alignment alignment = Qt::AlignLeft | Qt::AlignTop;
    Q_ASSERT(m_textWidget->alignment() != alignment);

    m_textWidget->setAlignment(alignment);
    QVERIFY2(m_textWidget->alignment() == alignment, "Alignment wasn't set or can't get back");
}

void TextWidgetTest::testTextChangedSignal()
{
    QString testText("test text 1");
    QFocusEvent focusInEvent(QEvent::FocusIn);
    QFocusEvent focusOutEvent(QEvent::FocusOut);
    QSignalSpy spy(m_textWidget, SIGNAL(textChanged(QString)));
    GraphicsTextItem *textItem = m_textWidget->m_textItem;

    textItem->setPlainText(testText);
    QVERIFY2(spy.count() == 0, "Text changed signal should only be emitted when text item has focus out event with new text");
    textItem->setPlainText("");

    // Simulate edit with focus in -> new text -> focus out
    textItem->focusInEvent(&focusInEvent);
    textItem->setPlainText(testText);
    textItem->focusOutEvent(&focusOutEvent);
    QVERIFY2(spy.count() == 1, "Text changed signal wasn't emitted after focus out of text item with new text");

    // Simulate edit with not changing text
    textItem->focusInEvent(&focusInEvent);
    textItem->focusOutEvent(&focusOutEvent);
    QVERIFY2(spy.count() == 1, "Text changed signal wasn emitted despite text hasn't changed");
}

void TextWidgetTest::testSizeChangedSignal()
{
    QSignalSpy spy(m_textWidget, SIGNAL(sizeChanged(QSizeF)));
    GraphicsTextItem *textItem = m_textWidget->m_textItem;
    QSizeF newSize(123.1116, 456.46748);

    textItem->document()->setPageSize(newSize);

    QVERIFY2(spy.count() == 1, "sizeChanged signal wasn't emitted after changing size");
}

QTEST_MAIN(TextWidgetTest)

#include "tst_textwidgettest.moc"
