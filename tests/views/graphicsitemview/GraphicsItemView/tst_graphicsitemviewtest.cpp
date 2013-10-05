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
#include <QStandardItemModel>
#include <graphicsitemview/graphicsitemview.h>
#include <graphicsitemview/visualmusicpresenter.h>
#include "tst_graphicsitemviewtest.h"

Q_IMPORT_PLUGIN(lp_greathighlandbagpipe)

GraphicsItemViewTest::GraphicsItemViewTest()
{
}

void GraphicsItemViewTest::init()
{
    m_model = new MusicModel(this);
    m_graphicsItemView = new GraphicsItemView();

    m_graphicsItemView->setModel(m_model);
}

void GraphicsItemViewTest::cleanup()
{
    delete m_graphicsItemView;
}

void GraphicsItemViewTest::testSetModel()
{
    QStandardItemModel *model = new QStandardItemModel(this);

    m_graphicsItemView->setModel(model);

    QVERIFY2(m_graphicsItemView->m_musicPresenter->model() ==
             model, "Music presenter model wasn't set through GraphicsItemView");

    QVERIFY2(m_graphicsItemView->model() == model, "QAbstractItemView model wasn't set");

    delete model;
}

QTEST_MAIN(GraphicsItemViewTest)
