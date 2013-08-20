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

void GraphicsItemViewTest::cleanup()
{
    delete m_graphicsItemView;
}

QTEST_MAIN(GraphicsItemViewTest)
