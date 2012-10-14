/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>

#include <musicmodel.h>
#include <musicproxymodel.h>
#include <instrument.h>
#include <symbol.h>

namespace {

class SymbolWithPitch : public Symbol
{
public:
    SymbolWithPitch()
        : Symbol()
    {
        setSymbolOptions(Symbol::HasPitch);
    }
};

class TestInstrument : public Instrument
{
public:
    TestInstrument()
        : Instrument() {}
    bool supportsSymbolType(int type) const
        { Q_UNUSED(type) return true; }
};

}

class MusicProxyModelTest : public QObject
{
    Q_OBJECT
    
public:
    MusicProxyModelTest()
        : m_model(0),
          m_proxyModel(0) {}
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testColumnCount();
    void testPitchColumn();

private:
    MusicModel *m_model;
    MusicProxyModel *m_proxyModel;
};

void MusicProxyModelTest::initTestCase()
{
    m_model = new MusicModel(this);
    m_proxyModel = new MusicProxyModel(this);
    m_proxyModel->setSourceModel(m_model);
}

void MusicProxyModelTest::cleanupTestCase()
{
}

void MusicProxyModelTest::testColumnCount()
{
    //QVERIFY2(m_proxyModel->columnCount(QModelIndex()) == 3, "Fail, wrong column count");
}

void MusicProxyModelTest::testPitchColumn()
{
    QModelIndex tuneSource = m_model->insertTuneWithScore(0, "First Score", InstrumentPtr(new TestInstrument()));
    m_model->insertSymbol(0, tuneSource, new SymbolWithPitch());
    //m_model->sibling(symbolWithPitch.row(), MusicProxyModel::PitchColumn, symbolWithPitch);

    QModelIndex score = m_proxyModel->index(0, 0, QModelIndex());
    QModelIndex tune = m_proxyModel->index(0, 0, score);
    QModelIndex symbolWithPitch = m_proxyModel->index(0, 0, tune);
    QModelIndex pitchIndex = m_proxyModel->sibling(symbolWithPitch.row(), MusicProxyModel::PitchColumn, symbolWithPitch);
    QVERIFY2(symbolWithPitch.isValid(), "Failed inserting symbol");
    QVERIFY2(pitchIndex.isValid(), "Fail, pitch index isn't valid");

    //QVERIFY2(m_proxyModel->index(symbolWithPitch.row(), MusicProxyModel::PitchColumn, tune).isValid(), "No valid index for pitch column");

//    QModelIndex symbolWithoutPitch = m_model->insertSymbol(0, tune, new Symbol(LP::Bar, "testsymbol"));
//    QModelIndex noPitchIndex = m_model->index(symbolWithoutPitch.row(), 1, symbolWithoutPitch.parent());
//    QVERIFY2(m_model->data(noPitchIndex, Qt::DisplayRole).isValid() == false, "Valid data was returned for symbol with no pitch");
}

QTEST_APPLESS_MAIN(MusicProxyModelTest)

#include "tst_musicproxymodeltest.moc"
