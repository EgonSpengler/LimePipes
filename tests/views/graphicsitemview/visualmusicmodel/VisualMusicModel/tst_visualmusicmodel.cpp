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
#include <views/graphicsitemview/visualmusicmodel/visualmusicmodel.h>
#include "tst_visualmusicmodel.h"

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

void VisualMusicModelTest::cleanup()
{
    delete m_visualMusicModel;
}

void VisualMusicModelTest::init()
{
    m_visualMusicModel = new VisualMusicModel();
}

QTEST_MAIN(VisualMusicModelTest)
