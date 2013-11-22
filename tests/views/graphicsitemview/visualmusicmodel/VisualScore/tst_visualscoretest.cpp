/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <model/musicmodel.h>
#include <datatypes/timesignature.h>
#include <views/graphicsitemview/visualmusicmodel/visualscore.h>

Q_IMPORT_PLUGIN(GreatHighlandBagpipe)

class VisualScoreTest : public QObject
{
    Q_OBJECT

public:
    VisualScoreTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testItemType();
    void testGraphicalType();
    void testRowGraphics();
    void testSetDataFromIndex();
    void testDataChangedSignal();

private:
    VisualScore *m_visualScore;
    MusicModel *m_musicModel;
};

VisualScoreTest::VisualScoreTest()
{
}

void VisualScoreTest::init()
{
    m_visualScore = new VisualScore();
    m_musicModel = new MusicModel();
}

void VisualScoreTest::cleanup()
{
    delete m_visualScore;
    delete m_musicModel;
}

void VisualScoreTest::testItemType()
{
    QVERIFY2(m_visualScore->itemType() == VisualItem::VisualScoreItem,
             "Visual score returned wrong type");
}

void VisualScoreTest::testGraphicalType()
{
    QVERIFY2(m_visualScore->graphicalType() == VisualItem::GraphicalRowType,
             "Visual score is no graphical row type");
}

void VisualScoreTest::testRowGraphics()
{
    QList<InteractingGraphicsItem*> scoreRows(m_visualScore->rowGraphics());
    QVERIFY2(scoreRows.count() == 2, "Score has not correct row count");

    Q_ASSERT(scoreRows.count() == 2);
    QVERIFY2(scoreRows.at(0) == m_visualScore->headerItem(), "First row graphic is not header item");
    QVERIFY2(scoreRows.at(1) == m_visualScore->footerItem(), "Second row graphic is not footer item");
}

void VisualScoreTest::testSetDataFromIndex()
{
    Q_ASSERT(m_musicModel->instrumentNames().count());

    QString scoreTitle("Testscore");
    QString scoreType("3/4 March");
    QModelIndex scoreIndex = m_musicModel->insertScore(0, scoreTitle);
    QString scoreComposer("Composer");
    QString scoreArranger("Arranger");
    QString scoreYear("2013");
    QString scoreCopyright("TB");

    m_musicModel->setData(scoreIndex, scoreComposer, LP::ScoreComposer);
    m_musicModel->setData(scoreIndex, scoreType, LP::ScoreType);
    m_musicModel->setData(scoreIndex, scoreArranger, LP::ScoreArranger);
    m_musicModel->setData(scoreIndex, scoreYear, LP::ScoreYear);
    m_musicModel->setData(scoreIndex, scoreCopyright, LP::ScoreCopyright);
}

void VisualScoreTest::testDataChangedSignal()
{
    QSignalSpy spy(m_visualScore, SIGNAL(dataChanged(QVariant,int)));
    QString title("title 1");
}

QTEST_MAIN(VisualScoreTest)

#include "tst_visualscoretest.moc"
