/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <app/commonpluginmanager.h>
#include <common/datatypes/length.h>
#include "tst_lengthdelegatetest.h"

Q_IMPORT_PLUGIN(MusicModelTestPlugin)

void LengthDelegateTest::initTestCase()
{
    m_pluginManager = PluginManager(new CommonPluginManager());
    m_model = new MusicModel(this);
    m_model->setPluginManager(m_pluginManager);

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

    m_symbolWithLengthIndex = new QPersistentModelIndex(symbolIndex(LP::SymbolLength, true));
    if (!m_symbolWithLengthIndex->isValid())
        qWarning("Instrument plugin has no symbol with length");

    m_symbolWithNoLengthIndex = new QPersistentModelIndex(symbolIndex(LP::SymbolLength, false));
    if (!m_symbolWithNoLengthIndex->isValid())
        qWarning("Instrument plugin has no symbol with no length");

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
    m_lengthIndex = m_model->index(m_symbolWithLengthIndex->row(), 0, m_symbolWithLengthIndex->parent());
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
    Length::Value length = m_symbolWithLengthIndex->data(LP::SymbolLength).value<Length::Value>();
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
    length = m_symbolWithLengthIndex->data(LP::SymbolLength).value<Length::Value>();
    lengthFromSymbolData = QString::number(length);
    QVERIFY2(m_editor->currentText() == lengthFromSymbolData, "Failed setting length");
}

QModelIndex LengthDelegateTest::symbolIndex(LP::SymbolDataRole role, bool hasData)
{
    QModelIndex tuneIndex = m_model->insertTuneWithScore(0, "score", m_instrumentNames.at(0));
    QModelIndex partIndex = m_model->insertPartIntoTune(0, tuneIndex, 5);
    QModelIndex measureIndex = m_model->index(0, 0, partIndex);

    foreach (QString symbolName, m_symbolNames) {
        QModelIndex symbolIndex = m_model->insertSymbolIntoMeasure(0, measureIndex, symbolName);
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

QTEST_MAIN(LengthDelegateTest)
