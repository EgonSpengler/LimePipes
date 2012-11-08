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
#include <pitchdelegate.h>
#include <pitch.h>
#include <symbol.h>
#include <instrument.h>
#include <musicmodel.h>

Q_IMPORT_PLUGIN(lp_musicmodeltestplugin)

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
    QModelIndex symbolIndex(LP::DataRole role, bool hasData);
    MusicModel *m_model;
    PitchDelegate *m_delegate;
    InstrumentPtr m_instrument;
    QPersistentModelIndex *m_tuneIndex;
    QPersistentModelIndex *m_symbolWithPitchIndex;
    QPersistentModelIndex *m_symbolWithNoPitchIndex;
    QWidget *m_parentWidget;
    QComboBox *m_editor;
    QModelIndex m_pitchIndex;
    QStringList m_instrumentNames;
    QStringList m_symbolNames;
};

void PitchDelegateTest::initTestCase()
{
    m_model = new MusicModel(this);

    m_instrumentNames = m_model->instrumentNames();
    if (m_instrumentNames.isEmpty()) {
        qWarning("There was no plugin loaded by the model.");
        return;
    }

    m_symbolNames = m_model->symbolNamesForInstrument(m_instrumentNames.at(0));
    if (m_symbolNames.isEmpty()) {
        qWarning("Plugin's instrument has no symbols.");
        return;
    }

    m_tuneIndex = new QPersistentModelIndex(
                m_model->insertTuneWithScore(0, "One score", m_model->instrumentNames().at(0)));

    QVariant instrumentVar = m_tuneIndex->data(LP::tuneInstrument);
    if (!instrumentVar.isValid())
        qWarning("Tune has no instrument");
    if (instrumentVar.canConvert<InstrumentPtr>()) {
        m_instrument = instrumentVar.value<InstrumentPtr>();
    } else {
        qWarning("Can't convert instrument variant into instrument");
    }

    m_symbolWithPitchIndex = new QPersistentModelIndex(symbolIndex(LP::symbolPitch, true));
    if (!m_symbolWithPitchIndex->isValid())
        qWarning("Instrument plugin has no symbol with pitch");

    m_symbolWithNoPitchIndex = new QPersistentModelIndex(symbolIndex(LP::symbolPitch, false));
    if (!m_symbolWithNoPitchIndex->isValid())
        qWarning("Instrument plugin has no symbol with no pitch");

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
    m_pitchIndex = m_model->index(m_symbolWithPitchIndex->row(), 0, m_symbolWithPitchIndex->parent());
    Q_ASSERT(m_pitchIndex.isValid());
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

QModelIndex PitchDelegateTest::symbolIndex(LP::DataRole role, bool hasData)
{
    QModelIndex tuneIndex = m_model->insertTuneWithScore(0, "score", m_instrumentNames.at(0));
    foreach (QString symbolName, m_symbolNames) {
        QModelIndex symbolIndex = m_model->insertSymbol(0, tuneIndex, symbolName);
        QVariant dataVar = symbolIndex.data(role);
        if (hasData) {
            if (dataVar.isValid()) {
                return symbolIndex;
            }
        } else {
            if (!dataVar.isValid()) {
                return symbolIndex;
            }
        }
    }
    return QModelIndex();
}

QTEST_MAIN(PitchDelegateTest)

#include "tst_pitchdelegatetest.moc"
