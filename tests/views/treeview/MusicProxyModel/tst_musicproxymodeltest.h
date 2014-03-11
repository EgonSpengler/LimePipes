/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICPROXYMODELTEST_H
#define MUSICPROXYMODELTEST_H

#include <QMetaType>
#include <musicmodel.h>
#include <symbol.h>
#include <views/treeview/musicproxymodel.h>
#include <common/pluginmanagerinterface.h>

namespace {

class SymbolWithPitchAndLength : public Symbol
{
public:
    SymbolWithPitchAndLength()
        : Symbol()
    {
        setSymbolOptions(Symbol::HasPitch |
                         Symbol::HasLength);
        initData(QVariant::fromValue<PitchPtr>(PitchPtr(new Pitch(2, "testpitch"))), LP::SymbolPitch);
        initData(QVariant::fromValue<Length::Value>(Length::_32), LP::SymbolLength);
    }
};

}

class MusicProxyModelTest : public QObject
{
    Q_OBJECT

public:
    explicit MusicProxyModelTest();

private Q_SLOTS:
    void initTestcase();
    void init();
    void cleanup();
    void testColumnCount();
    void testInsertScore();
    void testAppendScore();
    void testInsertTuneIntoScore();
    void testAppendTuneToScore();
    void testInsertTuneWithScore();
    void testInsertSymbol();
    void testCallOfOkToInsertChild();
    void testItemForIndex();
    void testClear();
    void testIsScore();
    void testIsTune();
    void testIsSymbol();
    void testPitchColumn();
    void testLengthColumn();

private:
    QModelIndex symbolIndexWithData(LP::SymbolDataRole role);
    MusicModel *m_sourceModel;
    MusicProxyModel *m_proxyModel;
    QStringList m_instrumentNames;
    QStringList m_symbolNames;
    PluginManager m_pluginManager;
};

#endif
