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
#include <pitchdelegateinstrument.h>
#include <pitchdelegate.h>
#include <pitch.h>
#include <symbol.h>
#include <instrument.h>
#include <musicmodel.h>
#include <melodynote.h>

class PitchDelegateTest : public QObject
{
    Q_OBJECT
    
public:
    PitchDelegateTest()
        : m_model(0),
          m_delegate(0),
          m_instrument(0),
          m_tuneIndex(0),
          m_symbolWithPitchIndex(0),
          m_symbolWithNoPitchIndex(0),
          m_parentWidget(0),
          m_editor(0) {}
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void testCreateEditor();
    void testSetEditorData();
    void setModelData();

private:
    MusicModel *m_model;
    PitchDelegate *m_delegate;
    InstrumentPtr m_instrument;
    QPersistentModelIndex *m_tuneIndex;
    QPersistentModelIndex *m_symbolWithPitchIndex;
    QPersistentModelIndex *m_symbolWithNoPitchIndex;
    QWidget *m_parentWidget;
    QComboBox *m_editor;
    QModelIndex m_pitchIndex;

    class SymbolWithPitch : public MelodyNote
    {
    public:
        SymbolWithPitch(PitchPtr pitch)
        {
            initData(QVariant::fromValue<PitchPtr>(pitch), LP::symbolPitch);
        }
    };
};

void PitchDelegateTest::initTestCase()
{
    m_model = new MusicModel(this);
    m_instrument = InstrumentPtr(new PitchDelegateInstrument());
    m_tuneIndex = new QPersistentModelIndex(
                m_model->insertTuneWithScore(0, "One score", m_instrument));
    m_symbolWithPitchIndex = new QPersistentModelIndex(
                m_model->insertSymbol(0, *m_tuneIndex, new SymbolWithPitch(m_instrument->pitchContext()->pitchForStaffPos(0))));
    m_symbolWithNoPitchIndex = new QPersistentModelIndex(
                m_model->insertSymbol(0, *m_tuneIndex, new Symbol(LP::Bar, "no pitch symbol")));
    m_parentWidget = new QWidget();
    m_delegate = new PitchDelegate(this);
}

void PitchDelegateTest::cleanupTestCase()
{
    delete m_model;
    delete m_delegate;
    delete m_tuneIndex;
    delete m_symbolWithPitchIndex;
    delete m_symbolWithNoPitchIndex;
    delete m_parentWidget;
}

void PitchDelegateTest::init()
{
    int rowOfSymbolWithPitch = 1;
    QModelIndex score = m_model->index(0, 0, QModelIndex());
    Q_ASSERT(score.isValid());
    QModelIndex tune = m_model->index(0, 0, score);
    Q_ASSERT(tune.isValid());
    m_pitchIndex = m_model->index(rowOfSymbolWithPitch, 0, tune);
}

void PitchDelegateTest::testCreateEditor()
{
    m_editor = static_cast<QComboBox*>(m_delegate->createEditor(m_parentWidget, QStyleOptionViewItem(), m_pitchIndex));
    Q_ASSERT(m_editor);
    m_editor->setParent(m_parentWidget);
    QVERIFY2(m_editor, "delegate hasn't returned a QComboBox as editor");
}

void PitchDelegateTest::testSetEditorData()
{
    Q_ASSERT(m_editor);
    m_delegate->setEditorData(m_editor, m_pitchIndex);
    QVERIFY2(m_editor->count() == m_instrument->pitchNames().count(), "Editor wasn't set with pitch names");
}

void PitchDelegateTest::setModelData()
{
    Q_ASSERT(m_editor);

    // check current pitch with symbol data
    PitchPtr pitchFromSymbolData = m_symbolWithPitchIndex->data(LP::symbolPitch).value<PitchPtr>();
    QVERIFY2(m_editor->currentText() == pitchFromSymbolData->name(), "current selected pitch doesn't match with symbol data");

    int newIndex = m_editor->currentIndex() + 1;
    if (newIndex == m_editor->count()) {
        newIndex = 0;
    }
    m_editor->setCurrentIndex(newIndex);

    Q_ASSERT(pitchFromSymbolData->name() != m_editor->currentText());

    // Set model data
    m_delegate->setModelData(m_editor, m_model, m_pitchIndex);
    pitchFromSymbolData = m_symbolWithPitchIndex->data(LP::symbolPitch).value<PitchPtr>();
    QVERIFY2(m_editor->currentText() == pitchFromSymbolData->name(), "Failed setting pitch");
}

QTEST_MAIN(PitchDelegateTest)

#include "tst_pitchdelegatetest.moc"