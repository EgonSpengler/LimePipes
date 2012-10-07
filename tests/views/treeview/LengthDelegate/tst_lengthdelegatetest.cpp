/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QComboBox>
#include <length.h>
#include <musicmodel.h>
#include <lengthdelegate.h>
#include <melodynote.h>

class LengthDelegateTest : public QObject
{
    Q_OBJECT
    
public:
    LengthDelegateTest()
        : m_model(0),
          m_delegate(0),
          m_tuneIndex(0),
          m_symbolWithLengthIndex(0),
          m_symbolWithNoLengthIndex(0),
          m_parentWidget(0),
          m_editor(0) {}
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void testCreateEditor();
    void testSetEditorData();
    void testSetModelData();

private:
    MusicModel *m_model;
    LengthDelegate *m_delegate;
    QPersistentModelIndex *m_tuneIndex;
    QPersistentModelIndex *m_symbolWithLengthIndex;
    QPersistentModelIndex *m_symbolWithNoLengthIndex;
    QWidget *m_parentWidget;
    QComboBox *m_editor;
    QModelIndex m_lengthIndex;

    class SymbolWithLength : public Symbol
    {
    public:
        SymbolWithLength(Length::Value length)
            : Symbol(LP::Bar, "testsymbol", Symbol::HasNoPitch, Symbol::HasLength)
        {
            initData(QVariant::fromValue<Length::Value>(length), LP::symbolLength);
        }
    };

    class TestInstrument : public Instrument
    {
    public:
        TestInstrument()
            : Instrument(LP::BassDrum, "Bass") {}
        bool supportsSymbolType(int type) const
        { Q_UNUSED(type) return true; }
    };
};

void LengthDelegateTest::initTestCase()
{
    m_model = new MusicModel(this);
    m_tuneIndex = new QPersistentModelIndex(
                m_model->insertTuneWithScore(0, "One score", InstrumentPtr(new TestInstrument())));
    m_symbolWithLengthIndex = new QPersistentModelIndex(
                m_model->insertSymbol(0, *m_tuneIndex, new SymbolWithLength(Length::_4)));
    m_symbolWithNoLengthIndex = new QPersistentModelIndex(
                m_model->insertSymbol(0, *m_tuneIndex, new Symbol(LP::Bar, "no length symbol")));
    m_parentWidget = new QWidget();
    m_delegate = new LengthDelegate(this);
}

void LengthDelegateTest::cleanupTestCase()
{
    delete m_model;
    delete m_delegate;
    delete m_tuneIndex;
    delete m_symbolWithLengthIndex;
    delete m_symbolWithNoLengthIndex;
    delete m_parentWidget;
}

void LengthDelegateTest::init()
{
    int rowOfSymbolWithLength = 1;

    QModelIndex score = m_model->index(0, 0, QModelIndex());
    Q_ASSERT(score.isValid());
    QModelIndex tune = m_model->index(0, 0, score);
    Q_ASSERT(tune.isValid());
    m_lengthIndex = m_model->index(rowOfSymbolWithLength, 0, tune);
    Q_ASSERT(m_lengthIndex.isValid());
}

void LengthDelegateTest::testCreateEditor()
{
    m_editor = static_cast<QComboBox*>(m_delegate->createEditor(m_parentWidget, QStyleOptionViewItem(), m_lengthIndex));
    Q_ASSERT(m_editor);
    m_editor->setParent(m_parentWidget);
    QVERIFY2(m_editor, "delegate hasn't returned a QComboBox as editor");
}

void LengthDelegateTest::testSetEditorData()
{
    Q_ASSERT(m_editor);
    m_delegate->setEditorData(m_editor, m_lengthIndex);
    QVERIFY2(m_editor->count() == Length::lengthValues().count(), "Editor wasn't set with all length values");
}

void LengthDelegateTest::testSetModelData()
{
    Q_ASSERT(m_editor);

    // check current length with symbol data
    Length::Value length = m_symbolWithLengthIndex->data(LP::symbolLength).value<Length::Value>();
    QString lengthFromSymbolData = QString::number(length);
    QVERIFY2(m_editor->currentText() == lengthFromSymbolData, "current selected length doesn't match with symbol data");

    int newIndex = m_editor->currentIndex() + 1;
    if (newIndex == m_editor->count()) {
        newIndex = 0;
    }
    m_editor->setCurrentIndex(newIndex);

    Q_ASSERT(lengthFromSymbolData != m_editor->currentText());

    // Set model data
    m_delegate->setModelData(m_editor, m_model, m_lengthIndex);
    length = m_symbolWithLengthIndex->data(LP::symbolLength).value<Length::Value>();
    lengthFromSymbolData = QString::number(length);
    QVERIFY2(m_editor->currentText() == lengthFromSymbolData, "Failed setting length");
}

QTEST_MAIN(LengthDelegateTest)

#include "tst_lengthdelegatetest.moc"
