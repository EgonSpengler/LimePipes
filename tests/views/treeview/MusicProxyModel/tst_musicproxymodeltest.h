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

namespace {

class SymbolWithPitchAndLength : public Symbol
{
public:
    SymbolWithPitchAndLength()
        : Symbol()
    {
        setSymbolOptions(Symbol::HasPitch |
                         Symbol::HasLength);
        initData(QVariant::fromValue<PitchPtr>(PitchPtr(new Pitch(2, "testpitch"))), LP::symbolPitch);
        initData(QVariant::fromValue<Length::Value>(Length::_32), LP::symbolLength);
    }
};

}

class MusicProxyModelTest : public QObject
{
    Q_OBJECT
    
public:
    MusicProxyModelTest()
        : m_sourceModel(0),
          m_proxyModel(0)
    { qRegisterMetaType<QModelIndex>("QModelIndex"); }
    
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
    QModelIndex symbolIndexWithData(LP::DataRole role);
    MusicModel *m_sourceModel;
    MusicProxyModel *m_proxyModel;
    QStringList m_instrumentNames;
    QStringList m_symbolNames;
};

#endif
