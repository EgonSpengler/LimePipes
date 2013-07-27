/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <QCoreApplication>
#include <model/musicmodel.h>
#include <views/graphicsitemview/graphicsitemview.h>
#include "visualmusicmodeldummy.h"
#include "tst_graphicsitemviewtest.h"

Q_IMPORT_PLUGIN(lp_greathighlandbagpipe)

GraphicsItemViewTest::GraphicsItemViewTest()
{
}

void GraphicsItemViewTest::init()
{
    m_model = new MusicModel(this);
    m_graphicsItemView = new GraphicsItemView();
    m_visualMusicModelDummy = new VisualMusicModelDummy(this);

    m_graphicsItemView->setModel(m_model);
    m_graphicsItemView->setVisualMusicModel(m_visualMusicModelDummy);
}

void GraphicsItemViewTest::testScoreInserted()
{
    QSignalSpy signalSpy(m_visualMusicModelDummy, SIGNAL(insertScoreCalled()));

    m_model->insertScore(0, "Testscore");

    QVERIFY2(signalSpy.count(), "Insert score wasn't called on VisualMusicModelInterface");
}

void GraphicsItemViewTest::testTuneInserted()
{
    Q_ASSERT(m_model->instrumentNames().count());
    QSignalSpy signalSpy(m_visualMusicModelDummy, SIGNAL(insertTuneIntoScoreCalled()));

    QModelIndex score = m_model->insertScore(0, "Testscore");
    m_model->insertTuneIntoScore(0, score, m_model->instrumentNames().at(0));

    QVERIFY2(signalSpy.count(), "Insert tune wasn't called on VisualMusicModelInterface");
}

void GraphicsItemViewTest::testPartInserted()
{
    QSignalSpy signalSpy(m_visualMusicModelDummy, SIGNAL(insertPartIntoTuneCalled()));

    QModelIndex score = m_model->insertScore(0, "Testscore");
    QModelIndex tune  = m_model->insertTuneIntoScore(0, score, m_model->instrumentNames().at(0));
    m_model->insertPartIntoTune(0, tune, 8);

    QVERIFY2(signalSpy.count(), "Insert part wasn't called on VisualMusicModelInterface");
}

void GraphicsItemViewTest::cleanup()
{
    delete m_graphicsItemView;
}

QTEST_MAIN(GraphicsItemViewTest)
