/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtTest/QtTest>
#include <QCoreApplication>
#include <QStandardItemModel>
#include <model/musicmodel.h>
#include <views/graphicsitemview/visualmusicmodel/visualmusicmodel.h>
#include "tst_visualmusicmodel.h"

Q_IMPORT_PLUGIN(lp_greathighlandbagpipe)

#include <QDebug>

VisualMusicModelTest::VisualMusicModelTest(QObject *parent)
    : QObject(parent)
{
}

void VisualMusicModelTest::testSetModel()
{
    QStandardItemModel *model = new QStandardItemModel(this);
    m_visualMusicModel->setModel(model);
    QVERIFY2(m_visualMusicModel->model() == model, "Failed setting QAbstractItemModel and getting it back");
}

void VisualMusicModelTest::testIsertScore()
{
    Q_ASSERT(m_musicModel->instrumentNames().count());

    m_musicModel->insertScore(0, "Testscore");

    QVERIFY2(m_visualMusicModel->m_rootItem != 0, "Root item is still 0 after insert of score");
    QVERIFY2(m_visualMusicModel->m_visualScoreIndexes.count() == 1,
             "No visual score was inserted");
}

void VisualMusicModelTest::cleanup()
{
    delete m_visualMusicModel;
    delete m_musicModel;
}

void VisualMusicModelTest::init()
{
    m_musicModel = new MusicModel(this);
    m_visualMusicModel = new VisualMusicModel();
    m_visualMusicModel->setModel(m_musicModel);
}

QTEST_MAIN(VisualMusicModelTest)
